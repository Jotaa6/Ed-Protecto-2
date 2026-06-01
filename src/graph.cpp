/*
 * Archivo: graph.cpp
 * Descripcion: Implementacion del grafo con lista de adyacencia y matriz dinamica
 * Estructuras: Arco, Vertice
 * Funciones: insertarVertice, insertarArco, buscarVertice, eliminarVertice,
 *            eliminarArco, actualizarCostoArco, desmarcarVertices,
 *            cargarMatrizAdyacencia, imprimirGrafo
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/graph.h"

Vertice* grafo      = nullptr;
float**  adjMatrix  = nullptr;
int      matrixSize = 0;

/**
 * @brief  Busca un vertice en el grafo global por su galaxyId string
 * @param  galaxyId  id string a buscar
 * @return puntero al Vertice si se encuentra, nullptr si no existe
 */
Vertice* buscarVertice(string galaxyId) {
    Vertice* temp = grafo;
    while (temp != nullptr) {
        if (temp->galaxyId == galaxyId) return temp;
        temp = temp->sigV;
    }
    return nullptr;
}

/**
 * @brief  Inserta un nuevo vertice en el grafo global
 * @param  galaxyId  id string de la galaxia
 * @param  nombre    nombre de la galaxia
 * @return void
 */
void insertarVertice(string galaxyId, string nombre) {
    if (buscarVertice(galaxyId) != nullptr) return;

    Vertice* nuevo       = new Vertice();
    nuevo->galaxyId      = galaxyId;
    nuevo->nombre        = nombre;
    nuevo->visitado      = false;
    nuevo->subListaArcos = nullptr;
    nuevo->sigV          = grafo;
    grafo                = nuevo;
}

/**
 * @brief  Inserta un arco dirigido de origen a destino
 * @param  origenId   id string origen
 * @param  destinoId  id string destino
 * @param  costo      costo float del arco
 * @return void
 */
void insertarArco(string origenId, string destinoId, float costo) {
    Vertice* origen = buscarVertice(origenId);
    if (origen == nullptr) {
        cout << "Error: vertice origen " << origenId << " no encontrado." << endl;
        return;
    }

    Arco* nuevoArco       = new Arco();
    nuevoArco->destinoId  = destinoId;
    nuevoArco->costo      = costo;
    nuevoArco->sigA       = origen->subListaArcos;
    origen->subListaArcos = nuevoArco;
}

/**
 * @brief  Elimina un vertice y todos sus arcos incluyendo arcos entrantes
 * @param  galaxyId  id string del vertice a eliminar
 * @return void
 */
void eliminarVertice(string galaxyId) {
    // Eliminar arcos entrantes desde otros vertices
    Vertice* temp = grafo;
    while (temp != nullptr) {
        if (temp->galaxyId != galaxyId) {
            Arco* arco     = temp->subListaArcos;
            Arco* anterior = nullptr;
            while (arco != nullptr) {
                if (arco->destinoId == galaxyId) {
                    if (anterior == nullptr)
                        temp->subListaArcos = arco->sigA;
                    else
                        anterior->sigA = arco->sigA;
                    Arco* aEliminar = arco;
                    arco = arco->sigA;
                    delete aEliminar;
                } else {
                    anterior = arco;
                    arco     = arco->sigA;
                }
            }
        }
        temp = temp->sigV;
    }

    // Eliminar el vertice y sus arcos salientes
    Vertice* actual   = grafo;
    Vertice* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->galaxyId == galaxyId) {
            Arco* arco = actual->subListaArcos;
            while (arco != nullptr) {
                Arco* sig = arco->sigA;
                delete arco;
                arco = sig;
            }
            if (anterior == nullptr) grafo = actual->sigV;
            else anterior->sigV = actual->sigV;
            delete actual;
            return;
        }
        anterior = actual;
        actual   = actual->sigV;
    }
    cout << "Vertice " << galaxyId << " no encontrado." << endl;
}

/**
 * @brief  Elimina el arco de origen a destino
 * @param  origenId   id string origen
 * @param  destinoId  id string destino
 * @return void
 */
void eliminarArco(string origenId, string destinoId) {
    Vertice* origen = buscarVertice(origenId);
    if (origen == nullptr) {
        cout << "Vertice origen " << origenId << " no encontrado." << endl;
        return;
    }

    Arco* actual   = origen->subListaArcos;
    Arco* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->destinoId == destinoId) {
            if (anterior == nullptr) origen->subListaArcos = actual->sigA;
            else anterior->sigA = actual->sigA;
            delete actual;
            return;
        }
        anterior = actual;
        actual   = actual->sigA;
    }
    cout << "Arco " << origenId << " -> " << destinoId << " no encontrado." << endl;
}

/**
 * @brief  Actualiza el costo del arco de origen a destino
 * @param  origenId    id string origen
 * @param  destinoId   id string destino
 * @param  nuevoCosto  nuevo costo float
 * @return void
 */
void actualizarCostoArco(string origenId, string destinoId, float nuevoCosto) {
    Vertice* origen = buscarVertice(origenId);
    if (origen == nullptr) {
        cout << "Vertice origen " << origenId << " no encontrado." << endl;
        return;
    }

    Arco* arco = origen->subListaArcos;
    while (arco != nullptr) {
        if (arco->destinoId == destinoId) {
            arco->costo = nuevoCosto;
            return;
        }
        arco = arco->sigA;
    }
    cout << "Arco " << origenId << " -> " << destinoId << " no encontrado." << endl;
}

/**
 * @brief  Resetea visitado = false en todos los vertices
 * @return void
 */
void desmarcarVertices() {
    Vertice* temp = grafo;
    while (temp != nullptr) {
        temp->visitado = false;
        temp           = temp->sigV;
    }
}

/**
 * @brief  Carga la matriz de adyacencia desde arreglo 2D dinamico float**
 * @param  matrix  arreglo 2D float** fuente
 * @param  size    numero de filas y columnas
 * @return void
 */
void cargarMatrizAdyacencia(float** matrix, int size) {
    if (adjMatrix != nullptr) {
        for (int i = 0; i < matrixSize; i++) delete[] adjMatrix[i];
        delete[] adjMatrix;
    }
    matrixSize = size;
    adjMatrix  = new float*[size];
    for (int i = 0; i < size; i++) {
        adjMatrix[i] = new float[size];
        for (int j = 0; j < size; j++)
            adjMatrix[i][j] = matrix[i][j];
    }
}

/**
 * @brief  Imprime el grafo completo en terminal para verificacion
 * @return void
 */
void imprimirGrafo() {
    Vertice* temp = grafo;
    cout << "\n=== Grafo ===" << endl;
    while (temp != nullptr) {
        cout << "Vertice: " << temp->nombre
             << " (ID: " << temp->galaxyId << ")" << endl;
        Arco* arco = temp->subListaArcos;
        while (arco != nullptr) {
            cout << "  -> " << arco->destinoId
                 << " | Costo: " << arco->costo << endl;
            arco = arco->sigA;
        }
        temp = temp->sigV;
    }
}
