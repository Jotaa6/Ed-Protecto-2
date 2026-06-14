/*
 * Archivo: api_client.cpp
 * Descripcion: Implementacion del wrapper de libcurl
 * Estructuras: ResponseBuffer
 * Funciones: httpGet, writeCallback
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/api_client.h"

/**
 * @brief  Callback interno de curl que acumula bytes recibidos en el buffer
 * @param  content  puntero a los datos recibidos
 * @param  size     siempre 1
 * @param  nmemb    cantidad de bytes recibidos
 * @param  userp    puntero al ResponseBuffer donde se acumulan los datos
 * @return cantidad de bytes procesados (size * nmemb)
 */
static size_t writeCallback(void* content, size_t size, size_t nmemb, void* userp) {
    size_t totalBytes = size * nmemb;
    
    if (userp == nullptr)
        return 0;
    ResponseBuffer* buf = (ResponseBuffer*)userp;

    char* newData = (char*)realloc(buf->data, buf->size + totalBytes + 1);
    if (newData == nullptr) {
        cout << "Error: no se pudo reasignar memoria en writeCallback." << endl;
        return 0;
    }
    buf->data = newData;
    if (content == nullptr)
        return 0;

    memcpy(buf->data + buf->size, content, totalBytes);
    buf->size += totalBytes;
    buf->data[buf->size] = '\0';
    return totalBytes;
}

/**
 * @brief  Realiza una peticion HTTP GET a BASE_URL + endpoint
 *         y copia la respuesta en result
 *         Timeout de 60 segundos para tolerar cold start de la API en Render
 * @param  endpoint  ruta de la API e.g. "/galaxias"
 * @param  result    arreglo de chars donde se almacenara la respuesta
 * @param  maxLen    maximo de chars a copiar en result
 * @return void — result contiene la respuesta o cadena vacia si falla
 */
void httpGet(const char* endpoint, char* result, int maxLen) {
    result[0] = '\0';
    try {
        CURL* curl = curl_easy_init();
        if (curl == nullptr) {
            cout << "Error: no se pudo inicializar curl." << endl;
            return;
        }
        char url[512];
        snprintf(url, sizeof(url), "%s%s", BASE_URL, endpoint);

        ResponseBuffer buf;
        buf.data = (char*)malloc(1);
        buf.size = 0;
        if (buf.data == nullptr) {
            cout << "Error: no se pudo asignar memoria para el buffer." << endl;
            curl_easy_cleanup(curl);
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 300L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cout << "Error en httpGet(" << endpoint << "): "
                 << curl_easy_strerror(res) << endl;
        } else {
            strncpy(result, buf.data, maxLen - 1);
            result[maxLen - 1] = '\0';
        }

        free(buf.data);
        curl_easy_cleanup(curl);
    } catch (...) {
        cout << "Error inesperado en httpGet(" << endpoint << ")." << endl;
        result[0] = '\0';
    }
}
