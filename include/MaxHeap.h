#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <stdexcept>
#include "DLinkedList.h"
#include "KVPair.h"
#define DEFAULT_MAX_SIZE 1024
using std::runtime_error;
/*
Clase de tipo generico encargada de organizar una serie de elementos de mayor a menor
debtro de un arreglo de n capacidad.
Tiene por atributos un arreglo de tipo generico, un intero con la capacidad maxima
y un entero con la cantidad de elementos insertados.
*/
template <typename E>
class MaxHeap {
private:
    E *elements;
    int max;
    int size;

    void expand(){
        E *temp = new E[max * 2];
        for (int i = 0; i < size; i++){
            temp[i] = elements[i];
        }
        delete [] elements;
        elements = temp;
        max = max * 2;
    }
    void siftUp(int pos){
        while (pos > 0 && elements[pos] > elements[parent(pos)]){
            swap (pos , parent(pos));
            pos = parent (pos);
        }

    }
    int parent(int pos){
        return pos /2;
    }
    int leftChild(int pos){
        return pos * 2 + 1;
    }
    int rightChild(int pos){
        return (pos *2) + 2;
    }
    void swap(int pos, int pos2){
        E temp = elements[pos];
        elements[pos] = elements[pos2];
        elements[pos2] = temp;
    }
    void siftDown(int pos){
        while (!isLeaf(pos) && elements[pos] < elements[greaterChild(pos)]){
            int gChild = greaterChild(pos);
            swap(pos, gChild);
            pos = gChild;
        }
    }
    bool isLeaf(int pos){
        if (pos > 0 || pos < size)
           return leftChild(pos) >= size;
        return false;
    }
    int greaterChild(int pos){
        if (pos < 0 || pos >= size)
            throw runtime_error("Index out of range.");
        if (rightChild(pos) >= size ||
            elements[leftChild(pos)] > elements[rightChild(pos)])
            return leftChild(pos);
        return rightChild(pos);
    }
public:
    MaxHeap(int max = DEFAULT_MAX_SIZE){
        if (max < 1)
            throw runtime_error("Invalid array size.");
        elements = new E[max * 4];
        this->max = max;
        size = 0;
    }
    ~MaxHeap(){
        delete [] elements;
    }
    void insert(E element){
        if (size == max)
            expand();
        elements[size] = element;
        siftUp(size);
        size++;
    }
    E first(){
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return elements[0];
    }
    E removeFirst(){
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return remove(0);
    }
    E remove(int pos){
        if (pos >= size || pos < 0)
            throw runtime_error("Index out of range.");
        swap(pos, size-1);
        size--;
        if (size > 1)
            siftDown(pos);
        return elements[size];
    }
    int getSize(){
        return size;
    }
    bool isEmpty(){
        return size == 0;
    }
    bool contains(E element){
        for (int i = 0; i< size; i++){
            if (elements[i] == element)
                return true;
        }
        return false;
    }

    E find(E element){
        for (int i = 0; i< size; i++){
            if (elements[i] == element)
                return elements[i];
        }
        return false;
    }

    E getElement(int pos){
        if (pos < size)
            return elements[pos];
    }

    void print(){
        cout << "[ ";
        for (int i = 0; i < size; i++){
            cout << elements[i] << " ";
        }
        cout << " ]" << endl;
    }
    List<E>* removeTop(int n){
        List<E>* listaTop = new ArrayList<E>;
        for(int i = 0; i < n; i++){
            listaTop->append(removeFirst());
        }
        return listaTop;
    }
};

#endif // MAXHEAP_H

