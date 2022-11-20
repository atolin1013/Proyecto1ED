#ifndef AVLTREEDICTIONARY_H
#define AVLTREEDICTIONARY_H

#include "Dictionary.h"
#include "AVLTree.h"
#include "KVPair.h"
#include "DLinkedList.h"
#include <stdexcept>

using std::runtime_error;

template <typename K, typename V>
class AVLTreeDictionary : public Dictionary<K, V> {
private:
    AVLTree<KVPair<K, V>> pairs;

public:
    AVLTreeDictionary() : pairs() {}
    ~AVLTreeDictionary() {}
    void insert(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs.insert(p);
    }
    V remove(K key) {
        KVPair<K, V> p(key);
        p = pairs.remove(p);
        return p.value;
    }
    V getValue(K key) {
        KVPair<K, V> p(key);
        p = pairs.find(p);
        return p.value;
    }
    void setValue(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs.remove(p);
        pairs.insert(p);
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return pairs.contains(p);
    }
    List<K>* getKeys() {
        DLinkedList<K> *keys = new DLinkedList<K>();
        List<KVPair<K, V>> *elements = pairs.getElements();
        elements->goToStart();
        while (!elements->atEnd()) {
            KVPair<K, V> p = elements->getElement();
            keys->append(p.key);
            elements->next();
        }
        delete elements;
        return keys;
    }
    List<V>* getValues() {
        DLinkedList<V> *values = new DLinkedList<V>();
        List<KVPair<K, V>> *elements = pairs.getElements();
        elements->goToStart();
        while (!elements->atEnd()) {
            KVPair<K, V> p = elements->getElement();
            values->append(p.value);
            elements->next();
        }
        delete elements;
        return values;
    }
    void clear() {
        pairs.clear();
    }
    int getSize() {
        return pairs.getSize();
    }
};

#endif // AVLTREEDICTIONARY_H
