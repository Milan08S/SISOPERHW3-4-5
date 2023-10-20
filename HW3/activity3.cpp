//
//  activity3.cpp
//  Assigment 2
//

#include <iostream>

int main(){
    const int tamanoarray = 5;
    //Declaracion de un array de enteros
    int numeros[tamanoarray] = {10, 20, 30, 40, 50};

    //Imprimir el contenido del array
    std::cout<<"Contenido del array 'numeros': ";
    for(int i = 0; i < tamanoarray; i++) {
        std::cout << numeros[i] << " ";
    }
    std::cout << std::endl;

    //Declarar un puntero que apunta al inicio del array
    int* punteroNumeros = numeros;
    
    //Utilizar el puntero para acceder y modificar elementos del array
    //Modificar el segundo elemento del array
    punteroNumeros[1] = 99;

    //Imprimir el contenido del array despues de la modificacion
    std::cout << "Contenido del array 'numeros' despues de la modificacion: ";
    for ( int i = 0; i < tamanoarray; i++) {
        std::cout << numeros[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
