#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

struct Pagina {
  int idproceso; // ID del proceso que pertenece la página (-1 si está vacía)
  bool ocupada;  // Indica si la página está ocupada o libre

  Pagina() : idproceso(-1), ocupada(false) {}
};

struct Proceso {
  int id;
  int tamaño;
  std::vector<int> paginasAsignadas;
};

class SimuladorPaginacion {
private:
  int tamañoMemoria;
  int tamañoPagina;
  std::vector<Pagina> memoriaPaginada;
  std::vector<Proceso> procesos;

public:
  SimuladorPaginacion(int tamaño, int tamañoPag) : tamañoMemoria(tamaño), tamañoPagina(tamañoPag) {
    // Inicializar la memoria con páginas vacías
    int numPaginas = tamañoMemoria / tamañoPagina;
    memoriaPaginada.resize(numPaginas);
  }

  bool asignarMemoriaPaginas(Proceso& proceso) {
    int paginasNecesarias = proceso.tamaño / tamañoPagina + (proceso.tamaño % tamañoPagina != 0);

    // Buscar páginas libres para asignar al proceso
    for (int i = 0; i < memoriaPaginada.size(); i++) {
      if (paginasNecesarias == 0) {
        break;
      }

      if (!memoriaPaginada[i].ocupada) {
        memoriaPaginada[i].idproceso = proceso.id;
        proceso.paginasAsignadas.push_back(i);
        memoriaPaginada[i].ocupada = true; // Marcar la página como ocupada
        paginasNecesarias--;
      }
    }

    if (paginasNecesarias > 0) {
      std::cout << "No hay suficiente espacio en la memoria para asignar el proceso " << proceso.id << std::endl;
      return false;
    } else {
      std::cout << "Proceso " << proceso.id << " asignado a las páginas: ";
      for (int pagina : proceso.paginasAsignadas) {
        std::cout << pagina << " ";
      }
      std::cout << std::endl;
    }
    return true;
  }

  void liberarMemoriaPaginas(Proceso& proceso) {
    for (int pagina : proceso.paginasAsignadas) {
      memoriaPaginada[pagina].idproceso = -1;
      memoriaPaginada[pagina].ocupada = false; // Marcar la página como libre
    }
    
    proceso.paginasAsignadas.clear();

    std::cout << "Proceso " << proceso.id << " liberado de la memoria\n" << std::endl;
  }

  void imprimirEstadoMemoriaPaginada() {
    std::cout << "Estado de la memoria paginada:" << std::endl;
    for (int i = 0; i < memoriaPaginada.size(); i++) {
      if (!memoriaPaginada[i].ocupada) {
        std::cout << "Página " << i << ": Libre" << std::endl;
      } else {
        std::cout << "Página " << i << ": Proceso " << memoriaPaginada[i].idproceso << std::endl;
      }
    }
  }
};

int main() {
  int tamañoMemoria = 100;
  int tamañoPagina = 10;
  SimuladorPaginacion simulador(tamañoMemoria, tamañoPagina);

  Proceso proceso1 = {1, 30, {}};
  Proceso proceso2 = {2, 40, {}};
  Proceso proceso3 = {3, 15, {}};
  Proceso proceso4 = {4, 25, {}};
  Proceso proceso5 = {5, 35, {}};

  std::vector<Proceso> Procesos;
  Procesos.push_back(proceso1);
  Procesos.push_back(proceso2);
  Procesos.push_back(proceso3);
  Procesos.push_back(proceso4);
  Procesos.push_back(proceso5);

  simulador.imprimirEstadoMemoriaPaginada();
  std::cout <<"\n" << std::endl;
  int j = 0;
  for ( int i = 0; i < Procesos.size(); i++) {
    int ans = simulador.asignarMemoriaPaginas(Procesos[i]);
    simulador.imprimirEstadoMemoriaPaginada();
    std::cout <<"\n" << std::endl;
    if (ans == false) {
      simulador.liberarMemoriaPaginas(Procesos[j]);
      simulador.asignarMemoriaPaginas(Procesos[i]);
      j += 1;

    }
  }
  simulador.imprimirEstadoMemoriaPaginada();

  return 0;
}
