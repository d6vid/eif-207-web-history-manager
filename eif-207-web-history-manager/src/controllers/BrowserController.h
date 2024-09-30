#pragma once

#define NOMINMAX

#include "Browser.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <sstream>
#include <limits>

//Controlador para gestionar la interacción del usuario con el navegador web

class BrowserController {
public:
	//Inicia el controlador del navegador, mostranro el menú y manejando las opciones del usuario
	void start();
	//Constructor de la clase
	BrowserController();
private:
	//Instancia del navegador gestionado´por el controlador
	Browser browser;
	
	// -> Propósito general
	//Muestra el menú principal del navegador
	void showMenu();
	//Maneja la opción seleccionada por el usuario en el menú
	void handleMenuOption();

	// Método que navega a un sitio web ingresado por el usuario
	void goToWebsite();

	// Abre una nueva pestaña en el navegador
	void openTab();

	// Gestión de Marcadores
	//Agrega un marcador para la página web actual
	void addBookmark();
	//Este método muestra y permite seleccionar un marcador basado en una etiqueta
	void showAndSelectBookmark();

	// Gestión de Seguridad
	//Activa o desactiva el modo de navegación privada
	void switchIncognito();

	// Persistencia de Datos
	//Importa páginas web desde un archivo
	void importPages();
	//Muestra el menú de selección para importar o exportar sesiones.
	void importExportSelectMenu();
	// Muestra el menú de importación y devuelve la opción seleccionada por el usuario
	std::string importMenu();
	//Muestra el menú de exportación y devuelve la opción seleccionada por el usuario.
	std::string exportMenu();
	//Exporta la sesión actual a un archivo
	void exportSession();
	//Importa una sesión desde un archivo	
	void importSession();

	void applyPolicies();
};