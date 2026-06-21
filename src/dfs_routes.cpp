/*
 * Archivo: dfs_routes.cpp
 * Descripcion: Implementacion del DFS para todas las rutas
 * Estructuras: ninguna propia
 * Funciones: dfsTodasLasRutas, mostrarTodasLasRutas
 * Creado: 1/6/2026
 * Ultima modificacion: 21/6/2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#include "../include/dfs_routes.h"
#include "../include/utils.h"
#include "../include/file_io.h"

/**
 * @brief  Encuentra recursivamente todos los caminos desde origen
 *         Usa DFS con backtracking. Escribe en archivo si se proporciona.
 *         SIN LIMITE DE 50 RUTAS (muestra TODAS).
 * @param  origen  vertice actual
 * @param  ruta    camino acumulado
 * @param  costo   costo acumulado
 * @param  count   puntero al contador de caminos
 * @param  archivo puntero a ofstream para escribir (opcional)
 * @return void
 */
void dfsTodasLasRutas(Vertice* origen, string ruta, float costo, int* count, ofstream* archivo) {
    if (origen == nullptr) return;

    origen->visitado = true;
    Arco* arco = origen->subListaArcos;

    // Caso base: no tiene arcos de salida -> es una ruta completa
    if (arco == nullptr) {
        (*count)++;
        if (archivo != nullptr && archivo->is_open()) {
            *archivo << (*count) << ". " << ruta << " | Costo: " << costo << endl;
        }
        origen->visitado = false;
        return;
    }

    // Recorrer todos los arcos del vertice actual (SIN LIMITE)
    while (arco != nullptr) {
        Vertice* vecino = buscarVertice(arco->destinoId);
        if (vecino != nullptr && vecino->visitado == false) {
            Galaxy* galaxyVecino = findGalaxyById(vecino->galaxyId);
            string nombreVecino = (galaxyVecino != nullptr) ? galaxyVecino->name : vecino->galaxyId;
            string nuevaRuta = ruta + " > " + nombreVecino;
            float nuevoCosto = costo + arco->costo;

            dfsTodasLasRutas(vecino, nuevaRuta, nuevoCosto, count, archivo);
        }
        arco = arco->sigA;
    }

    // Backtracking
    origen->visitado = false;
}

/**
 * @brief  Punto de entrada para la consulta de todas las rutas
 *         Valida la galaxia, crea el archivo y ejecuta el DFS.
 *         LAS RUTAS SOLO SE ESCRIBEN EN EL ARCHIVO, NO EN TERMINAL.
 * @param  galaxyId  id de la galaxia origen
 * @return void
 */
void mostrarTodasLasRutas(string galaxyId) {
    Vertice* origen = buscarVertice(galaxyId);
    if (origen == nullptr) {
        cout << "Galaxia no encontrada." << endl;
        return;
    }
    if (origen->subListaArcos == nullptr) {
        cout << "Sin conexiones." << endl;
        return;
    }

    desmarcarVertices();
    Galaxy* galaxyOrigen = findGalaxyById(origen->galaxyId);
    string nombreOrigen = (galaxyOrigen != nullptr) ? galaxyOrigen->name : origen->galaxyId;

    // Abrir archivo para escritura
    ofstream archivo;
    if (!abrirArchivo(archivo, "todasLasRutas.txt")) {
        cout << "Error al crear el archivo de rutas." << endl;
        return;
    }

    // Escribir encabezado
    string titulo = "TODAS LAS RUTAS POSIBLES DESDE " + nombreOrigen;
    escribirEncabezado(archivo, titulo.c_str());
    archivo << "Galaxia origen: " << nombreOrigen << " (ID: " << galaxyId << ")" << endl;
    archivo << "========================================" << endl;

    int count = 0;
    dfsTodasLasRutas(origen, nombreOrigen, 0, &count, &archivo);

    // Escribir pie y total
    archivo << "========================================" << endl;
    archivo << "Total de rutas encontradas: " << count << endl;
    escribirPie(archivo);
    cerrarArchivo(archivo, "todasLasRutas.txt");

    // ÚNICO MENSAJE EN TERMINAL (solo confirmación)
    cout << "\nTodas las rutas desde " << nombreOrigen << " se han guardado en output/todasLasRutas.txt" << endl;
    cout << "Total de rutas: " << count << endl;
}
