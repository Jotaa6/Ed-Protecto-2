#Guardianes de la galaxia RRA


## Plantillas de documentacion interna

### Encabezado de archivo
Todo archivo .h y .cpp debe comenzar con:

    /*
     * Archivo: <nombre del archivo>
     * Descripcion: <que hace este archivo>
     * Estructuras: <structs definidos aqui>
     * Funciones: <funciones definidas aqui>
     * Creado: <fecha>
     * Ultima modificacion: <fecha>
     * Autores: <integrantes del equipo>
     */

### Comentario de funcion
Encima de cada funcion:

    /**
     * @brief  <descripcion en una linea>
     * @param  <nombreParam> <que es este parametro>
     * @return <que retorna, o void si no retorna nada>
     */

### Comentario de struct
Encima de cada struct:

    /**
     * @brief  <que representa este struct>
     * @field  <nombreCampo> <que almacena este campo>
     */
