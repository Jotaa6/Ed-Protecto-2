/*
 * Archivo: reports.cpp
 * Descripcion: Implementacion de la generacion de reportes
 * Estructuras: ninguna propia
 * Funciones: generarReporteRutasCortas, generarReporteRutaOptimizada,
 *            generarReporteEstadisticas
 * Creado: 5/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#include "../include/reports.h"

/**
 * @brief  Genera /output/rutasMasCortas.txt con todos los resultados Dijkstra de la sesion
 *         Escribe mensaje de sin datos si dijkstraCount es 0
 * @return void
 */
void generarReporteRutasCortas() {
    ofstream archivo;
    if (!abrirArchivo(archivo, "rutasMasCortas.txt")) {
        return;
    }
    escribirEncabezado(archivo, "REPORTE DE RUTAS MAS CORTAS");
    if (dijkstraCount == 0 || dijkstraResults == nullptr) {
        archivo << "No hay rutas mas cortas calculadas en esta sesion." << endl;
        escribirPie(archivo);
        cerrarArchivo(archivo, "rutasMasCortas.txt");
        return;
    }
    DijkstraResult* actual = dijkstraResults;
    int contador = 1;
    // Recorre la lista enlazada de resultados Dijkstra
    while (actual != nullptr) {
        archivo << "\nRuta #" << contador << endl;
    Galaxy* origen = findGalaxyById(actual->fromId);
    Galaxy* destino = findGalaxyById(actual->toId);
    string nombreOrigen = actual->fromId;
    string nombreDestino = actual->toId;
    if (origen != nullptr) {
        nombreOrigen = origen->name;
    }
    if (destino != nullptr) {
        nombreDestino = destino->name;
    }
    archivo << "Origen: " << nombreOrigen << endl;
    archivo << "Destino: " << nombreDestino << endl;
        archivo << "Camino: ";
        for (int i = 0; i < actual->pathLen; i++) {
            Galaxy* galaxia = findGalaxyById(actual->path[i]);
            string nombre = actual->path[i];
            if (galaxia != nullptr) {
                nombre = galaxia->name;
            }
            archivo << nombre;
            if (i < actual->pathLen - 1) {
                archivo << " > ";
            }
        }
        archivo << endl;
        archivo << "Costo total: " << actual->cost << endl;
        actual = actual->siguiente;
        contador++;
    }
    escribirPie(archivo);
    cerrarArchivo(archivo, "rutasMasCortas.txt");
}

/**
 * @brief  Genera /output/rutaOptimizada.txt con la lista completa de aristas del MST
 *         Version formal del reporte separada de resultantesKruskal.txt
 * @return void
 */
void generarReporteRutaOptimizada() {
    ofstream archivo;
    if (mstResult == nullptr) {
        cout << "Error: No se ha construido el MST. Ejecute la carga de datos primero." << endl;
        return;
    }
    if (!abrirArchivo(archivo, "rutaOptimizada.txt")) {
        return;
    }
    escribirEncabezado(archivo, "REPORTE DE RUTA OPTIMIZADA");
    Edge* actual = mstResult;
    int contador = 1;
    // Recorre la lista enlazada del MST
    while (actual != nullptr) {
        Galaxy* origen = findGalaxyById(actual->originId);
        Galaxy* destino = findGalaxyById(actual->destinationId);
        string nombreOrigen = actual->originId;
        string nombreDestino = actual->destinationId;
        if (origen != nullptr) {
            nombreOrigen = origen->name;
        }
        if (destino != nullptr) {
            nombreDestino = destino->name;
        }
        archivo << contador << ". ";
        archivo << nombreOrigen << " -> " << nombreDestino;
        archivo << " | Costo: " << actual->cost << endl;
        actual = actual->siguiente;
        contador++;
    }
    archivo << "\nCosto total MST: " << mstTotalCost << endl;
    escribirPie(archivo);
    cerrarArchivo(archivo, "rutaOptimizada.txt");
}

/**
 * @brief  Genera /output/estadisticas.txt con las estadisticas de la sesion
 *         Utiliza las funciones del modulo stats
 * @return void
 */
void generarReporteEstadisticas() {
    ofstream archivo;
    if (!abrirArchivo(archivo, "estadisticas.txt")) {
        return;
    }
    escribirEncabezado(archivo, "REPORTE DE ESTADISTICAS");
    archivo << "Total de rutas calculadas: "<< getTotalRutasCalculadas() << endl;
    char galaxia[200];
    int grado = 0;
    getGalaxiaMasConectada(galaxia, grado);
    archivo << "Galaxia mas conectada: "<< galaxia << endl;
    archivo << "Cantidad de conexiones: "<< grado << endl;
    archivo << "Costo promedio de rutas: "<< getCostoPromedio() << endl;
    archivo << endl;
    imprimirComparacionMST(archivo);
    archivo << endl;
    archivo << "=== TOTAL GALAXIAS Y RUTAS ===" << endl;
    archivo << "Total galaxias: " << contarVertices()
            << " | Total rutas: " << getTotalRutas() << endl;

    archivo << endl;
    archivo << "=== TOP 5 GALAXIAS MAS CONECTADAS ===" << endl;

    string nombres[5];
    int grados[5];

    getTop5GalaxiasMasConectadas(nombres, grados);

    for (int i = 0; i < 5; i++) {
        if (grados[i] > 0) {
            archivo << nombres[i]<< " - Grado: "<< grados[i]<< endl;
        }
    }
    escribirPie(archivo);
    cerrarArchivo(archivo, "estadisticas.txt");
}
// ==================== Función para generar todos los reportes ====================

/**
 * @brief  Genera los tres reportes del sistema consecutivamente
 * @return void
 */
void generarTodosLosReportes() {
    generarReporteRutasCortas();
    generarReporteRutaOptimizada();
    generarReporteEstadisticas();
}
