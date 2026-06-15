/*
 * Archivo: utils.cpp
 * Descripcion: Implementacion de funciones utilitarias compartidas
 * Estructuras: ninguna propia
 * Funciones: pedirEntero, pedirCadena, confirmarAccion, getCurrentTimestamp,
 *            findGalaxyById, findShipById, findEdgeById, findTripById, freeAll
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/utils.h"
#include "../include/graph.h"   // para acceder a grafo, Vertice, Arco

Galaxy* globalGalaxias = nullptr;
Ship*   globalShips    = nullptr;
Edge*   globalEdges    = nullptr;
Trip*   globalTrips    = nullptr;

/**
 * @brief  Lee entero de cin, repite hasta que se ingrese un entero valido
 * @param  mensaje  prompt a mostrar al usuario
 * @return entero valido ingresado por el usuario
 */
int pedirEntero(const char* mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.good()) { cin.ignore(); return valor; }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada invalida. Ingrese un numero entero." << endl;
    }
}

/**
 * @brief  Lee string no vacio via getline, repite hasta que no este vacio
 * @param  mensaje  prompt a mostrar
 * @param  result   arreglo de chars para almacenar resultado
 * @param  maxLen   maximo de caracteres a leer
 * @return void
 */
void pedirCadena(const char* mensaje, char* result, int maxLen) {
    while (true) {
        cout << mensaje;
        cin.getline(result, maxLen);
        if (strlen(result) > 0) return;
        cout << "El campo no puede estar vacio." << endl;
    }
}

/**
 * @brief  Muestra pregunta de si/no al usuario
 * @param  mensaje  pregunta a mostrar
 * @return true si el usuario ingresa s o S, false en caso contrario
 */
bool confirmarAccion(const char* mensaje) {
    char respuesta[4];
    cout << mensaje << " (s/n): ";
    cin.getline(respuesta, 4);
    return (respuesta[0] == 's' || respuesta[0] == 'S');
}

/**
 * @brief  Retorna fecha y hora actual como string formateado
 * @param  result   arreglo de chars para almacenar el timestamp
 * @param  maxLen   maximo de caracteres a escribir
 * @return void
 */
void getCurrentTimestamp(char* result, int maxLen) {
    time_t now = time(nullptr);
    struct tm t;
    localtime_s(&t, &now);
    strftime(result, maxLen, "%Y-%m-%d %H:%M:%S", &t);
}

/**
 * @brief  Busca en la lista global de Galaxy por id string
 * @param  id  id string a buscar
 * @return puntero a Galaxy si se encuentra, nullptr si no
 */
Galaxy* findGalaxyById(string id) {
    Galaxy* temp = globalGalaxias;
    while (temp != nullptr) {
        if (temp->id == id) return temp;
        temp = temp->siguiente;
    }
    return nullptr;
}

/**
 * @brief  Busca en la lista global de Ship por id string
 * @param  id  id string a buscar
 * @return puntero a Ship si se encuentra, nullptr si no
 */
Ship* findShipById(string id) {
    Ship* temp = globalShips;
    while (temp != nullptr) {
        if (temp->id == id) return temp;
        temp = temp->siguiente;
    }
    return nullptr;
}

/**
 * @brief  Busca en la lista global de Edge por id string
 * @param  id  id string a buscar
 * @return puntero a Edge si se encuentra, nullptr si no
 */
Edge* findEdgeById(string id) {
    Edge* temp = globalEdges;
    while (temp != nullptr) {
        if (temp->id == id) return temp;
        temp = temp->siguiente;
    }
    return nullptr;
}

/**
 * @brief  Busca en la lista global de Trip por id string
 * @param  id  id string a buscar
 * @return puntero a Trip si se encuentra, nullptr si no
 */
Trip* findTripById(string id) {
    Trip* temp = globalTrips;
    while (temp != nullptr) {
        if (temp->id == id) return temp;
        temp = temp->siguiente;
    }
    return nullptr;
}

/**
 * @brief  Libera toda la memoria dinámica de las listas globales y del grafo
 *         Debe llamarse justo antes de salir del programa
 * @return void
 */
void freeAll() {
    // Liberar galaxias
    while (globalGalaxias != nullptr) {
        Galaxy* tmp = globalGalaxias;
        globalGalaxias = globalGalaxias->siguiente;
        delete tmp;
    }
    // Liberar naves (los viajes ya están en la lista global de trips)
    while (globalShips != nullptr) {
        Ship* tmp = globalShips;
        globalShips = globalShips->siguiente;
        delete tmp;
    }
    // Liberar rutas (edges)
    while (globalEdges != nullptr) {
        Edge* tmp = globalEdges;
        globalEdges = globalEdges->siguiente;
        delete tmp;
    }
    // Liberar viajes
    while (globalTrips != nullptr) {
        Trip* tmp = globalTrips;
        globalTrips = globalTrips->siguiente;
        delete tmp;
    }
    // Liberar grafo (vértices y arcos)
    extern Vertice* grafo;
    Vertice* v = grafo;
    while (v != nullptr) {
        Arco* a = v->subListaArcos;
        while (a != nullptr) {
            Arco* sig = a->sigA;
            delete a;
            a = sig;
        }
        Vertice* sigV = v->sigV;
        delete v;
        v = sigV;
    }
    grafo = nullptr;
}
