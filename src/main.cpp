/*
 * Archivo: main.cpp
 * Descripcion: Main temporal para probar carga de datos y grafo
 * Creado: 2026
 * Autores: <integrantes>
 */
#include <iostream>
#include <direct.h>
#include "../include/data_loader.h"
#include "../include/graph.h"
#include "../include/kruskal.h"
using namespace std;

int main() {
    _mkdir("output");
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
