#include <iostream>
#include <fstream>
#include <cstdint>
#include <time.h>
#include <chrono>
#include <windows.h>
#include <thread>

#include "List.h"
#include "Trie.h"
#include "ArrayList.h"
#include "AVLTreeDictionary.h"
#include "MaxHeap.h"

using namespace std;

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

char filtro(char letra){
    if(letra < 123){
        if(letra > 96)
            return letra;
        if(letra > 64 && letra < 91)
            return letra + 32;
        if(letra == 32 || letra == 45) // Espacio o guión
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

void cargar(ArrayList<string>* arrayDestino, Trie* arbolDestino,
            string archivo, MaxHeap<KVPair<int, string>>* topHeap, int arraySize){
    string line;
    int i = 0;
    ifstream myfile(archivo);
    arrayDestino->goToStart();
    while(getline(myfile, line)){
        if(arrayDestino->checkFullList())
            throw runtime_error("Array size exceeded");
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

void cargarHeap(Trie* arbol, MaxHeap<KVPair<int, string>>* topHeap){
    arbol->loadHeap(topHeap);
}

int main() {
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    Trie* arbol;
    ArrayList<string>* lista;
    MaxHeap<KVPair<int, string>> *topHeap;
    int arraySize;

    int opc =0;
    int opc2 =0;
    //mensaje de bienvenida
    cout <<"Bienvenidos al programa de indizacion de textos " << endl;
    cout <<"Nos complace mucho tenerlo por acá " << endl;
    string archivo;
    string foo;
    while(true){
        opc = 0;
        archivo = "";
        while(archivo == ""){
            cout<< "Por favor escriba el nombre del archivo junto con su extension: "; cin>> archivo;
        }
        topHeap = new MaxHeap<KVPair<int, string>>();
        arbol = new Trie();
        ifstream e(archivo);
        if(getline(e, foo)){
            try{
                arraySize = getArraySize(archivo, 2500);
                lista = new ArrayList<string>(arraySize);
                cargar(lista, arbol, archivo, topHeap, arraySize);
            } catch(runtime_error&) {
                delete lista;
                arraySize = getArraySizeAux(archivo);
                lista = new ArrayList<string>(arraySize);
                cargar(lista, arbol, archivo, topHeap, arraySize);
            };
            thread top(cargarHeap, arbol, topHeap);

            //MAIN
            while(opc != 5)
            {
                opc = 0;
                opc2 = 0;
                cout <<"\n\n1. Consulta por prefijo" << endl;
                cout <<"2. Buscar palabra" << endl;
                cout <<"3. Buscar por cantidad de letras" << endl;
                cout <<"4. Palabras mas utilizadas" << endl;
                cout <<"5. Cargar nuevo archivo" << endl
                    << "6. Salir" << endl;
                cout<< "Digita la opcion a realizar: ";
                cin >>opc;
                switch(opc)
                {
                    case 1:
                        {
                        cout <<"Ingresa un prefijo para buscar en el arbol" << endl;
                        string prefijo = "";
                        cin >>prefijo;
                        List<string> *palabras = arbol->getMatches(prefijo, lista);

                        palabras->print();

                        delete palabras;
                        }
                        break;
                    case 2:
                        {

                        cout <<"Ingresa la palabra a buscar" << endl;
                        string palabra = "";
                        cin >>palabra;
                        arbol->getWordMatches(palabra, lista)->print();
                        }
                        break;
                    case 3: //Buscar por Cantidad letras
                        {
                        cout <<"Ingresa un entero" << endl;
                        int entero = 0;
                        cin >>entero;
                            List<string> *words = arbol->getMatches(entero);//
                            //lines
                            cout << "[ ";
                            for (words->goToStart(); !words->atEnd(); words->next())
                            cout << words->getElement()<<"\n" <<endl;
                            cout << "]" << endl;
                        } break;
                    case 4://Palabras mas utilizadas
                        {
                        cout <<"1. Ver top" << endl;
                        cout <<"2. Regresar al menu principal" << endl;
                        cin >>opc2;
                        string palabra = "";
                        if(top.joinable()){
                            top.join();
                        }
                        switch(opc2)
                        {
                            case 1:
                                {
                                cout <<"Ingresa la cantidad de elementos" << endl;
                                int cantidad = 0;
                                cin>>cantidad;
                                List<KVPair<int,string>>* words = topHeap->removeTop(cantidad);

                                for (words->goToStart(); !words->atEnd(); words->next())
                                    cout << words->getElement()<<endl;
                                break;
                                }
                            default:
                                break;
                            break;
                        }
                        break;
                    }
                    case 5:
                        {
                            delete arbol;
                            delete lista;
                            delete topHeap;
                            break;
                        }
                    case 6:{
                        if(top.joinable()){
                            top.join();
                        }
                        return 0;
                    }
                    default:  cout <<"Opción fuera de rango, por favor escriba una nueva opción" << endl;
                }

            }
            if(top.joinable()){
                top.join();
            }
        } else {
            cout << "Archivo introducido es inválido" << endl;
        }
    }
    return 0;
}
