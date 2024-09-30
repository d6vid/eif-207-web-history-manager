#pragma once

#include "BookmarkManager.h"
#include "TabManager.h"
#include "SearchManager.h"
#include "Policies.h"

class Browser : public Serializable {
public:
	//Constructor de la clase
	Browser(const TabManager& tabManager = TabManager::create(), const BookmarkManager& bookmarkManager = BookmarkManager::create(), 
			const SearchManager& searchManager = SearchManager::create({ WebPage::create("www.una.com", "una.com", "UNA"), WebPage::create("www.facebook.com", "facebook.com", "Facebook") }));
	//Destructor de la clase Browser
	~Browser();

	// X. Politicas
	const void applyPolicies();

	// 1. Gestión general
	//Activa o desactiva el modo de búsqueda privada
	const void switchPrivateSearch();
	//Verifica si el modo de búsqueda privada está activado. Retorna true si el modo privado está activado y false en el caso contrario.
	const bool getIsPrivate();

	// 2. Gestión de búsquedas
   //Busca una página por URL y retorna true si la página se encontró y se agregó a una pestaña y false en caso contrario.
	const bool searchPage(const std::string& url);
	//Obtiene una página web por URL
	const std::optional<WebPage> getPageByUrl(const std::string& url);
	//Carga páginas web desde un archivo
	const void loadPagesFromFile(std::ifstream& in);

	// 3. Gestión de pestañas
	//Obtiene la pestaña actual
	const std::optional<Tab> getCurrentTab();
	//Obtiene el índica de la pestaña actual
	const std::optional<size_t> getCurrentTabIndex();
	//Abre una nueva pestaña
	const bool openTab();
	//Cierra la pestaña actual
	const bool closeCurrentTab();
	//Mueve la pestaña a la izquierda y si el movimiento fue exitoso returna true y false en caso contrario.
	const bool moveToLeftTab();
	//Mueve a la pestaña a la derecha y retorna true si el movimiento fue exitoso, false en caso contrario
	const bool moveToRightTab();

	// 4. Gestión del Historial / Páginas Web
	//Mueve a la página a la izquierda en la pestaña actual. Retorna true si el movimiento fue exitoso y false en caso contrario.
	const bool moveToLeftPage();
	//Mueve a la página a la derecha en la pestaña actual y retorna true si el movimiento fue exitoso y false en caso contrario.
	const bool moveToRightPage();
	//Obtiene la página web actual en la pestaña actual.
	const std::optional<WebPage> getCurrentPage();
	
	// 5. Gestión de marcadores
	//Agrega un marcador
	const bool addBookmark(const WebPage& page, const std::vector<std::string>& tags);	
	//Eliminar un marcador por índice
	const bool removeBookmarkByIndex(const size_t index);
	//Obtiene todos los marcadores
	const std::vector<Bookmark>& getBookmarks() const;
	//Obtiene marcadores por etiqueta
	std::vector<Bookmark> getBookmarksByTag(const std::string& tag);

	// 6. Persistencia de datos
	//Serializa el estado del navegador a un archivo y retorna true si la serialización fue exitosa, false en caso contrario.
	bool serialize(std::ofstream& out);
	//Deserializa el estado del navegador desde un archivo. True si la deserialización fue exitosa, false en caso contrario.
	bool deserialize(std::ifstream& in);

private:
	//Gestor de pestañas
	TabManager tabManager;
	//Gestor de marcadores
	BookmarkManager bookmarkManager;
	//Gestor de búsquedas
	SearchManager searchManager;
	//Indica si el modo de búsqueda privada está activado.
	bool isPrivate;
};