/*
 * Archivo: menu.h
 * Descripcion: Menu principal y submenus de navegacion
 * Estructuras: ninguna propia
 * Funciones: showMainMenu, showGalaxiasSubmenu, showRutasSubmenu,
 *            showNavesSubmenu, showViajesSubmenu, showConsultasSubmenu,
 *            showReportesSubmenu
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <Jorge Ulate>
 */
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "entities.h"
#include "crud.h"
#include "queries.h"
#include "reports.h"
#include "utils.h"
#include "data_loader.h"
using namespace std;

/**
 * @brief  Menu principal — enruta a todos los submenus
 *         do-while + switch, sale en opcion 0
 * @return void
 */
void showMainMenu();

/**
 * @brief  Submenu Galaxias — ejecuta runCrud(galaxyConfig)
 * @return void
 */
void showGalaxiasSubmenu();

/**
 * @brief  Submenu Rutas — ejecuta runCrud(routeConfig)
 * @return void
 */
void showRutasSubmenu();

/**
 * @brief  Submenu Naves — ejecuta runCrud(shipConfig)
 * @return void
 */
void showNavesSubmenu();

/**
 * @brief  Submenu Viajes — ejecuta runCrud(tripConfig)
 * @return void
 */
void showViajesSubmenu();

/**
 * @brief  Submenu Consultas — cuatro consultas disponibles
 *         do-while + switch
 * @return void
 */
void showConsultasSubmenu();

/**
 * @brief  Submenu Reportes — tres reportes mas generar todos
 *         do-while + switch
 * @return void
 */
void showReportesSubmenu();

#endif
