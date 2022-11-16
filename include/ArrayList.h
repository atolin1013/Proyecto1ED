#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#define DEFAULT_MAX_SIZE 1024

#include "List.h"
#include <stdexcept>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayList : public List<E> {
protected:
    E *elements;
    int max;
    int size;
    int pos;

    bool checkFullList() {
        return(size == max);
    }

private:
    void expand(){
        E* expandedElements = new E[max * 2];
        E* provisional;
        pos = 0;
        while(pos < size){
            expandedElements[pos] = elements[pos];
            pos++;
        }
        provisional = elements;
        elements = expandedElements;
        max *= 2;
        delete provisional;
    }

public:
    ArrayList(int max = DEFAULT_MAX_SIZE) {
        if (max < 1)
            throw runtime_error("Invalid max size.");
        elements = new E[max];
        this->max = max;
        size = 0;
        pos = 0;
    }
    ~ArrayList() {
        delete [] elements;
    }

    void insert(E element) {
        if(checkFullList())
            expand();
        for (int i = size; i > pos; i--)
            elements[i] = elements[i - 1];
        elements[pos] = element;
        size++;
    }
    void append(E element) {
        if(checkFullList())
            expand();
        elements[size] = element;
        size++;
    }
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (pos == size)
            throw runtime_error("No current element.");
        E result = elements[pos];
        for (int i = pos; i < size - 1; i++)
            elements[i] = elements[i + 1];
        size--;
        return result;
    }
    void clear() {
        size = pos = 0;
        //delete [] elements;
        //elements = new E[max];
    }
    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (pos == size)
            throw runtime_error("No current element.");
        return elements[pos];
    }
    void goToStart() {
        pos = 0;
    }
    void goToEnd() {
        pos = size;
    }
    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Invalid index.");
        this->pos = pos;
    }
    void next() {
        if (pos < size)
            pos++;
    }
    void previous() {
        if (pos > 0)
            pos--;
    }
    bool atStart() {
        return pos == 0;
    }
    bool atEnd() {
        return pos == size;
    }
    int getPos() {
        return pos;
    }
    int getSize() {
        return size;
    }
    void print() {
        cout << "[ ";
        for (goToStart(); !atEnd(); next())
            cout << getElement() << " ";
        cout << "]" << endl;
    }
    int indexOf(E element){
        /**
Dice la posici�n de un elemento en una lista. Recibe un elemento a buscar dentro de la lista, si
se encuentra, retorna la posici�n donde fue encontrado. Si el elemento buscado se encuentra
repetido, debe retornar la posici�n de la primera ocurrencia. Si no se encuentra, retorna el
valor -1. La posici�n actual de la lista no debe cambiar despu�s de invocar este m�todo.

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
encuentra, retorna true, de otro modo retorna false. La posici�n actual de la lista no debe
cambiar despu�s de invocar este elemento.
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
M�todo que agrega al final de la lista actual los elementos de otra lista enviada por par�metro.
Recibe por par�metro un puntero a un objeto tipo List (puede ser cualquiera de las clases
derivadas: ArrayList, LinkedList o DLinkedList). Despu�s de invocar este m�todo, todos los
elementos de la lista L enviada por par�metro deben agregarse al final de la lista actual, en el
mismo orden en que se encuentran en la lista L. Al igual que los m�todos insert y append, la
capacidad de la lista debe aumentar mediante el m�todo privado expand en caso de que se
alcance la capacidad m�xima. La posici�n actual de la lista actual y de la lista enviada por
par�metro no debe ser alterada despu�s de invocar este m�todo.
        **/
        int p = L->getPos();
        L->goToStart();
        while(!L->atEnd()){
            if(checkFullList()){
                expand();
            }
            append(L->getElement());
            L->next();
        }
        L->goToPos(p);

    }
    bool equals(List<E>* L){
        /**
M�todo que dice si la lista actual contiene los mismos elementos y en el mismo orden que la
lista enviada por par�metro. Recibe por par�metro un puntero a un objeto tipo List. El m�todo
debe comprobar si la cantidad de elementos y el orden de estos es id�ntico en ambas listas. De
ser as�, el m�todo retorna true, de otro modo, false. La posici�n actual de ambas listas no debe
ser alterada despu�s de invocar este m�todo.
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
};

#endif // ARRAYLIST_H
