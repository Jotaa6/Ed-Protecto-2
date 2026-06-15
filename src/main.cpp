/*
 * Archivo: main.cpp
 * Descripcion: Main temporal para probar carga de datos y grafo
 * Creado: 2026
 * Autores: <integrantes>
 */
#include <iostream>
#include <direct.h>
nclude/menu.h"/a #include "../include/utils.h"
#include "../include/data_loader.h"
nclude/menu.h"/a #include "../include/utils.h"
#include "../include/graph.h"
nclude/menu.h"/a #include "../include/utils.h"
#include "../include/kruskal.h"
using namespace std;

int main() {
    _mkdir("output");
    playAudio("Guardianes.wav");
    try {
        loadAll();
        cout << "\n=== Verificacion del grafo ===" << endl;
        imprimirGrafo();
        cout << "\n=== Verificacion del MST ===" << endl;
        imprimirMST(mstResult);
    } catch (const exception& e) {
        cout << "Error critico: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "Error inesperado." << endl;
        return 1;
    }
    return 0;
}
