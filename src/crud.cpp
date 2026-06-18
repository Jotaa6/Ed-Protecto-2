/*
 * Archivo: crud.cpp
 * Descripcion: Implementacion del motor CRUD generico
 * Estructuras: CrudConfig
 * Funciones: runCrud, promptAndValidateId
 * Creado: 7/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#include "../include/crud.h"

/**
 * @brief  Solicita y valida un id de forma generica
 * @param  config  CrudConfig de la entidad siendo buscada
 * @return id ingresado por el usuario, o "" si no se encuentra
 */
string promptAndValidateId(CrudConfig config) {
    string id;

    cout << "Ingrese el ID de " << config.entityName << ": ";
    cin >> id;

    if (id == "") {
        cout << "ID invalido." << endl;
        return "";
    }

    if (config.findById == nullptr) {
        cout << "No existe funcion de busqueda para " << config.entityName << "." << endl;
        return "";
    }

    if (config.findById(id) == nullptr) {
        cout << config.entityName << " no encontrado." << endl;
        return "";
    }

    return id;
}

/**
 * @brief  Ejecuta el submenu CRUD generico para cualquier entidad
 *         Contiene el loop do-while, switch y try-catch por opcion
 *         Escrito una vez, usado por todas las entidades
 * @param  config  struct CrudConfig con nombre de entidad y punteros a funciones
 * @return void
 */
void runCrud(CrudConfig config) {
    int opcion = 0;

    do {
        cout << "\n=== CRUD DE " << config.entityName << " ===" << endl;
        cout << "1. Listar" << endl;
        cout << "2. Agregar" << endl;
        cout << "3. Editar" << endl;
        cout << "4. Eliminar" << endl;
        cout << "5. Buscar por ID" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Opcion invalida." << endl;
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1:
                try {
                    if (config.listAll != nullptr) {
                        config.listAll();
                    } else {
                        cout << "Funcion listar no disponible." << endl;
                    }
                } catch (...) {
                    cout << "Ocurrio un error al listar." << endl;
                }
                break;

            case 2:
                try {
                    if (config.add != nullptr) {
                        config.add();
                    } else {
                        cout << "Funcion agregar no disponible." << endl;
                    }
                } catch (...) {
                    cout << "Ocurrio un error al agregar." << endl;
                }
                break;

            case 3:
                try {
                    if (config.edit != nullptr) {
                        string id = promptAndValidateId(config);
                        if (id != "") {
                            config.edit(id);
                        }
                    } else {
                        cout << "Funcion editar no disponible." << endl;
                    }
                } catch (...) {
                    cout << "Ocurrio un error al editar." << endl;
                }
                break;

            case 4:
                try {
                    if (config.remove != nullptr) {
                        string id = promptAndValidateId(config);
                        if (id != "") {
                            config.remove(id);
                        }
                    } else {
                        cout << "Funcion eliminar no disponible." << endl;
                    }
                } catch (...) {
                    cout << "Ocurrio un error al eliminar." << endl;
                }
                break;

            case 5:
                try {
                    string id = promptAndValidateId(config);
                    if (id != "") {
                        void* item = config.findById(id);
                        if (item != nullptr) {
                            cout << config.entityName << " encontrado:" << endl;
                            if (config.printDetail != nullptr) {
                                config.printDetail(item);
                            } else {
                                cout << "(No hay funcion de detalle para esta entidad.)" << endl;
                            }
                        }
                    }
                } catch (...) {
                    cout << "Ocurrio un error al buscar." << endl;
                }
                break;

            case 0:
                cout << "Regresando al menu anterior..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
                break;
        }

    } while (opcion != 0);
}
