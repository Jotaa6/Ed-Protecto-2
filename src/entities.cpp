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
 * Autores: José Pablo Barrates
 */
#include "../include/entities.h"
/*
 *                              GALAXIAS
 */
/**
 * @brief Imprime todas las galaxias almacenadas en memoria.
 * @return void
 */
void listarGalaxias() {

    if (globalGalaxias == nullptr) {
        cout << "\nNo hay galaxias registradas brou." << endl;
        return;
    }

    Galaxy* actual = globalGalaxias;

    while (actual != nullptr) {

        cout << "\n----------------------------------------" << endl;
        cout << "ID: " << actual->id << endl;
        cout << "Nombre: " << actual->name << endl;
        cout << "Codigo: " << actual->code << endl;
        cout << "Tipo: " << actual->type << endl;
        cout << "Coordenadas: (" << actual->x << ", " << actual->y << ", " << actual->z << ")" << endl;
        actual = actual->siguiente;
    }
}

/**
 * @brief Agrega una galaxia en memoria.
 *        Rechaza codigos repetidos.
 * @return void
 */
void agregarGalaxia() {

    Galaxy* nueva = new Galaxy();

    char buffer[100];

    pedirCadena("ID: ", buffer, 100);
    nueva->id = buffer;

    //Verificar ID duplicado
    if (findGalaxyById(nueva->id) != nullptr) {
        cout << "\nYa registrado." << endl;
        delete nueva;
        return;
    }

    pedirCadena("Nombre: ", buffer, 100);
    nueva->name = buffer;

    pedirCadena("Codigo: ", buffer, 100);
    nueva->code = buffer;

    pedirCadena("Tipo: ", buffer, 100);
    nueva->type = buffer;

    nueva->x = pedirFloat("Coordenada X: ");
    nueva->y = pedirFloat("Coordenada Y: ");
    nueva->z = pedirFloat("Coordenada Z: ");

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

/**
 * @brief Edita nombre o coordenadas de una galaxia.
 * @param id identificador de la galaxia.
 * @return void
 */
void editarGalaxia(string id) {

    Galaxy* galaxy = findGalaxyById(id);

    if (galaxy == nullptr) {

        cout << "\nGalaxia no encontrada." << endl;
        return;
    }
    char buffer[100];
    pedirCadena("Nuevo Nombre: ", buffer, 100);

    galaxy->name = buffer;

    galaxy->x = pedirFloat("Coordenada X: ");

    galaxy->y = pedirFloat("Coordenada Y: ");

    galaxy->z = pedirFloat("Coordenada Z: ");

    cout << "\nGalaxia editada correctamente." << endl;
}

/**
 * @brief Elimina una galaxia de memoria.
 * @param id identificador de la galaxia.
 * @return void
 */
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

/**
 * @brief Busca una galaxia por id.
 * @param id identificador.
 * @return puntero a Galaxy o nullptr.
 */
void* buscarGalaxyPorId(string id) {
    return findGalaxyById(id);
}

/*
 *                                X-WINGS (Naves)
 */

/**
 * @brief Imprime todas las naves almacenadas en memoria.
 * @return void
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

/**
 * @brief Agrega una nave en memoria.
 *        Rechaza codigos duplicados.
 * @return void
 */
void agregarNave() {

    Ship* nueva = new Ship();
    char buffer[100];

    pedirCadena("ID: ", buffer, 100);
    nueva->id = buffer;

    //Verificar ID duplicado
    if (findShipById(nueva->id) != nullptr) {
        cout << "\nYa registrado." << endl;
        delete nueva;
        return;
    }

    pedirCadena("Nombre: ", buffer, 100);
    nueva->name = buffer;

    pedirCadena("Codigo: ", buffer, 100);
    nueva->code = buffer;

    nueva->capacidad = pedirEntero("Capacidad: ");
    nueva->velocidadMax = pedirEntero("Velocidad maxima: ");

    int opcion;
    do{
        opcion=pedirEntero("Activa (1=Si,0=No): ");
    }while(opcion!=0 && opcion!=1);
    nueva->activa=(opcion==1);

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

/**
 * @brief Edita el nombre de una nave.
 * @param id identificador de la nave.
 * @return void
 */
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

/**
 * @brief Elimina una nave de memoria.
 * @param id identificador de la nave.
 * @return void
 */
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

/**
 * @brief Busca una nave por id.
 * @param id identificador.
 * @return puntero a Ship o nullptr.
 */
void* buscarNavePorId(string id) {
    return findShipById(id);
}

/*
 *                                RUTAS
 */

/**
 * @brief Imprime todas las rutas almacenadas en memoria.
 * @return void
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

/**
 * @brief Agrega una ruta en memoria y sincroniza el grafo.
 * @return void
 */
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

    do {
        nueva->cost = pedirEntero("Costo: ");

        if(nueva->cost<=0)
            cout<<"El costo debe ser mayor que cero."<<endl;

    } while(nueva->cost<=0);
    
    do {
        nueva->tiempoDias = pedirEntero("Tiempo en dias: ");

        if (nueva->tiempoDias <= 0) {
            cout << "El tiempo debe ser mayor que cero." << endl;
        }

    } while (nueva->tiempoDias <= 0);

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

    insertarArco(
        nueva->originId,
        nueva->destinationId,
        nueva->cost
    );

    cout << "\nRuta agregada correctamente." << endl;
}

/**
 * @brief Edita el costo de una ruta.
 * @param id identificador de la ruta.
 * @return void
 */
void editarRuta(string id) {

    Edge* ruta = findEdgeById(id);

    if (ruta == nullptr) {

        cout << "\nRuta no encontrada." << endl;
        return;
    }

    do {
        ruta->cost = pedirEntero("Costo: ");

        if(ruta->cost<=0)
            cout<<"El costo debe ser mayor que cero."<<endl;

    } while(ruta->cost<=0);

    actualizarCostoArco(
        ruta->originId,
        ruta->destinationId,
        ruta->cost
    );

    cout << "\nRuta editada correctamente." << endl;
}

/**
 * @brief Elimina una ruta de memoria y del grafo.
 * @param id identificador de la ruta.
 * @return void
 */
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

    eliminarArco(
        actual->originId,
        actual->destinationId
    );

    delete actual;

    cout << "\nRuta eliminada correctamente." << endl;
}

/**
 * @brief Busca una ruta por id.
 * @param id identificador.
 * @return puntero a Edge o nullptr.
 */
void* buscarRutaPorId(string id) {
    return findEdgeById(id);
}

/*
 *                                VIAJES
 */

/**
 * @brief Imprime todos los viajes almacenados en memoria.
 * @return void
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

/**
 * @brief Registra un viaje en memoria.
 * @return void
 */
void registrarViaje() {

    Trip* nuevo = new Trip();
    char buffer[100];

    pedirCadena("ID: ", buffer, 100);
    nuevo->id = buffer;

    //Verificar ID duplicado
    if (findTripById(nuevo->id) != nullptr) {
        cout << "\nYa registrado." << endl;
        delete nuevo;
        return;
    }

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

    do {
        nuevo->cost = pedirEntero("Costo: ");

        if(nuevo->cost<=0)
            cout<<"El costo debe ser mayor que cero."<<endl;

    } while(nuevo->cost<=0);

    nuevo->exitoso = confirmarAccion("El viaje fue exitoso?");

    nuevo->naveNombre = nave->name;
    nuevo->origenNombre = origen->name;
    nuevo->destinoNombre = destino->name;

    nuevo->siguiente = nullptr;

    /*Agregar a la lista global*/
    if (globalTrips == nullptr) {

        globalTrips = nuevo;

    } else {

        Trip* temp = globalTrips;

        while (temp->siguiente != nullptr)
            temp = temp->siguiente;

        temp->siguiente = nuevo;
    }

    /* Si es el primer viaje de la nave, se almacena como referencia
   al inicio de su historial. Los demas viajes se obtienen
   recorriendo la lista global y filtrando por shipId. */

    if (nave->tripHistory == nullptr) {
        nave->tripHistory = nuevo;
    }

    cout << "\nViaje registrado correctamente." << endl;
}

/**
 * @brief Edita la fecha y costo de un viaje.
 * @param id identificador del viaje.
 * @return void
 */
void editarViaje(string id) {

    Trip* viaje = findTripById(id);

    if (viaje == nullptr) {

        cout << "\nViaje no encontrado." << endl;
        return;
    }

    char buffer[100];

    pedirCadena("Nueva fecha: ", buffer, 100);
    viaje->date = buffer;

    do {
        viaje->cost = pedirEntero("Costo: ");

        if(viaje->cost<=0)
            cout<<"El costo debe ser mayor que cero."<<endl;

    } while(viaje->cost<=0);

    cout << "\nViaje editado correctamente." << endl;
}

/**
 * @brief Elimina un viaje de memoria y del historial de la nave.
 * @param id identificador del viaje.
 * @return void
 */
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

    if (anterior == nullptr)
        globalTrips = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;

    delete actual;

    cout << "\nViaje eliminado correctamente." << endl;
}

/**
 * @brief Busca un viaje por id.
 * @param id identificador.
 * @return puntero a Trip o nullptr.
 */
void* buscarViajePorId(string id) {
    return findTripById(id);
}
/*
 *                        CONFIGURACIONES CRUD
 */

/**
 * @brief Configuracion CRUD para la entidad Galaxy.
 */
CrudConfig galaxyConfig = {
    "Galaxia",
    listarGalaxias,
    agregarGalaxia,
    editarGalaxia,
    eliminarGalaxia,
    buscarGalaxyPorId
};

/**
 * @brief Configuracion CRUD para la entidad Ship.
 */
CrudConfig shipConfig = {
    "Nave",
    listarNaves,
    agregarNave,
    editarNave,
    eliminarNave,
    buscarNavePorId
};

/**
 * @brief Configuracion CRUD para la entidad Route.
 */
CrudConfig routeConfig = {
    "Ruta",
    listarRutas,
    agregarRuta,
    editarRuta,
    eliminarRuta,
    buscarRutaPorId
};

/**
 * @brief Configuracion CRUD para la entidad Trip.
 */
CrudConfig tripConfig = {
    "Viaje",
    listarViajes,
    registrarViaje,
    editarViaje,
    eliminarViaje,
    buscarViajePorId
};
