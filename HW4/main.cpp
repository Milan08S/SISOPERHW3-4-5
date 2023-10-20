#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class GestorMemoria{
private:
    int tamanoMemoria;
    std::vector<int> memoria;
    
public:
    GestorMemoria(int tamano) : tamanoMemoria(tamano), memoria(tamano, -1) {
        //Inicializar la memoria con valores negativos (-1) para indicar que esta vacia
    }
    
    //Implementación del algoritmo First-fit para asignar memoria
    bool asignarMemoriaFirstFit(int procesoID, int tamano, int* listParticiones, int numParticiones, int* listParticionesInicial){
        bool ans = false;
        int i = 0;
        int ubicacion = -1;
        int posicion_actual = 0;
        //Se revisa el primer segmento donde se pueda almacenar el proceso
        while (i < numParticiones - 1 and ans == false){
            if(tamano <= listParticiones[i]){
                ans = true;
                ubicacion = i;
            }
            i++;
        }
        if (ubicacion != -1) {
            if (ubicacion == 0) {
                posicion_actual = listParticionesInicial[ubicacion] - listParticiones[ubicacion];
            } else {
                int sum = 0;
                for (int j = 0; j < ubicacion; j++){
                    sum += listParticionesInicial[j];
                }
                posicion_actual = sum + (listParticionesInicial[ubicacion] - listParticiones[ubicacion]);
            }
            // Se asigna el ID del proceso al espacio correspondiente de la memoria
            for (int j = posicion_actual; j < posicion_actual + tamano; j++) {
                memoria[j] = procesoID;
            }
            listParticiones[ubicacion] = listParticiones[ubicacion] - tamano;
        }
        return ans;
    }
    
    //Encontrar los espacios de memoria con menor a mayor tamaño para Best Fit
    // Definición de un par (valor, posición)
    using ValorPosicion = std::pair<int, int>;
    // Función para ordenar un vector y obtener las posiciones originales
    std::vector<int> ordenarVectorMenorAMayor(const std::vector<int>& inputVector, std::vector<int>& posiciones) {
        // Crear un vector de pares (valor, posición)
        std::vector<ValorPosicion> vectorConPosiciones;
        for (int i = 0; i < inputVector.size(); ++i) {
            vectorConPosiciones.push_back({inputVector[i], i});
        }
        // Ordenar el vector de pares basándose en los valores
        std::sort(vectorConPosiciones.begin(), vectorConPosiciones.end(),
                  [](const ValorPosicion& a, const ValorPosicion& b) {
                      return a.first < b.first;
                  });
        // Extraer los valores ordenados y las posiciones originales
        std::vector<int> vectorOrdenado;
        posiciones.clear(); // Limpiar el vector de posiciones
        for (const auto& par : vectorConPosiciones) {
            vectorOrdenado.push_back(par.first);
            posiciones.push_back(par.second);
        }
        return vectorOrdenado;
    }
    //Encontrar los espacios de memoria con mayor a menor tamaño para Best Fit
    std::vector<int> ordenarVectorMayoraMenor(const std::vector<int>& inputVector, std::vector<int>& posiciones) {
        std::vector<ValorPosicion> vectorConPosiciones;

        for (int i = 0; i < inputVector.size(); ++i) {
            vectorConPosiciones.push_back({inputVector[i], i});
        }

        // Cambiando la función de comparación para ordenar de mayor a menor
        std::sort(vectorConPosiciones.begin(), vectorConPosiciones.end(),
                  [](const ValorPosicion& a, const ValorPosicion& b) {
                      return a.first > b.first; // Cambiado a '>' para ordenar de mayor a menor
                  });

        std::vector<int> vectorOrdenado;
        posiciones.clear();

        for (const auto& par : vectorConPosiciones) {
            vectorOrdenado.push_back(par.first);
            posiciones.push_back(par.second);
        }

        return vectorOrdenado;
    }
    
    bool asignarMemoriaBestFit(int procesoID, int tamano, int* listParticiones, int numParticiones, int* listParticionesInicial) {
        bool ans = false;
        std::vector<int> particiones(listParticiones, listParticiones + numParticiones - 1);
        std::vector<int> posicionesOriginales;
        // Llamar a la función para ordenar el vector y obtener las posiciones de las posiciones
        // de menor a mayor espacio en la memoria
        std::vector<int> vectorOrdenado = ordenarVectorMenorAMayor(particiones, posicionesOriginales);
        int i = 0;
        int ubicacion = -1;  // Inicializar con un valor que indique que no se ha encontrado ubicación
        // Se revisa el segmento más pequeño donde se pueda almacenar el proceso
        while (i < numParticiones - 1 && !ans) {
            if (tamano <= listParticiones[posicionesOriginales[i]]) {
                ans = true;
                ubicacion = posicionesOriginales[i];
            }
            i++;
        }
        // Indica donde inicia el segmento donde se guardará el proceso
        int posicion_actual = 0;
        if (ubicacion != -1) {
            if (ubicacion == 0) {
                posicion_actual = listParticionesInicial[ubicacion] - listParticiones[ubicacion];
            } else {
                int sum = 0;
                for (int j = 0; j < ubicacion; j++){
                    sum += listParticionesInicial[j];
                }
                posicion_actual = sum + (listParticionesInicial[ubicacion] - listParticiones[ubicacion]);
            }
            // Se asigna el ID del proceso al espacio correspondiente de la memoria
            for (int j = posicion_actual; j < posicion_actual + tamano; j++) {
                memoria[j] = procesoID;
            }
            listParticiones[ubicacion] = listParticiones[ubicacion] - tamano;
        }
        return ans;
    }

    
    //worst fit
    bool asignarMemoriaWorstFit(int procesoID, int tamano, int* listParticiones, int numParticiones, int* listParticionesInicial){
        bool ans = false;
        std::vector<int> particiones(listParticiones, listParticiones + numParticiones - 1);
        std::vector<int> posicionesOriginales;
        // Llamar a la función para ordenar el vector y obtener las posiciones de las posiciones
        // de menor a mayor espacio en la memoria
        std::vector<int> vectorOrdenado = ordenarVectorMayoraMenor(particiones, posicionesOriginales);
        int ubicacion = -1;  // Inicializar con un valor que indique que no se ha encontrado ubicación
        // Se revisa el primer segmento más grande verificando si se puede gardar el proceso
        if (tamano <= listParticiones[posicionesOriginales[0]]) {
            ans = true;
            ubicacion = posicionesOriginales[0];
        }
        // Indica donde inicia el segmento donde se guardará el proceso
        int posicion_actual = 0;
        if (ubicacion != -1) {
            if (ubicacion == 0) {
                posicion_actual = listParticionesInicial[ubicacion] - listParticiones[ubicacion];
            } else {
                int sum = 0;
                for (int j = 0; j < ubicacion; j++){
                    sum += listParticionesInicial[j];
                }
                posicion_actual = sum + (listParticionesInicial[ubicacion] - listParticiones[ubicacion]);
            }
            // Se asigna el ID del proceso al espacio correspondiente de la memoria
            for (int j = posicion_actual; j < posicion_actual + tamano; j++) {
                memoria[j] = procesoID;
            }
            listParticiones[ubicacion] = listParticiones[ubicacion] - tamano;
        }
        return ans;
    }
    
    void liberarMemoria(int procesoID, int* listParticiones, int numParticiones, int* listParticionesInicial){
        int sum = 0;
        int ubicacion = 0;
        for(int i = 0; i < tamanoMemoria; i++){
            if (memoria[i] == procesoID){
                memoria[i] = -1; //Liberar el bloque de memoria
                sum += 1;
                ubicacion = i;
            }
        }
        //En la lista donde se encuentran los espacios disponibles en memoria,
        //se le debe sumar el valor que se acaba de liberar
        ubicacion = ubicacion - sum + 2;
        int posicionInicio = 0;
        int posicionFinal = 0;
        for (int i = 0; i < numParticiones - 1; i++){
            posicionFinal += listParticionesInicial[i];
            posicionInicio = posicionFinal - listParticionesInicial[i];
            if (ubicacion >=  posicionInicio and ubicacion <= posicionFinal){
                listParticiones[i] += sum;
            }
        }
    }
    
    void imprimirEstadoMemoria(){
        std::cout <<"Estado de la Memoria: ";
        for(int i = 0; i < tamanoMemoria; i++){
            std::cout << memoria[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int particiones = 5;
    int tamanoMemoria = 68; //Tamano de la memoria
    GestorMemoria gestor(tamanoMemoria);
    int listParticionesInicial[] = {10, 25, 18, 15};
    int listParticiones[] = {10, 25, 18, 15};
    
    if (gestor.asignarMemoriaBestFit(1, 20, listParticiones, particiones, listParticionesInicial)){
        std::cout << "Asignado proceso 1 de tamaño 20" << std::endl;
    }
    gestor.imprimirEstadoMemoria();
    
    if (gestor.asignarMemoriaBestFit(2, 3, listParticiones, particiones, listParticionesInicial)){
        std::cout << "Asignado proceso 2 de tamaño 3" << std::endl;
    }
    gestor.imprimirEstadoMemoria();
    
    if (gestor.asignarMemoriaBestFit(3, 15, listParticiones, particiones, listParticionesInicial)){
        std::cout << "Asignado proceso 3 de tamaño 15" << std::endl;
    }
    gestor.imprimirEstadoMemoria();
    
    if (gestor.asignarMemoriaBestFit(4, 10, listParticiones, particiones, listParticionesInicial)){
        std::cout << "Asignado proceso 4 de tamaño 10" << std::endl;
    }
    gestor.imprimirEstadoMemoria();
    
    if (gestor.asignarMemoriaBestFit(5, 19, listParticiones, particiones, listParticionesInicial)){
        std::cout << "Asignado proceso 5 de tamaño 19" << std::endl;
    }
    else {std::cout << "No se pudo asignar" << std::endl;}
    gestor.imprimirEstadoMemoria();
    
    gestor.liberarMemoria(4, listParticiones, particiones, listParticionesInicial);
    std::cout << "Proceso 4 liberado" << std::endl;
    
    if (gestor.asignarMemoriaBestFit(6, 9, listParticiones, particiones, listParticionesInicial)){
        std::cout << "Asignado proceso 6 de tamaño 9" << std::endl;
    }
    
    gestor.imprimirEstadoMemoria();
    return 0;
}
