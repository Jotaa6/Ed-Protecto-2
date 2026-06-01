/*
 * Archivo: data_loader.cpp
 * Descripcion: Implementacion de la carga automatica de datos al inicio
 * Estructuras: ninguna propia
 * Funciones: loadAll, printLoadStep
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/data_loader.h"

/**
 * @brief  Imprime un mensaje de paso de carga en terminal
 * @param  paso     numero del paso a mostrar
 * @param  mensaje  descripcion de lo que se esta cargando
 * @return void
 */
void printLoadStep(int paso, const char* mensaje) {
    cout << "[Paso " << paso << "] " << mensaje << "..." << endl;
}

/**
 * @brief  Orquesta la carga completa de datos en 8 pasos al inicio
 *         Despues de retornar la API nunca se vuelve a llamar
 * @return void
 */
void loadAll() {
    char json[65536];
    cout << "\n=== Cargando datos de la API ===" << endl;

    // Paso 1 — Galaxias
    try {
        printLoadStep(1, "Cargando galaxias");
        httpGet("/galaxias", json, sizeof(json));
        if (json[0] != '\0') {
            parseGalaxias(json, globalGalaxias);
            Galaxy* g = globalGalaxias;
            while (g != nullptr) {
                insertarVertice(g->id, g->name);
                g = g->siguiente;
            }
            int count = 0;
            g = globalGalaxias;
            while (g != nullptr) { count++; g = g->siguiente; }
            cout << "   " << count << " galaxias cargadas." << endl;
        } else {
            cout << "   Advertencia: no se pudo cargar galaxias." << endl;
        }
    } catch (...) {
        cout << "   Error en Paso 1 — continuando." << endl;
    }

    // Paso 2 — Rutas
    try {
        printLoadStep(2, "Cargando rutas");
        httpGet("/rutas", json, sizeof(json));
        if (json[0] != '\0') {
            parseRutas(json, globalEdges);
            Edge* e = globalEdges;
            while (e != nullptr) {
                insertarArco(e->originId, e->destinationId, e->cost);
                e = e->siguiente;
            }
            int count = 0;
            e = globalEdges;
            while (e != nullptr) { count++; e = e->siguiente; }
            cout << "   " << count << " rutas cargadas." << endl;
        } else {
            cout << "   Advertencia: no se pudo cargar rutas." << endl;
        }
    } catch (...) {
        cout << "   Error en Paso 2 — continuando." << endl;
    }

    // Paso 3 — Grafo completo (verificacion)
    try {
        printLoadStep(3, "Verificando estructura del grafo");
        httpGet("/grafo", json, sizeof(json));
        if (json[0] != '\0') {
            cout << "   Grafo verificado." << endl;
        } else {
            cout << "   Advertencia: no se pudo verificar grafo." << endl;
        }
    } catch (...) {
        cout << "   Error en Paso 3 — continuando." << endl;
    }

    // Paso 4 — Matriz de adyacencia
    try {
        printLoadStep(4, "Cargando matriz de adyacencia");
        httpGet("/grafo/adyacencia", json, sizeof(json));
        if (json[0] != '\0') {
            float** matrix = nullptr;
            int size = 0;
            parseAdyacencia(json, matrix, size);
            if (matrix != nullptr && size > 0) {
                cargarMatrizAdyacencia(matrix, size);
                for (int i = 0; i < size; i++) delete[] matrix[i];
                delete[] matrix;
                cout << "   Matriz " << size << "x" << size << " cargada." << endl;
            }
        } else {
            cout << "   Advertencia: no se pudo cargar matriz." << endl;
        }
    } catch (...) {
        cout << "   Error en Paso 4 — continuando." << endl;
    }

    // Paso 5 — Naves
    try {
        printLoadStep(5, "Cargando naves");
        httpGet("/naves", json, sizeof(json));
        if (json[0] != '\0') {
            parseNaves(json, globalShips);
            int count = 0;
            Ship* s = globalShips;
            while (s != nullptr) { count++; s = s->siguiente; }
            cout << "   " << count << " naves cargadas." << endl;
        } else {
            cout << "   Advertencia: no se pudo cargar naves." << endl;
        }
    } catch (...) {
        cout << "   Error en Paso 5 — continuando." << endl;
    }

    // Paso 6 — Historial de viajes
    try {
        printLoadStep(6, "Cargando historial de viajes");
        httpGet("/historial", json, sizeof(json));
        if (json[0] != '\0') {
            parseHistorial(json, globalTrips);
            // Adjuntar cada viaje al historial de su nave
            Trip* t = globalTrips;
            while (t != nullptr) {
                Ship* s = findShipById(t->shipId);
                if (s != nullptr) {
                    Trip* copia          = new Trip();
                    copia->id            = t->id;
                    copia->shipId        = t->shipId;
                    copia->rutaId        = t->rutaId;
                    copia->date          = t->date;
                    copia->cost          = t->cost;
                    copia->exitoso       = t->exitoso;
                    copia->naveNombre    = t->naveNombre;
                    copia->origenNombre  = t->origenNombre;
                    copia->destinoNombre = t->destinoNombre;
                    copia->siguiente     = s->tripHistory;
                    s->tripHistory       = copia;
                }
                t = t->siguiente;
            }
            int count = 0;
            t = globalTrips;
            while (t != nullptr) { count++; t = t->siguiente; }
            cout << "   " << count << " viajes cargados." << endl;
        } else {
            cout << "   Advertencia: no se pudo cargar historial." << endl;
        }
    } catch (...) {
        cout << "   Error en Paso 6 — continuando." << endl;
    }

    // Paso 7 — Kruskal
    try {
        printLoadStep(7, "Construyendo arbol de expansion minima (Kruskal)");
        httpGet("/grafo/kruskal", json, sizeof(json));
        if (json[0] != '\0') {
            Edge* kruskalEdges = nullptr;
            parseKruskal(json, kruskalEdges);
            int nodeCount = contarVertices();
            buildMST(kruskalEdges, nodeCount);
            // Liberar lista temporal
            while (kruskalEdges != nullptr) {
                Edge* sig = kruskalEdges->siguiente;
                delete kruskalEdges;
                kruskalEdges = sig;
            }
            cout << "   MST construido. Costo total: " << mstTotalCost << endl;
        } else {
            cout << "   Advertencia: no se pudo cargar kruskal." << endl;
        }
    } catch (...) {
        cout << "   Error en Paso 7 — continuando." << endl;
    }

    // Paso 8 — Resumen
    cout << "\n=== Carga completada ===" << endl;
    int ng = 0, ne = 0, ns = 0, nt = 0;
    Galaxy* g = globalGalaxias; while (g != nullptr) { ng++; g = g->siguiente; }
    Edge*   e = globalEdges;    while (e != nullptr) { ne++; e = e->siguiente; }
    Ship*   s = globalShips;    while (s != nullptr) { ns++; s = s->siguiente; }
    Trip*   t = globalTrips;    while (t != nullptr) { nt++; t = t->siguiente; }
    cout << "   Galaxias : " << ng << endl;
    cout << "   Rutas    : " << ne << endl;
    cout << "   Naves    : " << ns << endl;
    cout << "   Viajes   : " << nt << endl;
}
