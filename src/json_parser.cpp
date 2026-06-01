/*
 * Archivo: json_parser.cpp
 * Descripcion: Implementacion del parseo de JSON en tres capas
 *              Campos reales de la API:
 *              Galaxy: id(string), codigo, nombre, x, y, z
 *              Edge:   id(string), origen_id, destino_id, costo(float)
 *              Ship:   id(string), nombre
 *              Trip:   id(string), nave_id, ruta_id, fecha, costo_real(float)
 * Estructuras: ninguna propia
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/json_parser.h"

// ── Capa 1 — extractores crudos ───────────────────────────────────────────

/**
 * @brief  Extrae valor string para una clave en un objeto JSON plano
 * @param  json    JSON crudo
 * @param  key     nombre del campo a buscar
 * @param  result  arreglo de chars de salida
 * @param  maxLen  max chars a copiar en result
 * @return void
 */
void extractString(const char* json, const char* key,
                   char* result, int maxLen) {
    result[0] = '\0';
    if (json == nullptr || key == nullptr) return;

    char searchKey[256];
    snprintf(searchKey, sizeof(searchKey), "\"%s\"", key);
    const char* pos = strstr(json, searchKey);
    if (pos == nullptr) return;

    pos = strchr(pos, ':');
    if (pos == nullptr) return;
    pos++;
    while (*pos == ' ' || *pos == '\t') pos++;

    if (*pos == '"') {
        pos++;
        int i = 0;
        while (*pos != '"' && *pos != '\0' && i < maxLen - 1)
            result[i++] = *pos++;
        result[i] = '\0';
    } else {
        int i = 0;
        while (*pos != ',' && *pos != '}' &&
               *pos != '\0' && i < maxLen - 1)
            result[i++] = *pos++;
        result[i] = '\0';
    }
}

/**
 * @brief  Extrae valor int para una clave en un objeto JSON plano
 * @param  json  JSON crudo
 * @param  key   nombre del campo a buscar
 * @return int extraido, o -1 si no se encuentra
 */
int extractInt(const char* json, const char* key) {
    char buf[64];
    extractString(json, key, buf, sizeof(buf));
    if (buf[0] == '\0') return -1;
    return atoi(buf);
}

/**
 * @brief  Extrae valor float para una clave en un objeto JSON plano
 * @param  json  JSON crudo
 * @param  key   nombre del campo a buscar
 * @return float extraido, o 0.0 si no se encuentra
 */
float extractFloat(const char* json, const char* key) {
    char buf[64];
    extractString(json, key, buf, sizeof(buf));
    if (buf[0] == '\0') return 0.0f;
    return (float)atof(buf);
}

/**
 * @brief  Extrae valor bool para una clave en un objeto JSON plano
 * @param  json  JSON crudo
 * @param  key   nombre del campo a buscar
 * @return true si el valor es "true", false en caso contrario
 */
bool extractBool(const char* json, const char* key) {
    char buf[16];
    extractString(json, key, buf, sizeof(buf));
    return (strcmp(buf, "true") == 0);
}

/**
 * @brief  Divide arreglo JSON en strings de objetos o sub-arreglos individuales
 * @param  jsonArray  arreglo JSON crudo
 * @param  results    arreglo de salida
 * @param  maxItems   max elementos a extraer
 * @param  count      salida — numero de elementos encontrados
 * @return void
 */
void splitJsonArray(const char* jsonArray, char results[][2048],
                    int maxItems, int& count) {
    count = 0;
    if (jsonArray == nullptr) return;

    const char* pos = strchr(jsonArray, '[');
    if (pos == nullptr) return;
    pos++;

    while (*pos != '\0' && count < maxItems) {
        while (*pos == ' ' || *pos == '\t' ||
               *pos == '\n' || *pos == ',') pos++;
        if (*pos == ']' || *pos == '\0') break;

        if (*pos == '{') {
            int depth = 0;
            const char* start = pos;
            while (*pos != '\0') {
                if (*pos == '{') depth++;
                else if (*pos == '}') {
                    depth--;
                    if (depth == 0) { pos++; break; }
                }
                pos++;
            }
            int len = (int)(pos - start);
            if (len > 2047) len = 2047;
            strncpy(results[count], start, len);
            results[count][len] = '\0';
            count++;
        } else if (*pos == '[') {
            int depth = 0;
            const char* start = pos;
            while (*pos != '\0') {
                if (*pos == '[') depth++;
                else if (*pos == ']') {
                    depth--;
                    if (depth == 0) { pos++; break; }
                }
                pos++;
            }
            int len = (int)(pos - start);
            if (len > 2047) len = 2047;
            strncpy(results[count], start, len);
            results[count][len] = '\0';
            count++;
        } else {
            pos++;
        }
    }
}

/**
 * @brief  Extrae string de objeto anidado para una clave
 * @param  json    JSON crudo
 * @param  key     campo cuyo valor es un objeto
 * @param  result  salida
 * @param  maxLen  max chars
 * @return void
 */
void extractObject(const char* json, const char* key,
                   char* result, int maxLen) {
    result[0] = '\0';
    if (json == nullptr || key == nullptr) return;
    char searchKey[256];
    snprintf(searchKey, sizeof(searchKey), "\"%s\"", key);
    const char* pos = strstr(json, searchKey);
    if (pos == nullptr) return;
    pos = strchr(pos, ':');
    if (pos == nullptr) return;
    pos++;
    while (*pos == ' ' || *pos == '\t') pos++;
    if (*pos != '{') return;
    int depth = 0;
    const char* start = pos;
    while (*pos != '\0') {
        if (*pos == '{') depth++;
        else if (*pos == '}') {
            depth--;
            if (depth == 0) { pos++; break; }
        }
        pos++;
    }
    int len = (int)(pos - start);
    if (len > maxLen - 1) len = maxLen - 1;
    strncpy(result, start, len);
    result[len] = '\0';
}

/**
 * @brief  Extrae string de arreglo anidado para una clave
 * @param  json    JSON crudo
 * @param  key     campo cuyo valor es un arreglo
 * @param  result  salida
 * @param  maxLen  max chars
 * @return void
 */
void extractNestedArray(const char* json, const char* key,
                        char* result, int maxLen) {
    result[0] = '\0';
    if (json == nullptr || key == nullptr) return;
    char searchKey[256];
    snprintf(searchKey, sizeof(searchKey), "\"%s\"", key);
    const char* pos = strstr(json, searchKey);
    if (pos == nullptr) return;
    pos = strchr(pos, ':');
    if (pos == nullptr) return;
    pos++;
    while (*pos == ' ' || *pos == '\t') pos++;
    if (*pos != '[') return;
    int depth = 0;
    const char* start = pos;
    while (*pos != '\0') {
        if (*pos == '[') depth++;
        else if (*pos == ']') {
            depth--;
            if (depth == 0) { pos++; break; }
        }
        pos++;
    }
    int len = (int)(pos - start);
    if (len > maxLen - 1) len = maxLen - 1;
    strncpy(result, start, len);
    result[len] = '\0';
}

// ── Capa 2 — un parser por struct ─────────────────────────────────────────

/**
 * @brief  Parsea un objeto JSON en Galaxy
 *         Campos: id, codigo, nombre, tipo, x, y, z
 * @param  jsonObject  JSON crudo de una galaxia
 * @return nuevo Galaxy* en heap, o nullptr si falla
 */
Galaxy* parseGalaxia(const char* jsonObject) {
    if (jsonObject == nullptr || jsonObject[0] == '\0') return nullptr;
    Galaxy* g = new Galaxy();
    char buf[256];
    extractString(jsonObject, "id",     buf, sizeof(buf)); g->id   = string(buf);
    extractString(jsonObject, "nombre", buf, sizeof(buf)); g->name = string(buf);
    extractString(jsonObject, "codigo", buf, sizeof(buf)); g->code = string(buf);
    extractString(jsonObject, "tipo",   buf, sizeof(buf)); g->type = string(buf);
    g->x         = extractFloat(jsonObject, "x");
    g->y         = extractFloat(jsonObject, "y");
    g->z         = extractFloat(jsonObject, "z");
    g->siguiente = nullptr;
    return g;
}

/**
 * @brief  Parsea un objeto JSON en Edge
 *         Campos: id, origen_id, destino_id, tipo, costo, tiempo_dias, activa
 * @param  jsonObject  JSON crudo de una ruta
 * @return nuevo Edge* en heap, o nullptr si falla
 */
Edge* parseRuta(const char* jsonObject) {
    if (jsonObject == nullptr || jsonObject[0] == '\0') return nullptr;
    Edge* e = new Edge();
    char buf[256];
    extractString(jsonObject, "id",         buf, sizeof(buf)); e->id            = string(buf);
    extractString(jsonObject, "origen_id",  buf, sizeof(buf)); e->originId      = string(buf);
    extractString(jsonObject, "destino_id", buf, sizeof(buf)); e->destinationId = string(buf);
    extractString(jsonObject, "tipo",       buf, sizeof(buf)); e->tipo          = string(buf);
    e->cost       = extractFloat(jsonObject, "costo");
    e->tiempoDias = extractFloat(jsonObject, "tiempo_dias");
    e->activa     = extractBool(jsonObject,  "activa");
    e->siguiente  = nullptr;
    return e;
}

/**
 * @brief  Parsea un objeto JSON en Ship
 *         Campos: id, codigo, nombre, capacidad, velocidad_max, activa
 * @param  jsonObject  JSON crudo de una nave
 * @return nuevo Ship* en heap, o nullptr si falla
 */
Ship* parseNave(const char* jsonObject) {
    if (jsonObject == nullptr || jsonObject[0] == '\0') return nullptr;
    Ship* s = new Ship();
    char buf[256];
    extractString(jsonObject, "id",     buf, sizeof(buf)); s->id   = string(buf);
    extractString(jsonObject, "nombre", buf, sizeof(buf)); s->name = string(buf);
    extractString(jsonObject, "codigo", buf, sizeof(buf)); s->code = string(buf);
    s->capacidad    = extractInt(jsonObject,  "capacidad");
    s->velocidadMax = extractInt(jsonObject,  "velocidad_max");
    s->activa       = extractBool(jsonObject, "activa");
    s->tripHistory  = nullptr;
    s->siguiente    = nullptr;
    return s;
}

/**
 * @brief  Parsea un objeto JSON en Trip
 *         Campos: id, nave_id, ruta_id, fecha, costo_real, exitoso,
 *                 nave_nombre, origen_nombre, destino_nombre
 * @param  jsonObject  JSON crudo de un viaje
 * @return nuevo Trip* en heap, o nullptr si falla
 */
Trip* parseViaje(const char* jsonObject) {
    if (jsonObject == nullptr || jsonObject[0] == '\0') return nullptr;
    Trip* t = new Trip();
    char buf[256];
    extractString(jsonObject, "id",             buf, sizeof(buf)); t->id            = string(buf);
    extractString(jsonObject, "nave_id",         buf, sizeof(buf)); t->shipId        = string(buf);
    extractString(jsonObject, "ruta_id",         buf, sizeof(buf)); t->rutaId        = string(buf);
    extractString(jsonObject, "fecha",           buf, sizeof(buf)); t->date          = string(buf);
    extractString(jsonObject, "nave_nombre",     buf, sizeof(buf)); t->naveNombre    = string(buf);
    extractString(jsonObject, "origen_nombre",   buf, sizeof(buf)); t->origenNombre  = string(buf);
    extractString(jsonObject, "destino_nombre",  buf, sizeof(buf)); t->destinoNombre = string(buf);
    t->cost      = extractFloat(jsonObject, "costo_real");
    t->exitoso   = extractBool(jsonObject,  "exitoso");
    t->siguiente = nullptr;
    return t;
}

// ── Capa 3 — una funcion por endpoint ─────────────────────────────────────

/**
 * @brief  Parsea GET /galaxias en lista enlazada de Galaxy
 * @param  json  respuesta del endpoint — arreglo JSON directo
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseGalaxias(const char* json, Galaxy*& head) {
    head = nullptr;
    if (json == nullptr || json[0] == '\0') return;
    char objects[500][2048];
    int count = 0;
    splitJsonArray(json, objects, 500, count);
    Galaxy* tail = nullptr;
    for (int i = 0; i < count; i++) {
        Galaxy* g = parseGalaxia(objects[i]);
        if (g == nullptr) continue;
        if (head == nullptr) { head = g; tail = g; }
        else { tail->siguiente = g; tail = g; }
    }
}

/**
 * @brief  Parsea GET /galaxias/:id en un Galaxy
 * @param  json  respuesta del endpoint
 * @return nuevo Galaxy* en heap, o nullptr si falla
 */
Galaxy* parseGalaxiaById(const char* json) {
    return parseGalaxia(json);
}

/**
 * @brief  Parsea GET /rutas en lista enlazada de Edge
 * @param  json  respuesta del endpoint — arreglo JSON directo
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseRutas(const char* json, Edge*& head) {
    head = nullptr;
    if (json == nullptr || json[0] == '\0') return;
    char objects[500][2048];
    int count = 0;
    splitJsonArray(json, objects, 500, count);
    Edge* tail = nullptr;
    for (int i = 0; i < count; i++) {
        Edge* e = parseRuta(objects[i]);
        if (e == nullptr) continue;
        if (head == nullptr) { head = e; tail = e; }
        else { tail->siguiente = e; tail = e; }
    }
}

/**
 * @brief  Parsea GET /rutas/:id en un Edge
 * @param  json  respuesta del endpoint
 * @return nuevo Edge* en heap, o nullptr si falla
 */
Edge* parseRutaById(const char* json) {
    return parseRuta(json);
}

/**
 * @brief  Parsea GET /naves en lista enlazada de Ship
 * @param  json  respuesta del endpoint — arreglo JSON directo
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseNaves(const char* json, Ship*& head) {
    head = nullptr;
    if (json == nullptr || json[0] == '\0') return;
    char objects[500][2048];
    int count = 0;
    splitJsonArray(json, objects, 500, count);
    Ship* tail = nullptr;
    for (int i = 0; i < count; i++) {
        Ship* s = parseNave(objects[i]);
        if (s == nullptr) continue;
        if (head == nullptr) { head = s; tail = s; }
        else { tail->siguiente = s; tail = s; }
    }
}

/**
 * @brief  Parsea GET /naves/:id en un Ship
 * @param  json  respuesta del endpoint
 * @return nuevo Ship* en heap, o nullptr si falla
 */
Ship* parseNaveById(const char* json) {
    return parseNave(json);
}

/**
 * @brief  Parsea GET /historial en lista enlazada de Trip
 * @param  json  respuesta del endpoint — arreglo JSON directo
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseHistorial(const char* json, Trip*& head) {
    head = nullptr;
    if (json == nullptr || json[0] == '\0') return;
    char objects[500][2048];
    int count = 0;
    splitJsonArray(json, objects, 500, count);
    Trip* tail = nullptr;
    for (int i = 0; i < count; i++) {
        Trip* t = parseViaje(objects[i]);
        if (t == nullptr) continue;
        if (head == nullptr) { head = t; tail = t; }
        else { tail->siguiente = t; tail = t; }
    }
}

/**
 * @brief  Parsea GET /historial/:id en un Trip
 * @param  json  respuesta del endpoint
 * @return nuevo Trip* en heap, o nullptr si falla
 */
Trip* parseViajeById(const char* json) {
    return parseViaje(json);
}

/**
 * @brief  Parsea GET /naves/:id/historial en lista enlazada de Trip
 * @param  json  respuesta del endpoint
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseHistorialNave(const char* json, Trip*& head) {
    parseHistorial(json, head);
}

/**
 * @brief  Parsea GET /grafo en listas de Galaxy y Edge
 *         El endpoint devuelve objeto con "nodos" y "aristas"
 * @param  json   respuesta del endpoint
 * @param  gHead  salida — cabeza de la lista de Galaxy
 * @param  eHead  salida — cabeza de la lista de Edge
 * @return void
 */
void parseGrafo(const char* json, Galaxy*& gHead, Edge*& eHead) {
    gHead = nullptr;
    eHead = nullptr;
    if (json == nullptr || json[0] == '\0') return;
    char nodesArray[65536];
    char edgesArray[65536];
    extractNestedArray(json, "nodos",   nodesArray, sizeof(nodesArray));
    extractNestedArray(json, "aristas", edgesArray, sizeof(edgesArray));
    parseGalaxias(nodesArray, gHead);
    parseRutas(edgesArray,    eHead);
}

/**
 * @brief  Parsea GET /grafo/kruskal en lista enlazada de Edge
 *         El endpoint devuelve objeto con "aristas" en orden aleatorio
 * @param  json  respuesta del endpoint
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseKruskal(const char* json, Edge*& head) {
    head = nullptr;
    if (json == nullptr || json[0] == '\0') return;
    char edgesArray[65536];
    extractNestedArray(json, "aristas", edgesArray, sizeof(edgesArray));
    parseRutas(edgesArray, head);
}

/**
 * @brief  Parsea GET /grafo/adyacencia en matriz dinamica float**
 *         El endpoint devuelve objeto con "orden", "nodos" y "matriz"
 *         Los valores pueden ser null (0.0) o float
 *         Quien llama es responsable de liberar la memoria
 * @param  json    respuesta del endpoint
 * @param  matrix  salida — matriz dinamica float**
 * @param  size    salida — numero de filas y columnas
 * @return void
 */
void parseAdyacencia(const char* json, float**& matrix, int& size) {
    matrix = nullptr;
    size   = 0;
    if (json == nullptr || json[0] == '\0') return;

    char matrizArray[65536];
    extractNestedArray(json, "matriz", matrizArray, sizeof(matrizArray));
    if (matrizArray[0] == '\0') return;

    char rows[100][2048];
    int rowCount = 0;
    splitJsonArray(matrizArray, rows, 100, rowCount);
    if (rowCount == 0) return;

    size   = rowCount;
    matrix = new float*[size];

    for (int i = 0; i < size; i++) {
        matrix[i] = new float[size];
        const char* pos = rows[i];
        while (*pos != '[' && *pos != '\0') pos++;
        if (*pos == '[') pos++;

        int j = 0;
        while (*pos != ']' && *pos != '\0' && j < size) {
            while (*pos == ' ' || *pos == '\t' ||
                   *pos == '\n' || *pos == ',') pos++;
            if (*pos == ']' || *pos == '\0') break;

            if (strncmp(pos, "null", 4) == 0) {
                matrix[i][j] = 0.0f;
                pos += 4;
            } else {
                char numBuf[64];
                int k = 0;
                while (*pos != ',' && *pos != ']' &&
                       *pos != '\0' && k < 63)
                    numBuf[k++] = *pos++;
                numBuf[k]    = '\0';
                matrix[i][j] = (float)atof(numBuf);
            }
            j++;
        }
        while (j < size) matrix[i][j++] = 0.0f;
    }
}
