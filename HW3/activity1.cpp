//
//  activity1.cpp
//  Assigment 2
//


#include <iostream>

int main(){
    // declaracion y asignacion de una variable
    int variable1 = 42;
    //presente el valor almacenado en la variable
    std::cout << "Valor almacenado: " << variable1  << std::endl;
    //presente la direccion de memoria
    std::cout << "Direccion de memoria: " << &variable1 << std::endl;

    //Punture que "apunta" a la direccion de variable1
    int * puntero = &variable1;
    * puntero = 219;

    //Presente el valor almacenado en la variable
    std::cout << "Valor almacenado: " << variable1 << std::endl;

    return 0;
}
