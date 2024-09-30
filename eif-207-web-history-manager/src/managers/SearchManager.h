#pragma once

#include <vector>
#include <optional>
#include <sstream>
#include "WebPage.h"

//Gestiona un vector de páginas web, permitiendo agregar, buscar y cargar páginas desde un archivo

class SearchManager {
public:
	//Crea una instancia de SearchManager
	static SearchManager create(const std::vector<WebPage>& pages);
	//Agrega una página web a la colección y retorna true si la página se agregó correctamente
	const bool add(const WebPage& page);
	//Este método busca una página web por URL
	std::optional<WebPage> findByUrl(const std::string& url);
	//Carga páginas web desde un archivo
	void loadFromFile(std::ifstream& in);
	//Destructor de la clase SearchManager
	~SearchManager();
private:
	//Constructor privado para inicializar con páginas web
	SearchManager(const std::vector<WebPage>& pages = {});
	//Colección de páginas web siendo gestionadas
	std::vector<WebPage> pages;
};