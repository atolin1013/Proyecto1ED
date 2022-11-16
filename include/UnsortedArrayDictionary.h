#ifndef UNSORTEDARRAYDICTIONARY_H
#define UNSORTEDARRAYDICTIONARY_H
#define DEFAULT_MAX_SIZE 1024

#include "Dictionary.h"
#include "KVPair.h"
#include "DLinkedList.h"

template <typename K, typename V>
class UnsortedArrayDictionary : public Dictionary<K, V> {
private:
    ArrayList<KVPair<K, V> > *pairs;

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
    UnsortedArrayDictionary(int maxSize = DEFAULT_MAX_SIZE) {
        pairs = new ArrayList<KVPair<K, V> >(maxSize);
    };
    ~UnsortedArrayDictionary() {
        delete pairs;
    };
    void insert(K key, V value) {
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        pairs->append(p);
    }
    V remove(K key) {
        checkExisting(key);
        KVPair<K, V> p;
        p = pairs->remove();
        return p.value;
    }
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = pairs->getElement();
        return p.value;
    }
    void setValue(K key, V value) {
        checkExisting(key);
        KVPair<K, V> p(key, value);
        pairs->remove();
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

#endif // UNSORTEDARRAYDICTIONARY_H
