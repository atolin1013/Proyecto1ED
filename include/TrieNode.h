#ifndef TRIENODE_H
#define TRIENODE_H

#include "BSTDictionary.h"
#include "List.h"

class TrieNode {
public:
    int prefixCount;
    bool isFinal;
    Dictionary<char, TrieNode*> *children;

    TrieNode() {
        prefixCount = 0;
        isFinal = false;
        children = new BSTDictionary<char, TrieNode*>();
    }
    ~TrieNode() {
        delete children;
    }
    bool contains(char c) {
        return children->contains(c);
    }
    TrieNode* getChild(char c) {
        return children->getValue(c);
    }
    void addChild(char c) {
        children->insert(c, new TrieNode());
    }
    void removeChild(char c) {
        children->remove(c);
    }
    int childrenCount() {
        return children->getSize();
    }
    List<char>* getChildren() {
        return children->getKeys();
    }
    List<TrieNode*>* getChildrenPointers() {
        return children->getValues();
    }
};

#endif // TRIENODE_H
