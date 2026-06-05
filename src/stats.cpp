/*
 * Archivo: stats.cpp
 * Descripcion: Implementacion del motor de estadisticas
 * Estructuras: ninguna propia
 * Funciones: getTotalRutasCalculadas, getGalaxiaMasConectada,
 *            getCostoPromedio, imprimirComparacionMST
 * Creado: 4/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#include "../include/stats.h"

/**
 * @brief  Retorna el total de consultas Dijkstra ejecutadas en la sesion
 * @return valor global de dijkstraCount
 */
int getTotalRutasCalculadas() {
    return dijkstraCount;
}

/**
 * @brief  Encuentra la galaxia con mas arcos de salida en el grafo
 * @param  result  arreglo de chars para almacenar nombre de la galaxia mas conectada
 * @param  degree  salida — numero de arcos de la galaxia mas conectada
 * @return void
 */
void getGalaxiaMasConectada(char* result, int& degree) {
    degree = 0;
    if (result != nullptr) {
        strcpy(result, "N/A");
    }
    Vertice* actual = grafo;
    while (actual != nullptr) {
        int contador = 0;
        Arco* arco = actual->subListaArcos;
        // Cuenta los arcos de salida del vertice actual
        while (arco != nullptr) {
            contador++;
            arco = arco->sigA;
        }
        if (contador > degree) {
            degree = contador;
            Galaxy* galaxia = findGalaxyById(actual->galaxyId);
            string nombre = actual->galaxyId;
            if (galaxia != nullptr) {
                nombre = galaxia->name;
            }
            if (result != nullptr) {
                strcpy(result, nombre.c_str());
            }
        }
        actual = actual->sigV;
    }
}

/**
 * @brief  Calcula el costo promedio de todas las aristas en la lista global
 * @return costo promedio como float, o 0.0 si no hay aristas
 */
float getCostoPromedio() {
    Edge* actual = globalEdges;
    float suma = 0;
    int cantidad = 0;
    // Recorre la lista global de aristas
    while (actual != nullptr) {
        suma += actual->cost;
        cantidad++;
        actual = actual->siguiente;
    }
    if (cantidad == 0) {
        return 0.0;
    }
    return suma / cantidad;
}

/**
 * @brief  Imprime comparacion MST vs costos originales en un archivo abierto
 * @param  archivo  referencia a ofstream abierto donde escribir
 * @return void
 */
void imprimirComparacionMST(ofstream& archivo) {
    archivo << "=== COMPARACION MST VS COSTOS ORIGINALES ===" << endl;
    float costoOriginal = 0;
    int totalOriginal = 0;
    Edge* actual = globalEdges;
    // Calcula el costo total de las aristas originales
    while (actual != nullptr) {
        costoOriginal += actual->cost;
        totalOriginal++;
        actual = actual->siguiente;
    }
    archivo << "Cantidad de aristas originales: " << totalOriginal << endl;
    archivo << "Costo total de aristas originales: " << costoOriginal << endl;
    if (mstResult == nullptr) {
        archivo << "MST no construido." << endl;
        archivo << "Costo total MST: 0" << endl;
        return;
    }
    archivo << "Costo total MST: " << mstTotalCost << endl;
    archivo << "Ahorro aproximado: " << costoOriginal - mstTotalCost << endl;
    archivo << "\nAristas del MST:" << endl;
    Edge* mst = mstResult;
    // Imprime las aristas que forman el MST
    while (mst != nullptr) {
        Galaxy* origen = findGalaxyById(mst->originId);
        Galaxy* destino = findGalaxyById(mst->destinationId);
        string nombreOrigen = mst->originId;
        string nombreDestino = mst->destinationId;
        if (origen != nullptr) {
            nombreOrigen = origen->name;
        }
        if (destino != nullptr) {
            nombreDestino = destino->name;
        }
        archivo << nombreOrigen << " -> " << nombreDestino << " | Costo: " << mst->cost << endl;
        mst = mst->siguiente;
    }
}