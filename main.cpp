#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>

#include "List.h"
#include "Trie.h"
#include "ArrayList.h"

using namespace std;
using namespace std::chrono;

int getArraySize(string archivo){
    string line;
    int i = 0;
    int count = 0;
    int pLine = 2500;
    int lineas;
    ifstream myfile(archivo);
    ifstream in_file(archivo, ios::binary);
    in_file.seekg(0, ios::end);
    int file_size = in_file.tellg();
    in_file.close();
    for(i = 1; i <= pLine; i++){
        if(!getline(myfile, line))
            break;
        count += line.length();
    }
    myfile.close();
    lineas = file_size / (count / i);
    return lineas + lineas / 10;
}

int getArraySizeAux(string archivo){
    string line;
    int i = 0;
    ifstream myfile(archivo);
    while(getline(myfile, line))
        i++;
    myfile.close();
    return i;
}

void prueba(string archivo, int pLine){



    /*
    el_quijote
    bible
    PADRON_COMPLETO
    bible
    lmao
    big
    novela
    */




}

void basePrueba(int pLine){
    string archivos[] = {"PADRON_COMPLETO.txt","el_quijote.txt", "bible.txt", "lotr.txt", "lmao.txt", "novela.txt", "big.txt"};
    cout << pLine << endl;
    prueba(archivos[0], pLine);
    prueba(archivos[1], pLine);
    prueba(archivos[2], pLine);
    prueba(archivos[3], pLine);
    prueba(archivos[4], pLine);
    prueba(archivos[5], pLine);
    prueba(archivos[6], pLine);
    cout << endl;
}

void cargar(ArrayList<string>* arrayDestino, Trie* arbolDestino, string archivo){
    string line;
    int i = 0;
    ifstream myfile(archivo);
    arrayDestino->goToStart();
    while(getline(myfile, line)){
        arrayDestino->append(line);
        i++;
    }
}

int main() {
//    for(int pLine = 100; pLine == 100; pLine = pLine + 1000){
//        basePrueba(pLine);
//    }
//    for(int e = 0; e < 10; e++)
//    basePrueba(2500);
    string archivo = "PADRON_COMPLETO.txt";
    Trie* arbol = new Trie();
    ArrayList<string>* lista = new ArrayList<string>(getArraySize(archivo));
    cargar(lista, arbol, archivo);
    lista->goToStart();
//    for(int i = 0; i < 100; i++){
//        cout << lista->getElement() << endl;
//        lista->next();
//    }
    return 0;
}
