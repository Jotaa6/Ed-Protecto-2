/*
 * Archivo: main.cpp
 * Descripcion: Punto de entrada del sistema
 *              Inicializa la carga de datos, muestra el menu principal,
 *              reproduce audio y libera memoria al salir
 * Creado: 2026
 * Ultima modificacion: 21/6/2026
 * Autores: José Pablo Barrantes, Santiago Eloy Céspedes Mora
 */
#include <iostream>
#include <direct.h>
#include "../include/data_loader.h"
#include "../include/menu.h"
#include "../include/utils.h"

using namespace std;

/**
 * @brief  Punto de entrada del programa
 *         Crea la carpeta /output, reproduce el audio de bienvenida,
 *         carga los datos de la API y ejecuta el menu principal.
 *         Al salir, libera toda la memoria dinamica.
 * @return 0 en exito, 1 en error critico
 */
int main() {
    _mkdir("output");

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

    freeAll();
    return 0;
}
