/*
 * Archivo: main.cpp
 * Descripcion: Punto de entrada del sistema
 *              Inicializa la carga de datos, muestra el menu principal
 *              y libera memoria antes de salir
 * Creado: 2026
 * Autores: <integrantes>
 */
#include <iostream>
#include <direct.h>
#include "../include/data_loader.h"
#include "../include/menu.h"
#include "../include/utils.h"
using namespace std;

/**
 * @brief  Punto de entrada del programa
 *         Crea la carpeta de salida, carga todos los datos desde la API,
 *         muestra el menu principal y al salir libera toda la memoria
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
        cout << "Error inesperado. El programa se cerrara." << endl;
        return 1;
    }

    // Liberar toda la memoria dinámica antes de salir
    freeAll();

    return 0;
}
