#include <iostream>
#include <fstream>
#include <cstdint>
#include <time.h>
#include <chrono>

#include "List.h"
#include "Trie.h"
#include "ArrayList.h"

using namespace std;
using namespace std::chrono;

int getArraySize(string archivo, int pLine){
    string line;
    int i = 0;
    int count = 0;
//    int pLine = 2500;
    int lineas;
    ifstream myfile(archivo);
    ifstream in_file(archivo, ios::binary);
    in_file.seekg(0, ios::end);
    int file_size = in_file.tellg();
    in_file.close();
    for(i = 1; i <= pLine; i++){
//        if(i % 4 != 0)
//            myfile.ignore();
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

char filtro(char letra){
    if(letra < 123){
        if(letra > 96)
            return letra;
        if(letra > 64 && letra < 91)
            return letra + 32;
        if(letra == 32) // Espacio
            return 32;
        return 0;
    }
    if(letra == 130 || letra == 144) // É
        return 130;
    if(letra == 160 || letra == 184) // Á
        return 160;
    if(letra == 161 || letra == 214) // Ú
        return 161;
    if(letra == 162 || letra == 224) // Ó
        return 162;
    if(letra == 163 || letra == 233) // Ú
        return 163;
    if(letra == 164|| letra == 165) // Ñ
        return 164;
    if(letra == 129 || letra == 154) // Ü
        return 129;
    return 0;
}

void basePrueba(int pLine){
    string archivos[] = {"C:\\Users\\Marvin\\Desktop\\Cosas de Antony\\Progra 0mg\\Estructura de datos\\PADRON_COMPLETO.txt","el_quijote.txt", "bible.txt", "lotr.txt", "lmao.txt", "novela.txt", "big.txt"};
//    cout << pLine << endl;
    clock_t start = clock();
    for(int i = 0; i < 10; i++){
//        cout << 100 * (float)(3561311 - getArraySize(archivos[0], pLine)) / 3561311 << endl;
        getArraySize(archivos[0], pLine);
        getArraySize(archivos[1], pLine);
        getArraySize(archivos[2], pLine);
        getArraySize(archivos[3], pLine);
        getArraySize(archivos[4], pLine);
        getArraySize(archivos[5], pLine);
        getArraySize(archivos[6], pLine);
//        getArraySizeAux(archivos[0]);
//        getArraySizeAux(archivos[1]);
//        getArraySizeAux(archivos[2]);
//        getArraySizeAux(archivos[3]);
//        getArraySizeAux(archivos[4]);
//        getArraySizeAux(archivos[5]);
//        getArraySizeAux(archivos[6]);
    }
    clock_t stop = clock();
    cout << (long double) (stop - start) / CLOCKS_PER_SEC << endl;
}

void pToList(Trie* arbol){

}

void cargar(ArrayList<string>* arrayDestino, Trie* arbolDestino, string archivo){
    string line;
    int i = 0;
    ifstream myfile(archivo);
    arrayDestino->goToStart();
    while(getline(myfile, line)){
        arrayDestino->append(line);
        string palabra = "";
        char letra;
        for(int e = 0; e < (int)line.length(); e++){
            letra = filtro(line.at(e));
            if(letra == 32){
                if(palabra.length() > 1)
                    arbolDestino->insert(palabra, i);
                palabra = "";
            } else
            if(filtro(letra) != 0)
                palabra += letra;
        }
        i++;
    }
}

int main() {
    string archivos[] = {
        "C:\\Users\\Marvin\\Desktop\\Cosas de Antony\\Progra 0mg\\Estructura de datos\\PADRON_COMPLETO.txt",
        "el_quijote.txt", "bible.txt", "lotr.txt", "lmao.txt", "novela.txt", "big.txt"
        };
    int index = 6;
//    for(int pLine = 100; pLine == 100; pLine = pLine + 1000){
//        basePrueba(pLine);
//    }
//    for(int e = 0; e < 10; e++)
//    basePrueba(2500);
    string archivo = "C:\\Users\\Marvin\\Desktop\\Cosas de Antony\\Progra 0mg\\Estructura de datos\\PADRON_COMPLETO.txt";
    Trie* arbol = new Trie();
    clock_t start = clock();

    ArrayList<string>* lista = new ArrayList<string>(getArraySize(archivos[index], 2500));
    cargar(lista, arbol, archivos[index]);

    clock_t stop = clock();
    arbol->printD();
    cout << (float) (stop - start) / CLOCKS_PER_SEC << endl;
//    lista->goToStart();
//    for(int i = 0; i < 100; i++){
//        cout << lista->getElement() << endl;
//        lista->next();
//    }
    return 0;
}
