/*
 * Archivo: queries.cpp
 * Descripcion: Implementacion de las cuatro consultas del proyecto
 * Estructuras: ninguna propia
 * Funciones: validarGalaxia, validarNave, queryTodasLasRutas,
 *            queryRutaMenorCosto, queryArbolKruskal, queryHistorialNave
 * Creado: 4/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#include "../include/queries.h"

string construirIdGalaxia(int galaxyId) {
    return "galaxia-" + to_string(galaxyId);
}
string construirIdNave(int shipId) {
    return "nave-" + to_string(shipId);
}

/**
 * @brief  Valida que un id de galaxia existe en el grafo global
 * @param  galaxyId    id numerico a validar
 * @param  entityName  nombre para mostrar en mensaje de error
 * @return true si existe, false si no se encuentra
 */
bool validarGalaxia(int galaxyId, const char* entityName) {
    string id = construirIdGalaxia(galaxyId);
    if (buscarVertice(id) == nullptr) {
        cout << entityName << " no encontrada: " << id << endl;
        return false;
    }
    return true;
}

/**
 * @brief  Valida que un id de nave existe en la lista global de naves
 * @param  shipId  id numerico a validar
 * @return true si existe, false si no se encuentra
 */
bool validarNave(int shipId) {
    string id = construirIdNave(shipId);
    if (findShipById(id) == nullptr) {
        cout << "Nave no encontrada: " << id << endl;
        return false;
    }
    return true;
}

/**
 * @brief  Consulta 1 — muestra todas las rutas posibles desde una galaxia usando DFS
 * @param  galaxyId  id numerico de la galaxia origen
 * @return void
 */
void queryTodasLasRutas(int galaxyId) {
    cout << "\n=== CONSULTA 1: TODAS LAS RUTAS POSIBLES ===" << endl;
    if (!validarGalaxia(galaxyId, "Galaxia origen")) {
        return;
    }
    string origenId = construirIdGalaxia(galaxyId);
    mostrarTodasLasRutas(origenId);
}

/**
 * @brief  Consulta 2 — muestra la ruta de menor costo entre dos galaxias
 *         Resultado almacenado en lista global dijkstraResults para reporte
 * @param  origenId   id numerico de la galaxia origen
 * @param  destinoId  id numerico de la galaxia destino
 * @return void
 */
void queryRutaMenorCosto(int origenId, int destinoId) {
    cout << "\n=== CONSULTA 2: RUTA DE MENOR COSTO ===" << endl;
    if (!validarGalaxia(origenId, "Galaxia origen")) {
        return;
    }
    if (!validarGalaxia(destinoId, "Galaxia destino")) {
        return;
    }
    string origen = construirIdGalaxia(origenId);
    string destino = construirIdGalaxia(destinoId);
    float costo = dijkstra(origen, destino);
    if (costo == -1) {
        cout << "No existe una ruta entre las galaxias indicadas." << endl;
        return;
    }
    DijkstraResult* ultimo = getUltimoResultado();
    cout << "Ruta encontrada:" << endl;
    imprimirRutaDijkstra(ultimo);
}

/**
 * @brief  Consulta 3 — muestra el MST de Kruskal en terminal
 *         Escribe /output/resultantesKruskal.txt automaticamente cada vez
 *         Llama buildMST() primero si mstResult es nullptr
 * @return void
 */
void queryArbolKruskal() {
    cout << "\n=== CONSULTA 3: ARBOL DE EXPANSION MINIMA ===" << endl;
    if (mstResult == nullptr) {
        buildMST(globalEdges, contarVertices());
    }
    imprimirMST(mstResult);
    ofstream archivo;
    if (!abrirArchivo(archivo, "resultantesKruskal.txt")) {
        return;
    }
    escribirEncabezado(archivo, "RESULTANTES KRUSKAL");
    if (mstResult == nullptr) {
        archivo << "No hay datos del arbol de expansion minima." << endl;
        escribirPie(archivo);
        cerrarArchivo(archivo, "resultantesKruskal.txt");
        return;
    }
    Edge* actual = mstResult;
    while (actual != nullptr) {
        Galaxy* origen = findGalaxyById(actual->originId);
        Galaxy* destino = findGalaxyById(actual->destinationId);
        string nombreOrigen = actual->originId;
        string nombreDestino = actual->destinationId;
        if (origen != nullptr) {
            nombreOrigen = origen->name;
        }
        if (destino != nullptr) {
            nombreDestino = destino->name;
        }
        archivo << nombreOrigen << " -> " << nombreDestino
                << " | Costo: " << actual->cost << endl;
        actual = actual->siguiente;
    }
    archivo << "\nCosto total MST: " << mstTotalCost << endl;
    escribirPie(archivo);
    cerrarArchivo(archivo, "resultantesKruskal.txt");
}

/**
 * @brief  Consulta 4 — muestra historial completo de viajes de una nave
 * @param  shipId  id numerico de la nave a consultar
 * @return void
 */
void queryHistorialNave(int shipId) {
    cout << "\n=== CONSULTA 4: HISTORIAL DE VIAJES DE NAVE ===" << endl;
    if (!validarNave(shipId)) {
        return;
    }
    string id = construirIdNave(shipId);
    Ship* nave = findShipById(id);
    cout << "Nave: " << nave->name << " (" << nave->id << ")" << endl;
    Trip* viaje = nave->tripHistory;
    if (viaje == nullptr) {
        cout << "La nave no tiene viajes registrados." << endl;
        return;
    }
    int contador = 0;
    while (viaje != nullptr) {
        contador++;
        cout << contador << ". ";
        cout << "Viaje: " << viaje->id << " | ";
        cout << "Ruta: " << viaje->origenNombre << " -> " << viaje->destinoNombre << " | ";
        cout << "Fecha: " << viaje->date << " | ";
        cout << "Costo: " << viaje->cost << " | ";
        if (viaje->exitoso) {
            cout << "Exitoso";
        } else {
            cout << "Fallido";
        }
        cout << endl;
        viaje = viaje->siguiente;
    }
}
// ==================== Funciones faltantes con string IDs ====================

/**
 * @brief  Consulta 1 — todas las rutas desde una galaxia (versión string)
 * @param galaxyId ID de la galaxia como string
 */
void queryTodasLasRutas(string galaxyId) {
    cout << "\n=== CONSULTA 1: TODAS LAS RUTAS POSIBLES ===" << endl;
    if (buscarVertice(galaxyId) == nullptr) {
        cout << "Galaxia no encontrada." << endl;
        return;
    }
    mostrarTodasLasRutas(galaxyId);
}

/**
 * @brief  Consulta 2 — ruta de menor costo entre dos galaxias (versión string)
 * @param origenId  ID origen
 * @param destinoId ID destino
 */
void queryRutaMenorCosto(string origenId, string destinoId) {
    cout << "\n=== CONSULTA 2: RUTA DE MENOR COSTO ===" << endl;
    if (buscarVertice(origenId) == nullptr) {
        cout << "Galaxia origen no encontrada." << endl;
        return;
    }
    if (buscarVertice(destinoId) == nullptr) {
        cout << "Galaxia destino no encontrada." << endl;
        return;
    }
    float costo = dijkstra(origenId, destinoId);
    if (costo == -1) {
        cout << "No existe una ruta entre las galaxias indicadas." << endl;
        return;
    }
    DijkstraResult* ultimo = getUltimoResultado();
    if (ultimo == nullptr) {
        cout << "No se pudo recuperar la ruta." << endl;
        return;
    }
    cout << "Ruta encontrada:" << endl;
    imprimirRutaDijkstra(ultimo);
}

/**
 * @brief  Consulta 4 — historial de viajes de una nave (versión string)
 * @param shipId ID de la nave
 */
void queryHistorialNave(string shipId) {
    cout << "\n=== CONSULTA 4: HISTORIAL DE VIAJES DE NAVE ===" << endl;
    Ship* nave = findShipById(shipId);
    if (nave == nullptr) {
        cout << "Nave no encontrada." << endl;
        return;
    }
    cout << "Nave: " << nave->name << " (" << nave->id << ")" << endl;
    Trip* viaje = nave->tripHistory;
    if (viaje == nullptr) {
        cout << "La nave no tiene viajes registrados." << endl;
        return;
    }
    int contador = 0;
    while (viaje != nullptr) {
        contador++;
        cout << contador << ". ";
        cout << "Viaje: " << viaje->id << " | ";
        cout << "Ruta: " << viaje->origenNombre << " -> " << viaje->destinoNombre << " | ";
        cout << "Fecha: " << viaje->date << " | ";
        cout << "Costo: " << viaje->cost << " | ";
        cout << (viaje->exitoso ? "Exitoso" : "Fallido") << endl;
        viaje = viaje->siguiente;
    }
}
