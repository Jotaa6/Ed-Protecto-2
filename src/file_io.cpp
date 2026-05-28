/*
 * Archivo: file_io.cpp
 * Descripcion: Implementacion de helpers de lectura y escritura de archivos .txt en /output
 * Estructuras: ninguna propia
 * Funciones: abrirArchivo, escribirLinea, escribirEncabezado, escribirPie,
 *            escribirSeparador, cerrarArchivo, getCurrentTimestamp
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/file_io.h"

/**
 * @brief  Obtiene la fecha y hora actual como string formateado
 *         Usa localtime_s para compatibilidad con Windows
 * @param  result   arreglo de chars donde se almacena el timestamp
 * @param  maxLen   maximo de caracteres a escribir en result
 * @return void
 */
void getCurrentTimestamp(char* result, int maxLen) {
    time_t now = time(nullptr);
    struct tm t;
    localtime_s(&t, &now);
    strftime(result, maxLen, "%Y-%m-%d %H:%M:%S", &t);
}

/**
 * @brief  Abre un archivo .txt en /output/ para escritura
 *         Crea la carpeta /output si no existe usando _mkdir
 *         _mkdir no muestra error si la carpeta ya existe
 * @param  archivo   referencia a ofstream a abrir
 * @param  filename  nombre del archivo e.g. rutasMasCortas.txt
 * @return true si se abrio correctamente, false en caso de fallo
 */
bool abrirArchivo(ofstream& archivo, const char* filename) {
    try {
        _mkdir("output");
        char path[256];
        snprintf(path, sizeof(path), "output/%s", filename);
        archivo.open(path);
        if (!archivo.is_open()) {
            cout << "Error: no se pudo abrir el archivo " << path << endl;
            return false;
        }
        return true;
    } catch (...) {
        cout << "Error inesperado al abrir archivo " << filename << endl;
        return false;
    }
}

/**
 * @brief  Escribe una linea seguida de salto de linea en el archivo
 * @param  archivo  referencia a ofstream abierto
 * @param  linea    texto a escribir
 * @return void
 */
void escribirLinea(ofstream& archivo, const char* linea) {
    try {
        archivo << linea << endl;
    } catch (...) {
        cout << "Error al escribir linea en archivo." << endl;
    }
}

/**
 * @brief  Escribe encabezado de reporte formateado
 * @param  archivo  referencia a ofstream abierto
 * @param  titulo   titulo del reporte
 * @return void
 */
void escribirEncabezado(ofstream& archivo, const char* titulo) {
    char timestamp[64];
    getCurrentTimestamp(timestamp, sizeof(timestamp));
    escribirLinea(archivo, "========================================");
    escribirLinea(archivo, titulo);
    escribirLinea(archivo, timestamp);
    escribirLinea(archivo, "========================================");
}

/**
 * @brief  Escribe pie de reporte formateado
 * @param  archivo  referencia a ofstream abierto
 * @return void
 */
void escribirPie(ofstream& archivo) {
    escribirLinea(archivo, "========================================");
    escribirLinea(archivo, "Fin del reporte.");
}

/**
 * @brief  Escribe una linea separadora --- en el archivo
 * @param  archivo  referencia a ofstream abierto
 * @return void
 */
void escribirSeparador(ofstream& archivo) {
    escribirLinea(archivo, "----------------------------------------");
}

/**
 * @brief  Cierra el archivo y imprime confirmacion en terminal
 * @param  archivo   referencia a ofstream a cerrar
 * @param  filename  nombre del archivo mostrado en el mensaje
 * @return void
 */
void cerrarArchivo(ofstream& archivo, const char* filename) {
    try {
        archivo.flush();
        archivo.close();
        cout << "Archivo guardado: output/" << filename << endl;
    } catch (...) {
        cout << "Error al cerrar archivo " << filename << endl;
    }
}
