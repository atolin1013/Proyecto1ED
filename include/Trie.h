#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Trie {
private:
    TrieNode* root;

    // Encontrar un nodo dentro del árbol
    // Retorna su dirección si lo encuentra, si no null.
    TrieNode* findNode(string prefix) {
        TrieNode* current = root;
        for (unsigned int i = 0; i < prefix.size(); i++) {
            if (current->contains(prefix[i])) {
                current = current->getChild(prefix[i]);
            } else
                return nullptr;
        }
        return current;
    }
    void clearAux(TrieNode* current) {
        if (current->childrenCount() == 0) {
            delete current;
            return;
        }
        List<TrieNode*>* children = current->getChildrenPointers();
        children->goToStart();
        while (!children->atEnd()) {
            clearAux(children->getElement());
            children->next();
        }
        delete children;
        delete current;
    }
    void getMatchesAux(TrieNode *current, string prefix, List<string> *result) {
        if (current->isFinal)
            result->append(prefix);
        List<char> *children = current->getChildren();
        for (children->goToStart(); !children->atEnd(); children->next()) {
            char c = children->getElement();
            string newPrefix = prefix + c;
            getMatchesAux(current->getChild(c), newPrefix, result);
        }
        delete children;
    }
    bool containsWordAux(string word, int line) {
        TrieNode *current = findNode(word);
        if (current == nullptr)
            return false;
        if(current->isFinal)
            current->lines->append(line);
        else
            return false;
        return true;
    }

public:
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        clear();
        delete root;
    }
    void insert(string word, int line) {
        if (containsWordAux(word, line))
            return;
        TrieNode* current = root;
        for (unsigned int i = 0; i < word.size(); i++) {
            current->prefixCount++;
            if (!current->contains(word[i]))
                current->addChild(word[i]);
            current = current->getChild(word[i]);
        }
        current->prefixCount++;
        current->isFinal = true;
        current->lines->append(line);
    }
    bool containsWord(string word) {
        TrieNode *current = findNode(word);
        if (current == nullptr)
            return false;
        return current->isFinal;
    }
    bool containsPrefix(string prefix) {
        TrieNode *current = findNode(prefix);
        return current != nullptr;
    }
    int prefixCount(string prefix) {
        TrieNode *current = findNode(prefix);
        if (current == nullptr)
            return 0;
        return current->prefixCount;
    }
    void remove(string word) {
        if (!containsWord(word))
            throw runtime_error("Word not in trie.");
        TrieNode *current = root;
        for (unsigned int i = 0; i < word.size(); i++) {
            current->prefixCount--;
            TrieNode *child = current->getChild(word[i]);
            if (child->prefixCount == 1)
                current->removeChild(word[i]);
            if (current->prefixCount == 0)
                delete current;
            current = child;
        }
        current->prefixCount--;
        if (current->prefixCount == 0)
            delete current;
        else
            current->isFinal = false;
    }
    void clear() {
        clearAux(root);
        root = new TrieNode();
    }
    List<string>* getMatches(string prefix) {
        List<string> *result = new DLinkedList<string>();
        TrieNode *current = findNode(prefix);
        if (current != nullptr) {
            getMatchesAux(current, prefix, result);
        }
        return result;
    }
    int getSize() {
        return root->prefixCount;
    }
    void print() {
        List<string> *words = getMatches("");
        words->print();
        delete words;
    }
};

#endif // TRIE_H
