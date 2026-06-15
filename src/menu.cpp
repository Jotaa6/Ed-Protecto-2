/*
 * Archivo: menu.cpp
 * Descripcion: Implementacion del menu principal y submenus
 * Estructuras: ninguna propia
 * Funciones: showMainMenu, showGalaxiasSubmenu, showRutasSubmenu,
 *            showNavesSubmenu, showViajesSubmenu, showConsultasSubmenu,
 *            showReportesSubmenu
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/menu.h"

// ──────────────────────────────────────────────────────────────────────────
// Submenus CRUD – una sola línea cada uno
// ──────────────────────────────────────────────────────────────────────────

void showGalaxiasSubmenu() { runCrud(galaxyConfig); }
void showRutasSubmenu()    { runCrud(routeConfig); }
void showNavesSubmenu()    { runCrud(shipConfig); }
void showViajesSubmenu()   { runCrud(tripConfig); }

// ──────────────────────────────────────────────────────────────────────────
// Submenu Consultas
// ──────────────────────────────────────────────────────────────────────────

void showConsultasSubmenu() {
    int opcion;
    do {
        cout << "\n=== CONSULTAS ===" << endl;
        cout << "1. Todas las rutas desde una galaxia" << endl;
        cout << "2. Ruta de menor costo entre dos galaxias" << endl;
        cout << "3. Árbol de expansión mínima (Kruskal)" << endl;
        cout << "4. Historial de viajes de una nave" << endl;
        cout << "0. Volver" << endl;

        opcion = pedirEntero("Seleccione una opción: ");

        switch (opcion) {
            case 1:
                try {
                    char id[100];
                    pedirCadena("Ingrese el ID de la galaxia origen: ", id, 100);
                    queryTodasLasRutas(string(id));
                } catch (...) {
                    cout << "Ocurrió un error al ejecutar la consulta." << endl;
                }
                break;

            case 2:
                try {
                    char origen[100], destino[100];
                    pedirCadena("ID de la galaxia origen: ", origen, 100);
                    pedirCadena("ID de la galaxia destino: ", destino, 100);
                    queryRutaMenorCosto(string(origen), string(destino));
                } catch (...) {
                    cout << "Ocurrió un error al ejecutar la consulta." << endl;
                }
                break;

            case 3:
                try {
                    queryArbolKruskal();
                } catch (...) {
                    cout << "Ocurrió un error al ejecutar la consulta." << endl;
                }
                break;

            case 4:
                try {
                    char id[100];
                    pedirCadena("Ingrese el ID de la nave: ", id, 100);
                    queryHistorialNave(string(id));
                } catch (...) {
                    cout << "Ocurrió un error al ejecutar la consulta." << endl;
                }
                break;

            case 0:
                cout << "Regresando al menú anterior..." << endl;
                break;

            default:
                cout << "Opción no válida, intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);
}

// ──────────────────────────────────────────────────────────────────────────
// Submenu Reportes
// ──────────────────────────────────────────────────────────────────────────

void showReportesSubmenu() {
    int opcion;
    do {
        cout << "\n=== REPORTES ===" << endl;
        cout << "1. Reporte de rutas más cortas" << endl;
        cout << "2. Reporte de ruta optimizada (MST)" << endl;
        cout << "3. Reporte de estadísticas" << endl;
        cout << "4. Generar todos los reportes" << endl;
        cout << "0. Volver" << endl;

        opcion = pedirEntero("Seleccione una opción: ");

        switch (opcion) {
            case 1:
                try {
                    generarReporteRutasCortas();
                    cout << "Reporte generado correctamente." << endl;
                } catch (...) {
                    cout << "Ocurrió un error al generar el reporte." << endl;
                }
                break;

            case 2:
                try {
                    generarReporteRutaOptimizada();
                    cout << "Reporte generado correctamente." << endl;
                } catch (...) {
                    cout << "Ocurrió un error al generar el reporte." << endl;
                }
                break;

            case 3:
                try {
                    generarReporteEstadisticas();
                    cout << "Reporte generado correctamente." << endl;
                } catch (...) {
                    cout << "Ocurrió un error al generar el reporte." << endl;
                }
                break;

            case 4:
                try {
                    generarReporteRutasCortas();
                    generarReporteRutaOptimizada();
                    generarReporteEstadisticas();
                    cout << "Todos los reportes fueron generados correctamente." << endl;
                } catch (...) {
                    cout << "Ocurrió un error al generar los reportes." << endl;
                }
                break;

            case 0:
                cout << "Regresando al menú anterior..." << endl;
                break;

            default:
                cout << "Opción no válida, intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);
}

// ──────────────────────────────────────────────────────────────────────────
// Menu Principal
// ──────────────────────────────────────────────────────────────────────────

void showMainMenu() {
    int opcion;
    do {
        cout << "\n===================================" << endl;
        cout << "      SISTEMA DE GALAXIAS" << endl;
        cout << "===================================" << endl;
        cout << "1. Galaxias" << endl;
        cout << "2. Rutas" << endl;
        cout << "3. Naves" << endl;
        cout << "4. Viajes" << endl;
        cout << "5. Consultas" << endl;
        cout << "6. Reportes" << endl;
        cout << "0. Salir" << endl;

        opcion = pedirEntero("Seleccione una opción: ");

        switch (opcion) {
            case 1:
                try { showGalaxiasSubmenu(); }
                catch (...) { cout << "Ocurrió un error al abrir el submenú." << endl; }
                break;
            case 2:
                try { showRutasSubmenu(); }
                catch (...) { cout << "Ocurrió un error al abrir el submenú." << endl; }
                break;
            case 3:
                try { showNavesSubmenu(); }
                catch (...) { cout << "Ocurrió un error al abrir el submenú." << endl; }
                break;
            case 4:
                try { showViajesSubmenu(); }
                catch (...) { cout << "Ocurrió un error al abrir el submenú." << endl; }
                break;
            case 5:
                try { showConsultasSubmenu(); }
                catch (...) { cout << "Ocurrió un error al abrir el submenú." << endl; }
                break;
            case 6:
                try { showReportesSubmenu(); }
                catch (...) { cout << "Ocurrió un error al abrir el submenú." << endl; }
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción no válida, intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);
}
