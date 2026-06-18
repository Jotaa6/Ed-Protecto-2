/*
 * Archivo: file_io.h
 * Descripcion: Helpers de lectura y escritura de archivos .txt en /output
 * Estructuras: ninguna propia
 * Funciones: abrirArchivo, escribirLinea, escribirEncabezado, escribirPie,
 *            escribirSeparador, cerrarArchivo
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <Jorge Ulate>
 */
#ifndef FILE_IO_H
#define FILE_IO_H

#include <fstream>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <direct.h>
#include "utils.h"
using namespace std;

/**
 * @brief  Abre un archivo .txt en /output/ para escritura
 *         Crea la carpeta /output si no existe usando _mkdir
 * @param  archivo   referencia a ofstream a abrir
 * @param  filename  nombre del archivo e.g. rutasMasCortas.txt
 * @return true si se abrio correctamente, false en caso de fallo
 */
bool abrirArchivo(ofstream& archivo, const char* filename);

/**
 * @brief  Escribe una linea seguida de salto de linea en el archivo
 * @param  archivo  referencia a ofstream abierto
 * @param  linea    texto a escribir
 * @return void
 */
void escribirLinea(ofstream& archivo, const char* linea);

/**
 * @brief  Escribe encabezado de reporte formateado
 *         Formato: === separator, titulo, timestamp, === separator
 *         Usado por todos los reportes y por la consulta del arbol de Kruskal
 * @param  archivo  referencia a ofstream abierto
 * @param  titulo   titulo del reporte a mostrar en el encabezado
 * @return void
 */
void escribirEncabezado(ofstream& archivo, const char* titulo);

/**
 * @brief  Escribe pie de reporte formateado
 *         Formato: === separator + Fin del reporte.
 * @param  archivo  referencia a ofstream abierto
 * @return void
 */
void escribirPie(ofstream& archivo);

/**
 * @brief  Escribe una linea separadora --- en el archivo
 * @param  archivo  referencia a ofstream abierto
 * @return void
 */
void escribirSeparador(ofstream& archivo);

/**
 * @brief  Cierra el archivo y imprime confirmacion en terminal
 * @param  archivo   referencia a ofstream a cerrar
 * @param  filename  nombre del archivo mostrado en el mensaje de confirmacion
 * @return void
 */
void cerrarArchivo(ofstream& archivo, const char* filename);

#endif
