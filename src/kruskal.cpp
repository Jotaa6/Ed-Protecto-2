/*
 * Archivo: kruskal.cpp
 * Descripcion: Implementacion del algoritmo de Kruskal aleatorio
 * Estructuras: ninguna propia
 * Funciones: buildMST, imprimirMST
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: Jose Pablo Barrantes Hernandez
 */
#include "../include/kruskal.h"
#include "../include/kruskal.h"
#include "../include/utils.h"
#include <cstdlib>

// Resultado global del MST
Edge* mstResult = nullptr;

// Costo total acumulado del MST
float mstTotalCost = 0;

/**
 * @brief  Construye el MST usando el algoritmo de Kruskal aleatorio modificado
 *         La API ya entrega las aristas en orden aleatorio mediante
 *         GET /grafo/kruskal, por lo que no se realiza ordenamiento local.
 *         Se utiliza Union-Find para evitar ciclos.
 * @param  kruskalEdges  lista enlazada de aristas recibidas de la API
 * @param  nodeCount     cantidad total de vertices del grafo
 * @return void
 */
void buildMST(Edge* kruskalEdges, int nodeCount) {

    //Limpiar resultado anterior si existe
    while (mstResult != nullptr) {
        Edge* sig = mstResult->siguiente;
        delete mstResult;
        mstResult = sig;
    }

    mstTotalCost = 0;

    if (kruskalEdges == nullptr || nodeCount <= 0)
        return;

    //Inicializar estructura Union-Find
    initUnionFind(nodeCount);

    Edge* ultimoMST = nullptr;
    Edge* actual    = kruskalEdges;

    int aristasMST = 0;

    while (actual != nullptr && aristasMST < nodeCount - 1) {

        /*
        Los ids vienen con formato:
        galaxia-1
        galaxia-12
         
        Se extrae la parte numerica para Union-Find.
         */
        int origen  = atoi(actual->originId.substr(8).c_str()) - 1;
        int destino = atoi(actual->destinationId.substr(8).c_str()) - 1;

        //Si no forma ciclo, agregar al MST
        if (unite(origen, destino)) {

            Edge* nueva = new Edge();

            nueva->id = actual->id;
            nueva->originId = actual->originId;
            nueva->destinationId = actual->destinationId;
            nueva->tipo = actual->tipo;
            nueva->cost = actual->cost;
            nueva->tiempoDias = actual->tiempoDias;
            nueva->activa = actual->activa;
            nueva->siguiente = nullptr;

            if (mstResult == nullptr) {
                mstResult = nueva;
                ultimoMST = nueva;
            } else {
                ultimoMST->siguiente = nueva;
                ultimoMST= nueva;
            }

            mstTotalCost += (int)actual->cost;
            aristasMST++;
        }

        actual = actual->siguiente;
    }
}

/**
 * @brief  Imprime en pantalla las aristas que forman el MST
 *         Mostrando nombres de galaxias y costo de cada ruta
 * @param  mst  lista enlazada de aristas del MST
 * @return void
 */
void imprimirMST(Edge* mst) {

    cout << "\n=== ARBOLITO DE EXPANSION MINIMA ===" << endl;

    if (mst == nullptr) {
        cout << "No hay datos para mostrar." << endl;
        return;
    }

    Edge* actual = mst;

    while (actual != nullptr) {

        Galaxy* origen  = findGalaxyById(actual->originId);
        Galaxy* destino = findGalaxyById(actual->destinationId);

        string nombreOrigen  = actual->originId;
        string nombreDestino = actual->destinationId;

        if (origen  != nullptr) nombreOrigen  = origen->name;
        if (destino != nullptr) nombreDestino = destino->name;

        cout << nombreOrigen << " -> " << nombreDestino << " | Costo: " << actual->cost<< endl;

        actual = actual->siguiente;
    }

    cout << "\nCosto total MST: "
         << mstTotalCost
         << endl;
}