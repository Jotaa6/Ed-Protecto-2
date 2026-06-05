/*
 * Archivo: dijkstra.cpp
 * Descripcion: Implementacion del algoritmo de Dijkstra
 * Estructuras: DijkstraResult
 * Funciones: dijkstra, imprimirRutaDijkstra, getUltimoResultado
 * Creado: 1/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#include "../include/dijkstra.h"
#include <cfloat>

// Lista global de resultados Dijkstra
DijkstraResult* dijkstraResults = nullptr;

// Cantidad de consultas realizadas
int dijkstraCount = 0;

int buscarIndiceDijkstra(Vertice* vertices[], int cantidad, string id) {
    for (int i = 0; i < cantidad; i++) {
        if (vertices[i]->galaxyId == id) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief  Encuentra el camino de menor costo entre dos galaxias usando Dijkstra
 *         Usa arreglos planos y escaneo lineal manual
 *         Almacena resultado en lista global dijkstraResults
 *         Incrementa dijkstraCount global
 * @param  origenId   id de la galaxia origen
 * @param  destinoId  id de la galaxia destino
 * @return costo total del camino mas corto, o -1 si no es alcanzable
 */
float dijkstra(string origenId, string destinoId) {
    float dist[100];
    bool visited[100];
    int prev[100];
    Vertice* vertices[100];
    int cantidad = 0;
    Vertice* aux = grafo;
    // Guarda los vertices del grafo en un arreglo
    while (aux != nullptr && cantidad < 100) {
        vertices[cantidad] = aux;
        cantidad++;
        aux = aux->sigV;
    }
    int origen = buscarIndiceDijkstra(vertices, cantidad, origenId);
    int destino = buscarIndiceDijkstra(vertices, cantidad, destinoId);
    if (origen == -1 || destino == -1) {
        cout << "Origen o destino no encontrado." << endl;
        return -1;
    }
    // Inicializa los arreglos
    for (int i = 0; i < cantidad; i++) {
        dist[i] = FLT_MAX;
        visited[i] = false;
        prev[i] = -1;
    }
    dist[origen] = 0;

    // Ejecuta Dijkstra con escaneo lineal manual
    for (int i = 0; i < cantidad; i++) {
        float menor = FLT_MAX;
        int actual = -1;
        // Busca el nodo no visitado con menor distancia
        for (int j = 0; j < cantidad; j++) {
            if (visited[j] == false && dist[j] < menor) {
                menor = dist[j];
                actual = j;
            }
        }
        if (actual == -1) {
            break;
        }
        visited[actual] = true;
        Arco* arco = vertices[actual]->subListaArcos;
        // Recorre las conexiones del nodo actual
        while (arco != nullptr) {
            int vecino = buscarIndiceDijkstra(vertices, cantidad, arco->destinoId);
            if (vecino != -1 && visited[vecino] == false && dist[actual] != FLT_MAX) {
                float nuevoCosto = dist[actual] + arco->costo;
                if (nuevoCosto < dist[vecino]) {
                    dist[vecino] = nuevoCosto;
                    prev[vecino] = actual;
                }
            }
            arco = arco->sigA;
        }
    }

    if (dist[destino] == FLT_MAX) {
        return -1;
    }
    DijkstraResult* nuevo = new DijkstraResult;
    nuevo->fromId = origenId;
    nuevo->toId = destinoId;
    nuevo->cost = dist[destino];
    nuevo->pathLen = 0;
    nuevo->siguiente = nullptr;
    string caminoTemporal[100];
    int cantidadCamino = 0;
    // Reconstruye el camino desde el destino hasta el origen
    int actual = destino;
    while (actual != -1) {
        caminoTemporal[cantidadCamino] = vertices[actual]->galaxyId;
        cantidadCamino++;
        actual = prev[actual];
    }
    // Guarda el camino en orden correcto
    for (int i = cantidadCamino - 1; i >= 0; i--) {
        nuevo->path[nuevo->pathLen] = caminoTemporal[i];
        nuevo->pathLen++;
    }
    // Guarda el resultado en la lista enlazada global
    if (dijkstraResults == nullptr) {
        dijkstraResults = nuevo;
    } else {
        DijkstraResult* temp = dijkstraResults;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
    dijkstraCount++;
    return dist[destino];
}

/**
 * @brief  Imprime el camino almacenado en un DijkstraResult
 *         Formato: Galaxia A > Galaxia B > Galaxia C | Costo: X
 * @param  result  puntero al DijkstraResult a imprimir
 * @return void
 */
void imprimirRutaDijkstra(DijkstraResult* result) {
    if (result == nullptr) {
        cout << "No hay resultado de Dijkstra." << endl;
        return;
    }
    for (int i = 0; i < result->pathLen; i++) {
        cout << result->path[i];

        if (i < result->pathLen - 1) {
            cout << " > ";
        }
    }
    cout << " | Costo: " << result->cost << endl;
}

/**
 * @brief  Retorna puntero al resultado Dijkstra mas reciente
 * @return puntero al ultimo resultado, o nullptr si ninguno fue ejecutado
 */
DijkstraResult* getUltimoResultado() {
    if (dijkstraResults == nullptr) {
        return nullptr;
    }
    DijkstraResult* temp = dijkstraResults;
    while (temp->siguiente != nullptr) {
        temp = temp->siguiente;
    }
    return temp;
}