/*
 * Archivo: main.cpp
 * Descripcion: Punto de entrada del sistema
 *              Inicializa la carga de datos y muestra el menu principal
 * Creado: 2026
 * Autores: José Pablo Barrantes
 */
#include <iostream>
#include <direct.h>
#include "../include/data_loader.h"
#include "../include/menu.h"
#include "../include/utils.h"

using namespace std;

/**
 * @brief  Punto de entrada del programa
 *         Crea la carpeta de salida, carga todos los datos desde la API
 *         y muestra el menu principal del sistema
 * @return Codigo de salida del programa
 */
int main() {
    _mkdir("output");

    // Reproducir audio si el archivo Guardianes.wav existe
    playAudio("Guardianes.wav");

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

    // Liberar memoria dinámica antes de salir
    freeAll();

    return 0;
}
