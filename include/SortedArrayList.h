#ifndef SORTEDARRAYLIST_H
#define SORTEDARRAYLIST_H

#include "ArrayList.h"

template <typename E>
class SortedArrayList : public ArrayList<E> {
public:
    SortedArrayList(int maxSize = DEFAULT_MAX_SIZE) : ArrayList<E>(maxSize) {}
    void insert(E element) {
        ArrayList<E>::goToStart();
        while (!ArrayList<E>::atEnd() && element >= ArrayList<E>::getElement()) {
            ArrayList<E>::next();
        }
        ArrayList<E>::insert(element);
    }
    void append(E element) {
        insert(element);
    }
    bool contains(E element) {
        return indexOf(element) != -1;
    }

    // Si el elemento que se busca está repetido retorna la primera que se encuentre.
    int indexOf(E element) {
        int min = 0;
        int max = ArrayList<E>::size - 1;
        while (min <= max) {
            int mid = (min + max) / 2;
            if (element == ArrayList<E>::elements[mid])
                return mid;
             else if (element < ArrayList<E>::elements[mid])
                max = mid - 1;
            else
                min = mid + 1;
        }
        return -1;
    }
    // Esta versión retorna la aparición más a la izquierda del elemento.
    int indexOf2(E element) {
        int min = 0;
        int max = ArrayList<E>::size - 1;
        int mid;
        while (min < max) {
            mid = (min + max) / 2;
            if (element <= ArrayList<E>::elements[mid])
                max = mid;
            else
                min = mid + 1;
        }
        return ArrayList<E>::elements[mid] == element? mid : -1;
    }
};

#endif // SORTEDARRAYLIST_H
