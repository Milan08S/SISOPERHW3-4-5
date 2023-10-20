#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

class Reader {
public:
  int lectura(int posicion) {
    std::string nombreArchivo = "archivo.txt";
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    int i = 0;
    if (archivo.fail()) {
      std::cout << "No se pudo abrir el archivo" << std::endl;
      exit(1);
    }
    while (!archivo.eof()) {
      std::getline(archivo, linea);
      if (posicion == i) {
        archivo.close();         // Cerrar el archivo después de leer
        return std::stoi(linea); // Convertir la línea a entero y devolverlo
      }
      i++;
    }
    archivo.close();
    return -1;
  }

  int cantidadProcesos(int posicion) {
    std::string nombreArchivo = "archivo.txt";
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    int i = 0;
    if (archivo.fail()) {
      std::cout << "No se pudo abrir el archivo" << std::endl;
      exit(1);
    }
    while (!archivo.eof()) {
      std::getline(archivo, linea);
      i++;
    }
    archivo.close(); // Cerrar el archivo después de leer
    int ans = i - posicion;
    return ans;
  }

  std::vector<int> lecturaVectores(int posicion) {
    std::string nombreArchivo = "archivo.txt";
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    int i = 0;
    if (archivo.fail()) {
      std::cout << "No se pudo abrir el archivo" << std::endl;
      exit(1);
    }
    while (std::getline(archivo, linea)) {
      if (posicion == i) {
        archivo.close(); // Cerrar el archivo después de leer

        // Procesar la línea para obtener un vector de enteros
        std::vector<int> resultado;
        std::istringstream iss(linea);
        int valor;
        char coma; // Para capturar las comas entre los valores
        while (iss >> valor) {
          resultado.push_back(valor);
          iss >> coma; // Leer la coma
        }
        return resultado;
      }
      i++;
    }
    archivo.close();
    return {}; // Devolver un vector vacío si no se encuentra la posición
  }
};

class GestorMemoria {
private:
  int tamanoMemoria;
  std::vector<int> memoria;

public:
  GestorMemoria(int tamano) : tamanoMemoria(tamano), memoria(tamano, -1) {
    // Inicializar la memoria con valores negativos (-1) para indicar que esta
    // vacia
  }

  // Implementación del algoritmo First-fit para asignar memoria
  bool asignarMemoriaFirstFit(int procesoID, int tamano, int *listParticiones,
                              int numParticiones, int *listParticionesInicial) {
    bool ans = false;
    int i = 0;
    int ubicacion = -1;
    int posicion_actual = 0;
    // Se revisa el primer segmento donde se pueda almacenar el proceso
    while (i < numParticiones - 1 && ans == false) {
      if (tamano <= listParticiones[i]) {
        ans = true;
        ubicacion = i;
      }
      i++;
    }
    if (ubicacion != -1) {
      if (ubicacion == 0) {
        posicion_actual =
            listParticionesInicial[ubicacion] - listParticiones[ubicacion];
      } else {
        int sum = 0;
        for (int j = 0; j < ubicacion; j++) {
          sum += listParticionesInicial[j];
        }
        posicion_actual = sum + (listParticionesInicial[ubicacion] -
                                 listParticiones[ubicacion]);
      }
      // Se asigna el ID del proceso al espacio correspondiente de la memoria
      for (int j = posicion_actual; j < posicion_actual + tamano; j++) {
        memoria[j] = procesoID;
      }
      listParticiones[ubicacion] = listParticiones[ubicacion] - tamano;
    }
    return ans;
  }

  // Encontrar los espacios de memoria con menor a mayor tamaño para Best Fit
  //  Definición de un par (valor, posición)
  using ValorPosicion = std::pair<int, int>;
  // Función para ordenar un vector y obtener las posiciones originales
  std::vector<int> ordenarVectorMenorAMayor(const std::vector<int> &inputVector,
                                            std::vector<int> &posiciones) {
    // Crear un vector de pares (valor, posición)
    std::vector<ValorPosicion> vectorConPosiciones;
    for (int i = 0; i < inputVector.size(); ++i) {
      vectorConPosiciones.push_back({inputVector[i], i});
    }
    // Ordenar el vector de pares basándose en los valores
    std::sort(vectorConPosiciones.begin(), vectorConPosiciones.end(),
              [](const ValorPosicion &a, const ValorPosicion &b) {
                return a.first < b.first;
              });
    // Extraer los valores ordenados y las posiciones originales
    std::vector<int> vectorOrdenado;
    posiciones.clear(); // Limpiar el vector de posiciones
    for (const auto &par : vectorConPosiciones) {
      vectorOrdenado.push_back(par.first);
      posiciones.push_back(par.second);
    }
    return vectorOrdenado;
  }
  // Encontrar los espacios de memoria con mayor a menor tamaño para Best Fit
  std::vector<int> ordenarVectorMayoraMenor(const std::vector<int> &inputVector,
                                            std::vector<int> &posiciones) {
    std::vector<ValorPosicion> vectorConPosiciones;

    for (int i = 0; i < inputVector.size(); ++i) {
      vectorConPosiciones.push_back({inputVector[i], i});
    }

    // Cambiando la función de comparación para ordenar de mayor a menor
    std::sort(vectorConPosiciones.begin(), vectorConPosiciones.end(),
              [](const ValorPosicion &a, const ValorPosicion &b) {
                return a.first >
                       b.first; // Cambiado a '>' para ordenar de mayor a menor
              });

    std::vector<int> vectorOrdenado;
    posiciones.clear();

    for (const auto &par : vectorConPosiciones) {
      vectorOrdenado.push_back(par.first);
      posiciones.push_back(par.second);
    }

    return vectorOrdenado;
  }

  bool asignarMemoriaBestFit(int procesoID, int tamano, int *listParticiones,
                             int numParticiones, int *listParticionesInicial) {
    bool ans = false;
    std::vector<int> particiones(listParticiones,
                                 listParticiones + numParticiones - 1);
    std::vector<int> posicionesOriginales;
    // Llamar a la función para ordenar el vector y obtener las posiciones de
    // las posiciones de menor a mayor espacio en la memoria
    std::vector<int> vectorOrdenado =
        ordenarVectorMenorAMayor(particiones, posicionesOriginales);
    int i = 0;
    int ubicacion = -1; // Inicializar con un valor que indique que no se ha
                        // encontrado ubicación
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
        posicion_actual =
            listParticionesInicial[ubicacion] - listParticiones[ubicacion];
      } else {
        int sum = 0;
        for (int j = 0; j < ubicacion; j++) {
          sum += listParticionesInicial[j];
        }
        posicion_actual = sum + (listParticionesInicial[ubicacion] -
                                 listParticiones[ubicacion]);
      }
      // Se asigna el ID del proceso al espacio correspondiente de la memoria
      for (int j = posicion_actual; j < posicion_actual + tamano; j++) {
        memoria[j] = procesoID;
      }
      listParticiones[ubicacion] = listParticiones[ubicacion] - tamano;
    }
    return ans;
  }

  // worst fit
  bool asignarMemoriaWorstFit(int procesoID, int tamano, int *listParticiones,
                              int numParticiones, int *listParticionesInicial) {
    bool ans = false;
    std::vector<int> particiones(listParticiones,
                                 listParticiones + numParticiones - 1);
    std::vector<int> posicionesOriginales;
    // Llamar a la función para ordenar el vector y obtener las posiciones de
    // las posiciones de menor a mayor espacio en la memoria
    std::vector<int> vectorOrdenado =
        ordenarVectorMayoraMenor(particiones, posicionesOriginales);
    int ubicacion = -1; // Inicializar con un valor que indique que no se ha
                        // encontrado ubicación
    // Se revisa el primer segmento más grande verificando si se puede gardar el
    // proceso
    if (tamano <= listParticiones[posicionesOriginales[0]]) {
      ans = true;
      ubicacion = posicionesOriginales[0];
    }
    // Indica donde inicia el segmento donde se guardará el proceso
    int posicion_actual = 0;
    if (ubicacion != -1) {
      if (ubicacion == 0) {
        posicion_actual =
            listParticionesInicial[ubicacion] - listParticiones[ubicacion];
      } else {
        int sum = 0;
        for (int j = 0; j < ubicacion; j++) {
          sum += listParticionesInicial[j];
        }
        posicion_actual = sum + (listParticionesInicial[ubicacion] -
                                 listParticiones[ubicacion]);
      }
      // Se asigna el ID del proceso al espacio correspondiente de la memoria
      for (int j = posicion_actual; j < posicion_actual + tamano; j++) {
        memoria[j] = procesoID;
      }
      listParticiones[ubicacion] = listParticiones[ubicacion] - tamano;
    }
    return ans;
  }

  void liberarMemoria(int procesoID, int *listParticiones, int numParticiones,
                      int *listParticionesInicial) {
    int sum = 0;
    int ubicacion = 0;
    for (int i = 0; i < tamanoMemoria; i++) {
      if (memoria[i] == procesoID) {
        memoria[i] = -1; // Liberar el bloque de memoria
        sum += 1;
        ubicacion = i;
      }
    }
    // En la lista donde se encuentran los espacios disponibles en memoria,
    // se le debe sumar el valor que se acaba de liberar
    ubicacion = ubicacion - sum + 2;
    int posicionInicio = 0;
    int posicionFinal = 0;
    for (int i = 0; i < numParticiones - 1; i++) {
      posicionFinal += listParticionesInicial[i];
      posicionInicio = posicionFinal - listParticionesInicial[i];
      if (ubicacion >= posicionInicio && ubicacion <= posicionFinal) {
        listParticiones[i] += sum;
      }
    }
  }

  void imprimirEstadoMemoria() {
    std::cout << "Estado de la Memoria: ";
    for (int i = 0; i < tamanoMemoria; i++) {
      std::cout << memoria[i] << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  Reader reader;
  int particiones = reader.lectura(1);
  int tamanoMemoria = reader.lectura(0); // Tamaño de la memoria
  int algoritmo = reader.lectura(3);
  GestorMemoria gestor(tamanoMemoria);
  int cantidadProcesos = reader.cantidadProcesos(4);
  std::vector<int> listParticionesInicial = reader.lecturaVectores(2);
  std::vector<int> listParticiones = reader.lecturaVectores(2);

  // Convertir vectores a punteros
  int *ptrListParticionesInicial = listParticionesInicial.data();
  int *ptrListParticiones = listParticiones.data();

  for (int i = 0; i < cantidadProcesos; i++) {
    std::vector<int> proceso = reader.lecturaVectores(i + 4);
    int procesoID = proceso[0];
    int tamanoProceso = proceso[1];
    switch (algoritmo) {
    case 1:
      if (gestor.asignarMemoriaFirstFit(procesoID, tamanoProceso,
                                        ptrListParticiones, particiones,
                                        ptrListParticionesInicial)) {
        std::cout << "Asignado proceso " << procesoID << " de tamaño "
                  << tamanoProceso << std::endl;
        gestor.imprimirEstadoMemoria();
      } else {
        std::cout << "No se pudo asignar" << std::endl;
      }
      break;
    case 2:
      if (gestor.asignarMemoriaBestFit(procesoID, tamanoProceso,
                                       ptrListParticiones, particiones,
                                       ptrListParticionesInicial)) {
        std::cout << "Asignado proceso " << procesoID << " de tamaño "
                  << tamanoProceso << std::endl;
        gestor.imprimirEstadoMemoria();
      } else {
        std::cout << "No se pudo asignar" << std::endl;
      }
      break;
    case 3:
      if (gestor.asignarMemoriaWorstFit(procesoID, tamanoProceso,
                                        ptrListParticiones, particiones,
                                        ptrListParticionesInicial)) {
        std::cout << "Asignado proceso " << procesoID << " de tamaño "
                  << tamanoProceso << std::endl;
        gestor.imprimirEstadoMemoria();
      } else {
        std::cout << "No se pudo asignar" << std::endl;
      }
    default:
      std::cout << "El numero ingresado no tiene un algoritmo" << std::endl;
    }
  }
  return 0;
}
