/*
 * Archivo: graph.cpp
 * Descripcion: Implementacion del grafo con lista de adyacencia y matriz de adyacencia dinamica
 * Estructuras: Arco, Vertice
 * Funciones: insertarVertice, insertarArco, buscarVertice, eliminarVertice,
 *            eliminarArco, actualizarCostoArco, desmarcarVertices,
 *            cargarMatrizAdyacencia, imprimirGrafo
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/graph.h"

// Variables globales
Vertice* grafo      = nullptr;
int**    adjMatrix  = nullptr;
int      matrixSize = 0;

/**
 * @brief  Busca un vertice en el grafo global por su galaxyId
 * @param  galaxyId  id de la galaxia a buscar
 * @return puntero al Vertice si se encuentra, nullptr si no existe
 */
Vertice* buscarVertice(int galaxyId) {
    Vertice* temp = grafo;
    while (temp != nullptr) {
        if (temp->galaxyId == galaxyId)
            return temp;
        temp = temp->sigV;
    }
    return nullptr;
}

/**
 * @brief  Inserta un nuevo vertice en el grafo global
 *         No hace nada si ya existe un vertice con el mismo galaxyId
 * @param  galaxyId  id de la galaxia a insertar
 * @param  nombre    nombre de la galaxia
 * @return void
 */
void insertarVertice(int galaxyId, string nombre) {
    if (buscarVertice(galaxyId) != nullptr)
        return;

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
 *         Actualiza tanto la lista de adyacencia como adjMatrix[][]
 * @param  origenId   id de la galaxia origen
 * @param  destinoId  id de la galaxia destino
 * @param  costo      costo del arco
 * @return void
 */
void insertarArco(int origenId, int destinoId, int costo) {
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

    if (adjMatrix != nullptr &&
        origenId < matrixSize && destinoId < matrixSize)
        adjMatrix[origenId][destinoId] = costo;
}

/**
 * @brief  Elimina un vertice y todos sus arcos del grafo global
 *         Elimina tambien los arcos entrantes desde otros vertices
 *         para evitar arcos colgando apuntando a un vertice inexistente
 *         Actualiza tanto la lista de adyacencia como adjMatrix[][]
 * @param  galaxyId  id del vertice a eliminar
 * @return void
 */
void eliminarVertice(int galaxyId) {
    // Primero eliminar arcos entrantes desde todos los demas vertices
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
                    arco            = arco->sigA;
                    delete aEliminar;
                } else {
                    anterior = arco;
                    arco     = arco->sigA;
                }
            }
        }
        temp = temp->sigV;
    }

    // Luego eliminar el vertice y sus arcos salientes
    Vertice* actual   = grafo;
    Vertice* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->galaxyId == galaxyId) {
            Arco* arco = actual->subListaArcos;
            while (arco != nullptr) {
                Arco* sigArco = arco->sigA;
                delete arco;
                arco = sigArco;
            }

            if (adjMatrix != nullptr && galaxyId < matrixSize) {
                for (int i = 0; i < matrixSize; i++) {
                    adjMatrix[galaxyId][i] = 0;
                    adjMatrix[i][galaxyId] = 0;
                }
            }

            if (anterior == nullptr)
                grafo = actual->sigV;
            else
                anterior->sigV = actual->sigV;

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
 *         Actualiza tanto la lista de adyacencia como adjMatrix[][]
 * @param  origenId   id de la galaxia origen
 * @param  destinoId  id de la galaxia destino
 * @return void
 */
void eliminarArco(int origenId, int destinoId) {
    Vertice* origen = buscarVertice(origenId);
    if (origen == nullptr) {
        cout << "Vertice origen " << origenId << " no encontrado." << endl;
        return;
    }

    Arco* actual   = origen->subListaArcos;
    Arco* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->destinoId == destinoId) {
            if (anterior == nullptr)
                origen->subListaArcos = actual->sigA;
            else
                anterior->sigA = actual->sigA;

            delete actual;

            if (adjMatrix != nullptr &&
                origenId < matrixSize && destinoId < matrixSize)
                adjMatrix[origenId][destinoId] = 0;
            return;
        }
        anterior = actual;
        actual   = actual->sigA;
    }
    cout << "Arco " << origenId << " -> " << destinoId << " no encontrado." << endl;
}

/**
 * @brief  Actualiza el costo del arco de origen a destino
 *         Actualiza tanto la lista de adyacencia como adjMatrix[][]
 * @param  origenId    id de la galaxia origen
 * @param  destinoId   id de la galaxia destino
 * @param  nuevoCosto  nuevo costo a asignar
 * @return void
 */
void actualizarCostoArco(int origenId, int destinoId, int nuevoCosto) {
    Vertice* origen = buscarVertice(origenId);
    if (origen == nullptr) {
        cout << "Vertice origen " << origenId << " no encontrado." << endl;
        return;
    }

    Arco* arco = origen->subListaArcos;
    while (arco != nullptr) {
        if (arco->destinoId == destinoId) {
            arco->costo = nuevoCosto;
            if (adjMatrix != nullptr &&
                origenId < matrixSize && destinoId < matrixSize)
                adjMatrix[origenId][destinoId] = nuevoCosto;
            return;
        }
        arco = arco->sigA;
    }
    cout << "Arco " << origenId << " -> " << destinoId << " no encontrado." << endl;
}

/**
 * @brief  Resetea visitado = false en todos los vertices del grafo
 *         Debe llamarse antes de cada recorrido BFS, DFS o Dijkstra
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
 * @brief  Carga la matriz de adyacencia desde un arreglo 2D dinamico
 *         Libera memoria anterior si existe y asigna nueva memoria dinamica
 * @param  matrix  arreglo 2D dinamico fuente con los valores de adyacencia
 * @param  size    numero de filas y columnas
 * @return void
 */
void cargarMatrizAdyacencia(int** matrix, int size) {
    if (adjMatrix != nullptr) {
        for (int i = 0; i < matrixSize; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }

    matrixSize = size;
    adjMatrix  = new int*[size];
    for (int i = 0; i < size; i++) {
        adjMatrix[i] = new int[size];
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
