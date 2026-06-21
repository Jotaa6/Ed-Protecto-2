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
#include "../include/file_io.h"

/**
 * @brief  Encuentra e imprime recursivamente todos los caminos desde origen
 *         Usa DFS
 *         Marca visitado=true, recorre arcos, recursa, luego pone visitado=false
 * @param  origen  vertice actual siendo visitado
 * @param  ruta    string acumulando el camino actual para mostrar
 * @param  costo   costo acumulado del camino actual
 * @param  count   puntero al contador de caminos encontrados
 * @return void
 */
void dfsTodasLasRutas(Vertice* origen, string ruta, float costo, float* count, ofstream* archivo) {
    if (origen == nullptr || *count >= 50) return;
    origen->visitado = true;
    Arco* arco = origen->subListaArcos;

    if (arco == nullptr) {
        (*count)++;
        string linea = to_string((int)*count) + ". " + ruta + " | Costo: " + to_string(costo);
        cout << linea << endl;
        if (archivo != nullptr && archivo->is_open()) {
            *archivo << linea << endl;
        }
        origen->visitado = false;
        return;
    }

    while (arco != nullptr && *count < 50) {
        Vertice* vecino = buscarVertice(arco->destinoId);
        if (vecino != nullptr && vecino->visitado == false) {
            Galaxy* galaxyVecino = findGalaxyById(vecino->galaxyId);
            string nombreVecino = (galaxyVecino != nullptr) ? galaxyVecino->name : vecino->galaxyId;
            string nuevaRuta = ruta + " > " + nombreVecino;
            float nuevoCosto = costo + arco->costo;
            (*count)++;
            string linea = to_string((int)*count) + ". " + nuevaRuta + " | Costo: " + to_string(nuevoCosto);
            cout << linea << endl;
            if (archivo != nullptr && archivo->is_open()) {
                *archivo << linea << endl;
            }
            dfsTodasLasRutas(vecino, nuevaRuta, nuevoCosto, count, archivo);
        }
        arco = arco->sigA;
    }
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
        cout << "No encontrado." << endl;
        return;
    }
    if (origen->subListaArcos == nullptr) {
        cout << "Sin conexiones." << endl;
        return;
    }

    desmarcarVertices();
    Galaxy* galaxyOrigen = findGalaxyById(origen->galaxyId);
    string nombreOrigen = (galaxyOrigen != nullptr) ? galaxyOrigen->name : origen->galaxyId;

    float count = 0;
    cout << "\n=== TODAS LAS RUTAS DESDE " << nombreOrigen << " ===" << endl;

    // Abrir archivo
    ofstream archivo;
    if (abrirArchivo(archivo, "todasLasRutas.txt")) {
        string titulo = "TODAS LAS RUTAS DESDE " + nombreOrigen;
        escribirEncabezado(archivo, titulo.c_str());
        archivo << "Galaxia origen: " << nombreOrigen << " (ID: " << galaxyId << ")" << endl;
        archivo << "========================================" << endl;
    }

    dfsTodasLasRutas(origen, nombreOrigen, 0, &count, (archivo.is_open() ? &archivo : nullptr));

    if (count == 0) {
        string msg = "La galaxia no tiene rutas de salida.";
        cout << msg << endl;
        if (archivo.is_open()) archivo << msg << endl;
    }
    if (count >= 50) {
        string msg = "\nSe mostraron solo los primeros 50 caminos.";
        cout << msg << endl;
        if (archivo.is_open()) archivo << msg << endl;
    }

    if (archivo.is_open()) {
        escribirPie(archivo);
        cerrarArchivo(archivo, "todasLasRutas.txt");
    }
}
