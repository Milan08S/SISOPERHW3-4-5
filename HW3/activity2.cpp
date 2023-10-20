//
//  activity2.cpp
//  Assigment 2


#include <iostream>
using namespace std;

int main(){
    //declare y asigne la variable (una_variable)
    float una_variable = 999.9;

    //declare y asigne a un punturo (un_puntero) a la referencia a la referencia a la interior variable
    float * un_puntero = &una_variable;

    //imprime el valor que esta almacenado en el punturo
    cout << "un_puntero: " << *un_puntero  << endl;

    //modifique el valor del puntero
    *un_puntero = 1000;

    //imprima el valor almacenadoen una_varibale
    cout << "una_variable= " << una_variable << endl;

    //cree una referencia a una_variable
    float &una_referencia = una_variable;

    //modifique que la referencia
    una_referencia = 1999.9;

    //imprima el valor de una_variable
    cout << "una_refrencia= " << una_referencia << endl;

    return 0;
}

