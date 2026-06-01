/*
 * Archivo: main.cpp
 * Descripcion: Punto de entrada del programa
 * Estructuras: ninguna propia
 * Funciones: main
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include <iostream>
#include <cstdlib>
#include "../include/data_loader.h"
#include "../include/menu.h"
using namespace std;

/**
 * @brief  Punto de entrada del programa
 *         Crea /output, carga todos los datos de la API y muestra el menu
 * @return 0 en salida limpia, 1 en error irrecuperable
 */
int main() {
    _mkdir("output");
    try {
        loadAll();
        showMainMenu();
    } catch (const exception& e) {
        cout << "Error critico: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "Error inesperado. El programa se cerrara." << endl;
        return 1;
    }
    return 0;
}
