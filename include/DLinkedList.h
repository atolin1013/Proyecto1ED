#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "List.h"
#include "DNode.h"
#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E> *head;
    DNode<E> *tail;
    DNode<E> *current;
    int size;

public:
    DLinkedList() {
        current = head = new DNode<E>(nullptr, nullptr);
        head->next = tail = new DNode<E>(nullptr, head);
        size = 0;
    }
    ~DLinkedList() {
        clear();
        delete head;
        delete tail;
    }
    void insert(E element) {
        current->next = current->next->previous =
            new DNode<E>(element, current->next, current);
        size++;
    }
    void append(E element) {
        tail->previous = tail->previous->next =
            new DNode<E>(element, tail, tail->previous);
        size++;
    }
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        E result = current->next->element;
        current->next = current->next->next;
        delete current->next->previous;
        current->next->previous = current;
        size--;
        return result;
    }
    void clear() {
        while (head->next != tail) {
            head->next = head->next->next;
            delete head->next->previous;
        }
        current = tail->previous = head;
        size = 0;
    }
    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        return current->next->element;
    }
    void goToStart() {
        current = head;
    }
    void goToEnd() {
        current = tail->previous;
    }
    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of range.");
        current = head;
        for (int i = 0; i < pos; i++)
            current = current->next;
    }
    void next() {
        if (current->next != tail)
            current = current->next;
    }
    void previous() {
        if (current != head)
            current = current->previous;
    }
    bool atStart() {
        return current == head;
    }
    bool atEnd() {
        return current == tail->previous;
    }
    int getPos() {
        DNode<E> *temp = head;
        int pos = 0;
        while (temp != current) {
            temp = temp->next;
            pos++;
        }
        return pos;
    }
    int getSize() {
        return size;
    }
    int indexOf(E element){
        /**
Dice la posición de un elemento en una lista. Recibe un elemento a buscar dentro de la lista, si
se encuentra, retorna la posición donde fue encontrado. Si el elemento buscado se encuentra
repetido, debe retornar la posición de la primera ocurrencia. Si no se encuentra, retorna el
valor -1. La posición actual de la lista no debe cambiar después de invocar este método.

        **/
        int pl = getPos();
        goToStart();
        while(!atEnd()){
            if(getElement() == element){
                goToPos(pl);
                return(getPos());
            }
            else
                next();
        }
        goToPos(pl);
        return -1;
    }
    bool contains(E element){
        /**
Dice si una lista contiene un elemento. Recibe un elemento a buscar dentro de la lista, si lo
encuentra, retorna true, de otro modo retorna false. La posición actual de la lista no debe
cambiar después de invocar este elemento.
        **/
        int pl = getPos();
        goToStart();
        while(!atEnd()){
            if(getElement() == element){
                goToPos(pl);
                return true;
            } else {
                next();
            }
        }
        goToPos(pl);
        return false;
    }
    void extend(List<E>* L){
        /**
Método que agrega al final de la lista actual los elementos de otra lista enviada por parámetro.
Recibe por parámetro un puntero a un objeto tipo List (puede ser cualquiera de las clases
derivadas: ArrayList, LinkedList o DLinkedList). Después de invocar este método, todos los
elementos de la lista L enviada por parámetro deben agregarse al final de la lista actual, en el
mismo orden en que se encuentran en la lista L. Al igual que los métodos insert y append, la
capacidad de la lista debe aumentar mediante el método privado expand en caso de que se
alcance la capacidad máxima. La posición actual de la lista actual y de la lista enviada por
parámetro no debe ser alterada después de invocar este método.
        **/
        int p = L->getPos();
        L->goToStart();
        while(!L->atEnd()){
            append(L->getElement());
            L->next();
        }
        L->goToPos(p);

    }
    bool equals(List<E>* L){
        /**
Método que dice si la lista actual contiene los mismos elementos y en el mismo orden que la
lista enviada por parámetro. Recibe por parámetro un puntero a un objeto tipo List. El método
debe comprobar si la cantidad de elementos y el orden de estos es idéntico en ambas listas. De
ser así, el método retorna true, de otro modo, false. La posición actual de ambas listas no debe
ser alterada después de invocar este método.
        **/
        int Ap = getPos();
        int Lp = L->getPos();
        goToStart();
        L -> goToStart();
        while(!atEnd() && !L->atEnd()){
            if (getElement() != L->getElement()){
                goToPos(Ap);
                L->goToPos(Lp);
                return false;
            } else {
                next(); L->next();
            }
        }
        if(atEnd() && L->atEnd()){
            goToPos(Ap);
            L->goToPos(Lp);
            return true;
        }
        goToPos(Ap);
        L->goToPos(Lp);
        return false;
    }
    void print() {
        cout << "[ ";
        for (goToStart(); !atEnd(); next())
            cout << getElement() << " ";
        cout << "]" << endl;
    }
};

#endif // DLINKEDLIST_H
