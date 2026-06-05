/*
 * Archivo: dfs_routes.cpp
 * Descripcion: Implementacion del DFS para todas las rutas
 * Estructuras: ninguna propia
 * Funciones: dfsTodasLasRutas, mostrarTodasLasRutas
 * Creado: 1/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#include "../include/dfs_routes.h"
#include "../include/utils.h"

/**
 * @brief  Encuentra e imprime recursivamente todos los caminos desde origen
 *         Usa DFS con backtracking
 *         Marca visitado=true, recorre arcos, recursa, luego pone visitado=false
 * @param  origen  vertice actual siendo visitado
 * @param  ruta    string acumulando el camino actual para mostrar
 * @param  costo   costo acumulado del camino actual
 * @param  count   puntero al contador de caminos encontrados
 * @return void
 */
void dfsTodasLasRutas(Vertice* origen, string ruta, int costo, int* count) {
    if (origen == nullptr || *count >= 50) {
        return;
    }
    origen->visitado = true;
    Arco* arco = origen->subListaArcos;
    // Si no tiene arcos de salida, imprime la ruta actual
    if (arco == nullptr) {
        (*count)++;
        cout << *count << ". " << ruta << " | Costo: " << costo << endl;
        origen->visitado = false;
        return;
    }

    // Recorre todos los arcos del vertice actual
    while (arco != nullptr && *count < 50) {
        Vertice* vecino = buscarVertice(arco->destinoId);
        if (vecino != nullptr && vecino->visitado == false) {
            Galaxy* galaxyVecino = findGalaxyById(vecino->galaxyId);
            string nombreVecino = vecino->galaxyId;
            if (galaxyVecino != nullptr) {
                nombreVecino = galaxyVecino->name;
            }
            string nuevaRuta = ruta + " > " + nombreVecino;
            float nuevoCosto = costo + (float)arco->costo;
            (*count)++;
            cout << *count << ". " << nuevaRuta << " | Costo: " << nuevoCosto << endl;
            dfsTodasLasRutas(vecino, nuevaRuta, nuevoCosto, count);
        }
        arco = arco->sigA;
    }
    // Backtracking
    origen->visitado = false;
}

/**
 * @brief  Punto de entrada para la consulta de todas las rutas
 *         Llama desmarcarVertices() y luego dfsTodasLasRutas()
 *         Limita la salida a los primeros 50 caminos
 * @param  galaxyId  id de la galaxia origen
 * @return void
 */
void mostrarTodasLasRutas(string galaxyId) {
    Vertice* origen = buscarVertice(galaxyId);
    if (origen == nullptr) {
        cout << "Galaxia origen no encontrada." << endl;
        return;
    }
    desmarcarVertices();
    Galaxy* galaxyOrigen = findGalaxyById(origen->galaxyId);
    string nombreOrigen = origen->galaxyId;
    if (galaxyOrigen != nullptr) {
        nombreOrigen = galaxyOrigen->name;
    }
    int count = 0;
    cout << "\n=== TODAS LAS RUTAS DESDE " << nombreOrigen << " ===" << endl;
    dfsTodasLasRutas(origen, nombreOrigen, 0, &count);
    if (count == 0) {
        cout << "La galaxia no tiene rutas de salida." << endl;
    }
    if (count >= 50) {
        cout << "\nSe mostraron solo los primeros 50 caminos." << endl;
    }
}
