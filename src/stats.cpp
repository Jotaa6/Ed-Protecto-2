/*
 * Archivo: stats.cpp
 * Descripcion: Implementacion del motor de estadisticas
 * Estructuras: ninguna propia
 * Funciones: getTotalRutasCalculadas, getGalaxiaMasConectada,
 *            getCostoPromedio, imprimirComparacionMST,
 *            getTotalRutas, getTop5GalaxiasMasConectadas
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
    float suma   = 0;
    int cantidad = 0;
    while (actual != nullptr) {
        suma += actual->cost;
        cantidad++;
        actual = actual->siguiente;
    }
    if (cantidad == 0) return 0.0f;
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
    int totalOriginal   = 0;
    Edge* actual = globalEdges;
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
    while (mst != nullptr) {
        Galaxy* origen  = findGalaxyById(mst->originId);
        Galaxy* destino = findGalaxyById(mst->destinationId);
        string nombreOrigen  = mst->originId;
        string nombreDestino = mst->destinationId;
        if (origen  != nullptr) nombreOrigen  = origen->name;
        if (destino != nullptr) nombreDestino = destino->name;
        archivo << nombreOrigen << " -> " << nombreDestino
                << " | Costo: " << mst->cost << endl;
        mst = mst->siguiente;
    }
}

/**
 * @brief  Retorna el total de rutas/aristas cargadas en la lista global
 * @return cantidad de aristas en globalEdges
 */
int getTotalRutas() {
    int count    = 0;
    Edge* actual = globalEdges;
    while (actual != nullptr) {
        count++;
        actual = actual->siguiente;
    }
    return count;
}

/**
 * @brief  Obtiene las 5 galaxias con mayor cantidad de arcos de salida
 *         Usa seleccion manual sin STL
 * @param  nombres  arreglo donde se guardan los nombres de las galaxias
 * @param  grados   arreglo donde se guardan los grados de salida
 * @return void
 */
void getTop5GalaxiasMasConectadas(string nombres[5], int grados[5]) {
    // Inicializar arreglos
    for (int i = 0; i < 5; i++) {
        nombres[i] = "";
        grados[i]  = 0;
    }

    Vertice* actual = grafo;
    while (actual != nullptr) {
        // Contar arcos de salida
        int contador = 0;
        Arco* arco   = actual->subListaArcos;
        while (arco != nullptr) {
            contador++;
            arco = arco->sigA;
        }

        // Obtener nombre de la galaxia
        Galaxy* galaxia = findGalaxyById(actual->galaxyId);
        string nombre   = actual->galaxyId;
        if (galaxia != nullptr) nombre = galaxia->name;

        // Insertar en el top 5 si corresponde
        for (int i = 0; i < 5; i++) {
            if (contador > grados[i]) {
                // Desplazar los menores hacia abajo
                for (int j = 4; j > i; j--) {
                    nombres[j] = nombres[j - 1];
                    grados[j]  = grados[j - 1];
                }
                nombres[i] = nombre;
                grados[i]  = contador;
                break;
            }
        }
        actual = actual->sigV;
    }
}
