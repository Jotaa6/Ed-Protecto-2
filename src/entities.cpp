/*
 * Archivo: entities.cpp
 * Descripcion: Implementacion de las funciones CRUD especificas por entidad
 * Estructuras: ninguna propia
 * Funciones: listarGalaxias, agregarGalaxia, editarGalaxia, eliminarGalaxia,
 *            buscarGalaxyPorId, listarNaves, agregarNave, editarNave,
 *            eliminarNave, buscarNavePorId, listarRutas, agregarRuta,
 *            editarRuta, eliminarRuta, buscarRutaPorId, listarViajes,
 *            registrarViaje, editarViaje, eliminarViaje, buscarViajePorId
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: José Pablo Barrantes
 */
#include "../include/entities.h"

/*
 *                              GALAXIAS
 */

void listarGalaxias() {
    if (globalGalaxias == nullptr) {
        cout << "\nNo hay galaxias registradas." << endl;
        return;
    }
    Galaxy* actual = globalGalaxias;
    while (actual != nullptr) {
        cout << "\n----------------------------------------" << endl;
        cout << "ID: " << actual->id << endl;
        cout << "Nombre: " << actual->name << endl;
        cout << "Codigo: " << actual->code << endl;
        cout << "Tipo: " << actual->type << endl;
        cout << "Coordenadas: ("
             << actual->x << ", "
             << actual->y << ", "
             << actual->z << ")" << endl;
        actual = actual->siguiente;
    }
}

void agregarGalaxia() {
    Galaxy* nueva = new Galaxy();
    char buffer[100];

    pedirCadena("ID: ", buffer, 100);
    nueva->id = buffer;

    pedirCadena("Nombre: ", buffer, 100);
    nueva->name = buffer;

    pedirCadena("Codigo: ", buffer, 100);
    nueva->code = buffer;

    pedirCadena("Tipo: ", buffer, 100);
    nueva->type = buffer;

    cout << "Coordenada X: ";
    cin >> nueva->x;
    cout << "Coordenada Y: ";
    cin >> nueva->y;
    cout << "Coordenada Z: ";
    cin >> nueva->z;
    cin.ignore();

    Galaxy* temp = globalGalaxias;
    while (temp != nullptr) {
        if (temp->code == nueva->code) {
            cout << "\nYa existe una galaxia con ese codigo." << endl;
            delete nueva;
            return;
        }
        temp = temp->siguiente;
    }

    nueva->siguiente = nullptr;
    if (globalGalaxias == nullptr) {
        globalGalaxias = nueva;
    } else {
        temp = globalGalaxias;
        while (temp->siguiente != nullptr)
            temp = temp->siguiente;
        temp->siguiente = nueva;
    }

    insertarVertice(nueva->id, nueva->name);
    cout << "\nGalaxia agregada correctamente." << endl;
}

void editarGalaxia(string id) {
    Galaxy* galaxy = findGalaxyById(id);
    if (galaxy == nullptr) {
        cout << "\nGalaxia no encontrada." << endl;
        return;
    }

    char buffer[100];
    pedirCadena("Nuevo nombre: ", buffer, 100);
    galaxy->name = buffer;

    cout << "Nueva coordenada X: ";
    cin >> galaxy->x;
    cout << "Nueva coordenada Y: ";
    cin >> galaxy->y;
    cout << "Nueva coordenada Z: ";
    cin >> galaxy->z;
    cin.ignore();

    cout << "\nGalaxia editada correctamente." << endl;
}

void eliminarGalaxia(string id) {
    Galaxy* actual = globalGalaxias;
    Galaxy* anterior = nullptr;
    while (actual != nullptr && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        cout << "\nGalaxia no encontrada." << endl;
        return;
    }
    if (anterior == nullptr)
        globalGalaxias = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;

    eliminarVertice(id);
    delete actual;
    cout << "\nGalaxia eliminada correctamente." << endl;
}

void* buscarGalaxyPorId(string id) {
    return findGalaxyById(id);
}

/*
 *                                NAVES
 */

void listarNaves() {
    if (globalShips == nullptr) {
        cout << "\nNo hay naves registradas." << endl;
        return;
    }
    Ship* actual = globalShips;
    while (actual != nullptr) {
        cout << "\n----------------------------------------" << endl;
        cout << "ID: " << actual->id << endl;
        cout << "Nombre: " << actual->name << endl;
        cout << "Codigo: " << actual->code << endl;
        cout << "Capacidad: " << actual->capacidad << endl;
        cout << "Velocidad maxima: " << actual->velocidadMax << endl;
        cout << "Activa: " << (actual->activa ? "Si" : "No") << endl;
        actual = actual->siguiente;
    }
}

void agregarNave() {
    Ship* nueva = new Ship();
    char buffer[100];

    pedirCadena("ID: ", buffer, 100);
    nueva->id = buffer;

    pedirCadena("Nombre: ", buffer, 100);
    nueva->name = buffer;

    pedirCadena("Codigo: ", buffer, 100);
    nueva->code = buffer;

    nueva->capacidad = pedirEntero("Capacidad: ");
    nueva->velocidadMax = pedirEntero("Velocidad maxima: ");
    cout << "Activa (1 = Si, 0 = No): ";
    cin >> nueva->activa;
    cin.ignore();

    nueva->tripHistory = nullptr;
    nueva->siguiente = nullptr;

    Ship* temp = globalShips;
    while (temp != nullptr) {
        if (temp->code == nueva->code) {
            cout << "\nYa existe una nave con ese codigo." << endl;
            delete nueva;
            return;
        }
        temp = temp->siguiente;
    }

    if (globalShips == nullptr) {
        globalShips = nueva;
    } else {
        temp = globalShips;
        while (temp->siguiente != nullptr)
            temp = temp->siguiente;
        temp->siguiente = nueva;
    }
    cout << "\nNave agregada correctamente." << endl;
}

void editarNave(string id) {
    Ship* ship = findShipById(id);
    if (ship == nullptr) {
        cout << "\nNave no encontrada." << endl;
        return;
    }
    char buffer[100];
    pedirCadena("Nuevo nombre: ", buffer, 100);
    ship->name = buffer;
    cout << "\nNave editada correctamente." << endl;
}

void eliminarNave(string id) {
    Ship* actual = globalShips;
    Ship* anterior = nullptr;
    while (actual != nullptr && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        cout << "\nNave no encontrada." << endl;
        return;
    }
    if (actual->tripHistory != nullptr) {
        cout << "\nAdvertencia: la nave posee viajes registrados." << endl;
        if (!confirmarAccion("Desea eliminarla de todas formas?"))
            return;
    }
    if (anterior == nullptr)
        globalShips = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;
    delete actual;
    cout << "\nNave eliminada correctamente." << endl;
}

void* buscarNavePorId(string id) {
    return findShipById(id);
}

/*
 *                                RUTAS
 */

void listarRutas() {
    if (globalEdges == nullptr) {
        cout << "\nNo hay rutas registradas." << endl;
        return;
    }
    Edge* actual = globalEdges;
    while (actual != nullptr) {
        cout << "\n----------------------------------------" << endl;
        cout << "ID: " << actual->id << endl;
        cout << "Origen: " << actual->originId << endl;
        cout << "Destino: " << actual->destinationId << endl;
        cout << "Tipo: " << actual->tipo << endl;
        cout << "Costo: " << actual->cost << endl;
        cout << "Tiempo (dias): " << actual->tiempoDias << endl;
        cout << "Activa: " << (actual->activa ? "Si" : "No") << endl;
        actual = actual->siguiente;
    }
}

void agregarRuta() {
    Edge* nueva = new Edge();
    char buffer[100];

    pedirCadena("ID: ", buffer, 100);
    nueva->id = buffer;
    if (findEdgeById(nueva->id) != nullptr) {
        cout << "\nYa existe una ruta con ese ID." << endl;
        delete nueva;
        return;
    }

    pedirCadena("ID galaxia origen: ", buffer, 100);
    nueva->originId = buffer;
    if (findGalaxyById(nueva->originId) == nullptr) {
        cout << "\nLa galaxia origen no existe." << endl;
        delete nueva;
        return;
    }

    pedirCadena("ID galaxia destino: ", buffer, 100);
    nueva->destinationId = buffer;
    if (findGalaxyById(nueva->destinationId) == nullptr) {
        cout << "\nLa galaxia destino no existe." << endl;
        delete nueva;
        return;
    }

    pedirCadena("Tipo: ", buffer, 100);
    nueva->tipo = buffer;

    cout << "Costo: ";
    cin >> nueva->cost;
    cout << "Tiempo en dias: ";
    cin >> nueva->tiempoDias;
    cin.ignore();
    nueva->activa = confirmarAccion("La ruta esta activa?");

    nueva->siguiente = nullptr;
    if (globalEdges == nullptr) {
        globalEdges = nueva;
    } else {
        Edge* temp = globalEdges;
        while (temp->siguiente != nullptr)
            temp = temp->siguiente;
        temp->siguiente = nueva;
    }

    insertarArco(nueva->originId, nueva->destinationId, nueva->cost);
    cout << "\nRuta agregada correctamente." << endl;
}

void editarRuta(string id) {
    Edge* ruta = findEdgeById(id);
    if (ruta == nullptr) {
        cout << "\nRuta no encontrada." << endl;
        return;
    }
    cout << "Nuevo costo: ";
    cin >> ruta->cost;
    cin.ignore();
    actualizarCostoArco(ruta->originId, ruta->destinationId, ruta->cost);
    cout << "\nRuta editada correctamente." << endl;
}

void eliminarRuta(string id) {
    Edge* actual = globalEdges;
    Edge* anterior = nullptr;
    while (actual != nullptr && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        cout << "\nRuta no encontrada." << endl;
        return;
    }
    if (anterior == nullptr)
        globalEdges = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;

    eliminarArco(actual->originId, actual->destinationId);
    delete actual;
    cout << "\nRuta eliminada correctamente." << endl;
}

void* buscarRutaPorId(string id) {
    return findEdgeById(id);
}

/*
 *                                VIAJES
 */

void listarViajes() {
    if (globalTrips == nullptr) {
        cout << "\nNo hay viajes registrados." << endl;
        return;
    }
    Trip* actual = globalTrips;
    while (actual != nullptr) {
        cout << "\n----------------------------------------" << endl;
        cout << "ID: " << actual->id << endl;
        cout << "Nave: " << actual->naveNombre << endl;
        cout << "Ruta: " << actual->rutaId << endl;
        cout << "Origen: " << actual->origenNombre << endl;
        cout << "Destino: " << actual->destinoNombre << endl;
        cout << "Fecha: " << actual->date << endl;
        cout << "Costo: " << actual->cost << endl;
        cout << "Exitoso: " << (actual->exitoso ? "Si" : "No") << endl;
        actual = actual->siguiente;
    }
}

void registrarViaje() {
    Trip* nuevo = new Trip();
    char buffer[100];

    pedirCadena("ID: ", buffer, 100);
    nuevo->id = buffer;

    pedirCadena("ID de la nave: ", buffer, 100);
    nuevo->shipId = buffer;
    Ship* nave = findShipById(nuevo->shipId);
    if (nave == nullptr) {
        cout << "\nLa nave no existe." << endl;
        delete nuevo;
        return;
    }

    pedirCadena("ID de la ruta: ", buffer, 100);
    nuevo->rutaId = buffer;
    Edge* ruta = findEdgeById(nuevo->rutaId);
    if (ruta == nullptr) {
        cout << "\nLa ruta no existe." << endl;
        delete nuevo;
        return;
    }

    Galaxy* origen = findGalaxyById(ruta->originId);
    Galaxy* destino = findGalaxyById(ruta->destinationId);
    if (origen == nullptr || destino == nullptr) {
        cout << "\nLa ruta referencia galaxias inexistentes." << endl;
        delete nuevo;
        return;
    }

    pedirCadena("Fecha: ", buffer, 100);
    nuevo->date = buffer;

    cout << "Costo: ";
    cin >> nuevo->cost;
    cin.ignore();

    nuevo->exitoso = confirmarAccion("El viaje fue exitoso?");

    nuevo->naveNombre = nave->name;
    nuevo->origenNombre = origen->name;
    nuevo->destinoNombre = destino->name;
    nuevo->siguiente = nullptr;

    // Agregar a lista global
    if (globalTrips == nullptr) {
        globalTrips = nuevo;
    } else {
        Trip* temp = globalTrips;
        while (temp->siguiente != nullptr)
            temp = temp->siguiente;
        temp->siguiente = nuevo;
    }

    // Agregar al historial de la nave
    if (nave->tripHistory == nullptr) {
        nave->tripHistory = nuevo;
    } else {
        Trip* temp = nave->tripHistory;
        while (temp->siguiente != nullptr)
            temp = temp->siguiente;
        temp->siguiente = nuevo;
    }

    cout << "\nViaje registrado correctamente." << endl;
}

void editarViaje(string id) {
    Trip* viaje = findTripById(id);
    if (viaje == nullptr) {
        cout << "\nViaje no encontrado." << endl;
        return;
    }
    char buffer[100];
    pedirCadena("Nueva fecha: ", buffer, 100);
    viaje->date = buffer;
    cout << "Nuevo costo: ";
    cin >> viaje->cost;
    cin.ignore();
    cout << "\nViaje editado correctamente." << endl;
}

void eliminarViaje(string id) {
    Trip* actual = globalTrips;
    Trip* anterior = nullptr;
    while (actual != nullptr && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        cout << "\nViaje no encontrado." << endl;
        return;
    }

    // Eliminar del historial de la nave
    Ship* nave = findShipById(actual->shipId);
    if (nave != nullptr) {
        Trip* hActual = nave->tripHistory;
        Trip* hAnterior = nullptr;
        while (hActual != nullptr && hActual->id != id) {
            hAnterior = hActual;
            hActual = hActual->siguiente;
        }
        if (hActual != nullptr) {
            if (hAnterior == nullptr)
                nave->tripHistory = hActual->siguiente;
            else
                hAnterior->siguiente = hActual->siguiente;
        }
    }

    // Eliminar de la lista global
    if (anterior == nullptr)
        globalTrips = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;

    delete actual;
    cout << "\nViaje eliminado correctamente." << endl;
}

void* buscarViajePorId(string id) {
    return findTripById(id);
}

/*
 *                        CONFIGURACIONES CRUD
 */

CrudConfig galaxyConfig = {
    "Galaxia",
    listarGalaxias,
    agregarGalaxia,
    editarGalaxia,
    eliminarGalaxia,
    buscarGalaxyPorId
};

CrudConfig shipConfig = {
    "Nave",
    listarNaves,
    agregarNave,
    editarNave,
    eliminarNave,
    buscarNavePorId
};

CrudConfig routeConfig = {
    "Ruta",
    listarRutas,
    agregarRuta,
    editarRuta,
    eliminarRuta,
    buscarRutaPorId
};

CrudConfig tripConfig = {
    "Viaje",
    listarViajes,
    registrarViaje,
    editarViaje,
    eliminarViaje,
    buscarViajePorId
};
