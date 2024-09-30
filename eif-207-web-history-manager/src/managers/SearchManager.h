#pragma once

#include <vector>
#include <optional>
#include <sstream>
#include "WebPage.h"

//Gestiona un vector de p�ginas web, permitiendo agregar, buscar y cargar p�ginas desde un archivo

class SearchManager {
public:
	//Crea una instancia de SearchManager
	static SearchManager create(const std::vector<WebPage>& pages);
	//Agrega una p�gina web a la colecci�n y retorna true si la p�gina se agreg� correctamente
	const bool add(const WebPage& page);
	//Este m�todo busca una p�gina web por URL
	std::optional<WebPage> findByUrl(const std::string& url);
	//Carga p�ginas web desde un archivo
	void loadFromFile(std::ifstream& in);
	//Destructor de la clase SearchManager
	~SearchManager();
private:
	//Constructor privado para inicializar con p�ginas web
	SearchManager(const std::vector<WebPage>& pages = {});
	//Colecci�n de p�ginas web siendo gestionadas
	std::vector<WebPage> pages;
};