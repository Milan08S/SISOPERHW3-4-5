//
//  activity4.cpp
//  Assigment 2
//
//

#include <iostream>

int main(){
    int** matrizDinamica;    //Declaracion de un puntero a puntero para crear una matriz dinamica
    int filas = 3;
    int columnas = 4;

    //Asignacion para la matriz dinamica
    matrizDinamica = new int*[filas];    //Crear array de puntero a int(filas)

    for (int i = 0; i < filas; i++) {
        matrizDinamica[i] = new int[columnas];    //Cada puntero a un array de int(columnas)
    }

    //Incializacion de las matriz con valores
    int valor = 1;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++) {
            matrizDinamica[i][j] = valor++;
        }
    }

    //Imprimir la matriz
    std::cout << "Matriz Dinamica: " << std::endl;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            std::cout << matrizDinamica[i][j] << " ";
        }
    }

    //Liberar la memoria asignada
    for(int i = 0; i < filas; i++){
        delete[] matrizDinamica[i];    //Liberar cada array de int(columnas)
    }
    delete[] matrizDinamica;    //Liberar el array de punteros (filas)

    return 0;

}
