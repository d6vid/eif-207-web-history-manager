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

//Controlador para gestionar la interacci�n del usuario con el navegador web

class BrowserController {
public:
	//Inicia el controlador del navegador, mostranro el men� y manejando las opciones del usuario
	void start();
	//Constructor de la clase
	BrowserController();
private:
	//Instancia del navegador gestionado�por el controlador
	Browser browser;
	
	// -> Prop�sito general
	//Muestra el men� principal del navegador
	void showMenu();
	//Maneja la opci�n seleccionada por el usuario en el men�
	void handleMenuOption();

	// M�todo que navega a un sitio web ingresado por el usuario
	void goToWebsite();

	// Abre una nueva pesta�a en el navegador
	void openTab();

	// Gesti�n de Marcadores
	//Agrega un marcador para la p�gina web actual
	void addBookmark();
	//Este m�todo muestra y permite seleccionar un marcador basado en una etiqueta
	void showAndSelectBookmark();

	// Gesti�n de Seguridad
	//Activa o desactiva el modo de navegaci�n privada
	void switchIncognito();

	// Persistencia de Datos
	//Importa p�ginas web desde un archivo
	void importPages();
	//Muestra el men� de selecci�n para importar o exportar sesiones.
	void importExportSelectMenu();
	// Muestra el men� de importaci�n y devuelve la opci�n seleccionada por el usuario
	std::string importMenu();
	//Muestra el men� de exportaci�n y devuelve la opci�n seleccionada por el usuario.
	std::string exportMenu();
	//Exporta la sesi�n actual a un archivo
	void exportSession();
	//Importa una sesi�n desde un archivo	
	void importSession();

	void applyPolicies();
};