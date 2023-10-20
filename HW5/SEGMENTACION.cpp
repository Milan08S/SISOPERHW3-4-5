#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

// Estructura para representar un segmento de memoria
struct Segmento {
    int id;          // Identificador único del segmento
    int base;        // Dirección base del segmento
    int limite;      // Límite del segmento
    bool ocupado;    // Estado del segmento: true si está ocupado, false si está libre

    Segmento(int id_, int base_, int limite_) : id(id_), base(base_), limite(limite_), ocupado(false) {}
};

// Estructura para representar un proceso
struct Proceso {
    int id;           // Identificador único del proceso
    int tamaño;       // Tamaño total del proceso en bytes

    Proceso(int id_, int tamaño_) : id(id_), tamaño(tamaño_) {}
};

class SimuladorSegmentacion {
private:
    int tamañoMemoria;
    std::vector<Segmento> segmentos;

public:
    SimuladorSegmentacion(int tamaño) : tamañoMemoria(tamaño) {}

    void agregarSegmento(int id, int base, int limite) {
        Segmento nuevoSegmento(id, base, limite);
        segmentos.push_back(nuevoSegmento);
    }

    bool asignarMemoria(Proceso proceso) {
        for (auto& segmento : segmentos) {
            if (!segmento.ocupado && segmento.limite >= proceso.tamaño) {
                segmento.ocupado = true;
                std::cout << "Proceso " << proceso.id << " asignado al segmento " << segmento.id << "\n" << std::endl;
                return true;
            }
        }
        std::cout << "No hay suficiente espacio para asignar el proceso " << proceso.id << std::endl;
        return false;
    }

    void liberarMemoria(int procesoID) {
        for (auto& segmento : segmentos) {
            if (segmento.ocupado && segmento.id == procesoID) {
                segmento.ocupado = false;
                std::cout << "Proceso " << procesoID << " liberado del segmento " << segmento.id << "\n" << std::endl;
                return;
            }
        }
        std::cout << "No se encontró un segmento ocupado asociado al proceso " << procesoID << std::endl;
    }

    void imprimirEstadoMemoria() {
        std::cout << "Estado de la memoria segmentada:" << std::endl;
        for (const Segmento& segmento : segmentos) {
            std::cout << "Segmento ID: " << segmento.id << ", Base: " << segmento.base << ", Límite: " << segmento.limite << ", Estado: ";
            if (segmento.ocupado) {
                std::cout << "Ocupado";
            } else {
                std::cout << "Libre";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
  int tamañoMemoria = 100;
  SimuladorSegmentacion simulador(tamañoMemoria);
  std::queue<int> Seg;

  // Agregar segmentos a la memoria
  simulador.agregarSegmento(1, 0, 30);
  simulador.agregarSegmento(2, 31, 50);
  simulador.agregarSegmento(3, 51, 80);
  Seg.push(1);
  Seg.push(2);
  Seg.push(3);

  // Crear procesos
  Proceso proceso1(1, 30);
  Proceso proceso2(2, 40);
  Proceso proceso3(3, 15);
  Proceso proceso4(4, 25);
  Proceso proceso5(5, 35);

  std::vector<Proceso> Procesos;
  Procesos.push_back(proceso1);
  Procesos.push_back(proceso2);
  Procesos.push_back(proceso3);
  Procesos.push_back(proceso4);
  Procesos.push_back(proceso5);

  simulador.imprimirEstadoMemoria();
  std::cout <<"\n" << std::endl;
  for ( int i = 0; i < Procesos.size(); i++) {
    int ans = simulador.asignarMemoria(Procesos[i]);
    simulador.imprimirEstadoMemoria();
    std::cout <<"\n" << std::endl;
    if (ans == false) {
      int Seg_eliminado = Seg.front();
      simulador.liberarMemoria(Seg_eliminado);
      simulador.asignarMemoria(Procesos[i]);
      simulador.imprimirEstadoMemoria();
      std::cout <<"\n" << std::endl;
      Seg.pop();
      Seg.push(Seg_eliminado);
      
    }
  }
  simulador.imprimirEstadoMemoria();

  return 0;
}
