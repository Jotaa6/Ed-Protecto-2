/*
 * Archivo: api_client.h
 * Descripcion: Wrapper de libcurl para peticiones HTTP GET
 * Estructuras: ResponseBuffer
 * Funciones: httpGet, writeCallback
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <curl/curl.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

const char* const BASE_URL = "https://galaxias-mock-api.onrender.com";

/**
 * @brief  Buffer interno usado por curl para acumular bytes de respuesta
 * @field  data  arreglo de chars en heap con el contenido de la respuesta
 * @field  size  cantidad actual de bytes almacenados en data
 */
struct ResponseBuffer {
    char* data;
    int   size;
};

/**
 * @brief  Realiza una peticion HTTP GET a BASE_URL + endpoint
 *         y copia la respuesta en result
 * @param  endpoint  ruta de la API e.g. "/galaxias"
 * @param  result    arreglo de chars donde se almacenara la respuesta
 * @param  maxLen    maximo de chars a copiar en result
 * @return void — result contiene la respuesta o cadena vacia si falla
 */
void httpGet(const char* endpoint, char* result, int maxLen);

#endif
