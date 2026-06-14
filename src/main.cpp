/*
 * Archivo: main.cpp
 * Descripcion: Main temporal para probar carga de datos y grafo
 * Creado: 2026
 * Autores: <José Pablo Barrantes
 */
#include <iostream>
#include <direct.h>
#include "../include/graph.h"
#include "../include/kruskal.h"
#include "../include/data_loader.h"
#include "../include/menu.h"
using namespace std;

/**
 * @brief  Punto de entrada del programa
 *         Crea la carpeta de salida, carga todos los datos desde la API
 *         y muestra el menu principal del sistema
 * @return Codigo de salida del programa
 */
int main() {
    _mkdir("output");

    try {
        loadAll();
        showMainMenu();
    }
    catch (const exception& e) {
        cout << "Error critico: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cout << "Error inesperado." << endl;
        return 1;
    }

    return 0;
}
