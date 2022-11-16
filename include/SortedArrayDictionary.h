#ifndef SORTEDARRAYDICTIONARY_H
#define SORTEDARRAYDICTIONARY_H

#include "Dictionary.h"
#include "KVPair.h"
#include "DLinkedList.h"
#include "SortedArrayList.h"

template <typename K, typename V>
class SortedArrayDictionary : public Dictionary<K, V> {
private:
    SortedArrayList<KVPair<K, V> > *pairs;

    void search(K key) {
        KVPair<K, V> p(key);
        pairs->goToPos(pairs->indexOf(p));
    }
    void checkNotExisting(K key) {
        if (contains(key)) {
            throw runtime_error("Duplicated key.");
        }
    }
    void checkExisting(K key) {
        if (!contains(key)) {
            throw runtime_error("Key not found.");
        }
    }

public:
    SortedArrayDictionary(int maxSize = DEFAULT_MAX_SIZE) {
        pairs = new SortedArrayList<KVPair<K, V> >(maxSize);
    }
    ~SortedArrayDictionary() {
        delete pairs;
    }
    void insert(K key, V value) {
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        pairs->insert(p);
    }
    V remove(K key) {
        checkExisting(key);
        search(key);
        KVPair<K, V> p = pairs->remove();
        return p.value;
    }
    V getValue(K key) {
        checkExisting(key);
        search(key);
        KVPair<K, V> p = pairs->getElement();
        return p.value;
    }
    void setValue(K key, V value) {
        checkExisting(key);
        search(key);
        KVPair<K, V> p = pairs->remove();
        p.value = value;
        pairs->insert(p);
    }
    void clear() {
        pairs->clear();
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return pairs->contains(p);
    }
    List<K>* getKeys() {
        List<K>* keys = new DLinkedList<K>();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            keys->append(p.key);
        }
        return keys;
    }
    List<V>* getValues() {
        List<V>* values = new DLinkedList<V>();
        for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
            KVPair<K, V> p = pairs->getElement();
            values->append(p.value);
        }
        return values;
    }
    int getSize() {
        return pairs->getSize();
    }
};

#endif // SORTEDARRAYDICTIONARY_H
