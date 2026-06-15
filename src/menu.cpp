/*
 * Archivo: menu.cpp
 * Descripcion: Implementacion del menu principal y submenus
 * Estructuras: ninguna propia
 * Funciones: showMainMenu, showGalaxiasSubmenu, showRutasSubmenu,
 *            showNavesSubmenu, showViajesSubmenu, showConsultasSubmenu,
 *            showReportesSubmenu
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: José Pablo Barrantes
 */
#include "../include/menu.h"

/**
 * @brief Ejecuta el CRUD de galaxias.
 * @return void
 */
void showGalaxiasSubmenu() {
    runCrud(galaxyConfig);
}

/**
 * @brief Ejecuta el CRUD de rutas.
 * @return void
 */
void showRutasSubmenu() {
    runCrud(routeConfig);
}

/**
 * @brief Ejecuta el CRUD de naves.
 * @return void
 */
void showNavesSubmenu() {
    runCrud(shipConfig);
}

/**
 * @brief Ejecuta el CRUD de viajes.
 * @return void
 */
void showViajesSubmenu() {
    runCrud(tripConfig);
}

/**
 * @brief  Muestra el submenu de consultas disponibles
 *         Permite ejecutar las cuatro consultas del proyecto
 * @return void
 */
void showConsultasSubmenu() {
    int opcion;

    do {
        cout << "\n=== CONSULTAS ===" << endl;
        cout << "1. Todas las rutas desde una galaxia" << endl;
        cout << "2. Ruta de menor costo" << endl;
        cout << "3. Arbol de expansion minima (Kruskal)" << endl;
        cout << "4. Historial de viajes de una nave" << endl;
        cout << "0. Volver" << endl;

        opcion = pedirEntero("Seleccione una opcion: ");

        switch (opcion) {

            case 1:
                try {
                    char id[100];
                    pedirCadena("Ingrese el ID de la galaxia: ", id, 100);
                    queryTodasLasRutas(string(id));
                }
                catch (...) {
                    cout << "Ocurrio un error al ejecutar la consulta." << endl;
                }
                break;

            case 2:
                try {
                    char origen[100];
                    char destino[100];

                    pedirCadena("Ingrese el ID de la galaxia origen: ", origen, 100);
                    pedirCadena("Ingrese el ID de la galaxia destino: ", destino, 100);

                    queryRutaMenorCosto(string(origen), string(destino));
                }
                catch (...) {
                    cout << "Ocurrio un error al ejecutar la consulta." << endl;
                }
                break;

            case 3:
                try {
                    queryArbolKruskal();
                }
                catch (...) {
                    cout << "Ocurrio un error al ejecutar la consulta." << endl;
                }
                break;

            case 4:
                try {
                    char id[100];
                    pedirCadena("Ingrese el ID de la nave: ", id, 100);

                    queryHistorialNave(string(id));
                }
                catch (...) {
                    cout << "Ocurrio un error al ejecutar la consulta." << endl;
                }
                break;

            case 0:
                cout << "Regresando al menu anterior..." << endl;
                break;

            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
                break;
        }

    } while (opcion != 0);
}

/**
 * @brief  Muestra el submenu de reportes disponibles
 *         Permite generar los reportes del proyecto
 * @return void
 */
void showReportesSubmenu() {
    int opcion;

    do {
        cout << "\n=== REPORTES ===" << endl;
        cout << "1. Reporte de rutas mas cortas" << endl;
        cout << "2. Reporte de ruta optimizada (MST)" << endl;
        cout << "3. Reporte de estadisticas" << endl;
        cout << "4. Generar todos los reportes" << endl;
        cout << "0. Volver" << endl;

        opcion = pedirEntero("Seleccione una opcion: ");

        switch (opcion) {

            case 1:
                try {
                    generarReporteRutasCortas();
                    cout << "Reporte generado correctamente." << endl;
                }
                catch (...) {
                    cout << "Ocurrio un error al generar el reporte." << endl;
                }
                break;

            case 2:
                try {
                    generarReporteRutaOptimizada();
                    cout << "Reporte generado correctamente." << endl;
                }
                catch (...) {
                    cout << "Ocurrio un error al generar el reporte." << endl;
                }
                break;

            case 3:
                try {
                    generarReporteEstadisticas();
                    cout << "Reporte generado correctamente." << endl;
                }
                catch (...) {
                    cout << "Ocurrio un error al generar el reporte." << endl;
                }
                break;

            case 4:
                try {
                    generarTodosLosReportes();
                    cout << "Todos los reportes fueron generados correctamente." << endl;
                }
                catch (...) {
                    cout << "Ocurrio un error al generar los reportes." << endl;
                }
                break;

            case 0:
                cout << "Regresando al menu anterior..." << endl;
                break;

            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
                break;
        }

    } while (opcion != 0);
}

/**
 * @brief  Muestra el menu principal del sistema
 *         Permite navegar hacia todos los submenus disponibles
 * @return void
 */
void showMainMenu() {
    
    int opcion;

    do {
        cout << "\n===================================" << endl;
        cout << "      Guardianes de la Galaxia       " << endl;
        cout << "===================================" << endl;
        cout << "1. Galaxias" << endl;
        cout << "2. Rutas" << endl;
        cout << "3. Naves" << endl;
        cout << "4. Viajes" << endl;
        cout << "5. Consultas" << endl;
        cout << "6. Reportes" << endl;
        cout << "0. Salir" << endl;

        opcion = pedirEntero("Seleccione una opcion: ");

        switch (opcion) {

            case 1:
                try {
                    showGalaxiasSubmenu();
                }
                catch (...) {
                    cout << "Ocurrio un error al abrir el submenu." << endl;
                }
                break;

            case 2:
                try {
                    showRutasSubmenu();
                }
                catch (...) {
                    cout << "Ocurrio un error al abrir el submenu." << endl;
                }
                break;

            case 3:
                try {
                    showNavesSubmenu();
                }
                catch (...) {
                    cout << "Ocurrio un error al abrir el submenu." << endl;
                }
                break;

            case 4:
                try {
                    showViajesSubmenu();
                }
                catch (...) {
                    cout << "Ocurrio un error al abrir el submenu." << endl;
                }
                break;

            case 5:
                try {
                    showConsultasSubmenu();
                }
                catch (...) {
                    cout << "Ocurrio un error al abrir el submenu." << endl;
                }
                break;

            case 6:
                try {
                    showReportesSubmenu();
                }
                catch (...) {
                    cout << "Ocurrio un error al abrir el submenu." << endl;
                }
                break;

            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;

            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
                break;
        }

    } while (opcion != 0);
}
