## Guardianes de la galaxia RRA 🦝🎧🌳


## Enunciado

La galaxia es una estructura de complejidad inherente, formada por billones de estrellas, planetas y nebulosas
interconectadas en una red que desafía la comprensión. Al igual que un laberinto mitológico, el universo no fue
diseñado para confundirnos, pero su inmensidad y sus rutas entrelazadas lo convierten en un desafío para
cualquier explorador. El término galaxia proviene del griego galaxias (“círculo lechoso”), evocando la Vía Láctea,
que en muchas culturas antiguas se veía como un sendero divino o un río celestial.
Existen 2 formas de interpretar su estructura, una galaxia elíptica simple, donde las estrellas siguen órbitas
predecibles y sin bifurcaciones significativas, y también puede ser una galaxia en espiral, con brazos que se
extienden en rutas enredadas, agujeros de gusano como atajos y sistemas binarios que actúan como nodos con
múltiples aristas.
Los Guardianes de la Galaxia, son un equipo de héroes especializado en resolver conflictos intergalácticos o
internos a los distintos planetas que conforman las distintas galaxias del cosmos. Por lo que el transporte entre
distintos puntos es una constante en su vida cotidiana. Para optimizar el tiempo de llegada entre los sistemas
estelares, el capitán ha ordenado que se desarrolle un sistema computacional que modele todas las rutas
posibles, determine las conexiones más eficientes y gestione los registros de viajes y rutas intergalácticas.


Para esto, se deberá:
⍟ Visitar el siguiente enlace https://galaxias-mock-api.onrender.com/ para visualizar la información
necesaria para armar la estructura del grafo. Dicha información será brindada en formato JSON por lo que
deberán utilizar la librería curl para poder consumir el servicio.
⍟ El resumen de los endpoints es el siguiente:
⍟ Representar el grafo usando listas o matrices según criterio a partir de los endpoints.
⍟ Implementar una modificación del algoritmo de Kruskal para encontrar una red galáctica de bajo costo.
⍟ Registrar rutas visitadas por naves en estructuras auxiliares.
⍟ Guardar resultados o configuraciones en archivo

Algoritmo de Kruskal modificado:
Consiste en una versión aleatoria del algoritmo de Kruskal. La idea de este algoritmo es generar una lista de arcos
ordenados de menor a mayor peso e ir agregando aristas al grafo resultante sin que se generen ciclos. La
modificación consiste en que la lista de arcos va a estar ordenada de forma aleatoria.
1. Consumir el endpoint /grafo/kruskal que ya contiene las aristas en orden aleatorio.
2. Crear conjuntos, poner cada nodo dentro del grafo en un conjunto diferente.
3. Por cada arco en la lista
a. Si los nodos que une el arco se encuentran en conjuntos diferentes
b. Agregar el arco en el grafo resultante
c. Unir los conjuntos a los que pertenecen los nodos que se unieron
Para este algoritmo debe utilizarse alguna estructura que permita representar conjuntos. No importa mucho si se
crea una lista desordenada de arcos o si se escoge un arco aleatoriamente de la lista cada vez, el resultado es el
mismo.
Este algoritmo tiende a producir patrones regulares que son relativamente fáciles de resolver

Información que debe registrarse
 Nombre y código de galaxia.
 Coordenadas X, Y, Z.
 Costos de viajes entre galaxias (tiempo de duración para llegar).
 Registro de rutas ya utilizadas.
 Naves registradas y su historial de viajes.
 Debe validar que no se ingresen datos repetidos.
 Asociar correctamente las entidades.
Consultas
 Mostrar todas las rutas posibles desde una galaxia
 Indicar la ruta de menor costo entre dos galaxias
 Mostrar el árbol de conexiones resultante del algoritmo de Kruskal
 Consultar el historial de viajes por nave
Reportes
 Archivo con las rutas más cortas generadas
 Archivo con árbol de expansiones (ruta galáctica optimizada)
 Informe con estadísticas como:
o Cantidad de rutas calculadas
o Galaxias con mayor conectividad
o Comparación entre rutas originales y optimizadas

Interfaz de Usuario
 Menú general de navegación por secciones
 Submenús para cada entidad con opciones CRUD
 Diseño limpio, navegación intuitiva y respuestas amigables en cada operación
 Usar funciones organizadas para cada tipo de operación
 Debe mostrar mensajes claros al usuario final de todo lo que pasa dentro de su programa (ejemplo:
“Dato ya insertado”) 
Documentación Externa
 Portada.
 Descripción del problema y justificación.
 Solución propuesta (ambiente de desarrollo, estructuras de datos utilizadas, funciones, instrucciones
para ejecutar el programa, minuta de trabajo por cada estudiante).
 Análisis de resultados (resultados finales, indicando que partes están completas, cuáles defectuosas y
cuáles no se realizaron).
 Conclusiones y recomendaciones con respecto al proyecto.
 Bibliografía.
Documentación Interna
 Fecha de inicio y última modificación.
 Nombre de los integrantes del grupo de trabajo.
 Descripción para cada estructura y su uso en el programa.



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
