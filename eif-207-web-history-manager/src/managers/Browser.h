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

	// 1. Gesti�n general
	//Activa o desactiva el modo de b�squeda privada
	const void switchPrivateSearch();
	//Verifica si el modo de b�squeda privada est� activado. Retorna true si el modo privado est� activado y false en el caso contrario.
	const bool getIsPrivate();

	// 2. Gesti�n de b�squedas
   //Busca una p�gina por URL y retorna true si la p�gina se encontr� y se agreg� a una pesta�a y false en caso contrario.
	const bool searchPage(const std::string& url);
	//Obtiene una p�gina web por URL
	const std::optional<WebPage> getPageByUrl(const std::string& url);
	//Carga p�ginas web desde un archivo
	const void loadPagesFromFile(std::ifstream& in);

	// 3. Gesti�n de pesta�as
	//Obtiene la pesta�a actual
	const std::optional<Tab> getCurrentTab();
	//Obtiene el �ndica de la pesta�a actual
	const std::optional<size_t> getCurrentTabIndex();
	//Abre una nueva pesta�a
	const bool openTab();
	//Cierra la pesta�a actual
	const bool closeCurrentTab();
	//Mueve la pesta�a a la izquierda y si el movimiento fue exitoso returna true y false en caso contrario.
	const bool moveToLeftTab();
	//Mueve a la pesta�a a la derecha y retorna true si el movimiento fue exitoso, false en caso contrario
	const bool moveToRightTab();

	// 4. Gesti�n del Historial / P�ginas Web
	//Mueve a la p�gina a la izquierda en la pesta�a actual. Retorna true si el movimiento fue exitoso y false en caso contrario.
	const bool moveToLeftPage();
	//Mueve a la p�gina a la derecha en la pesta�a actual y retorna true si el movimiento fue exitoso y false en caso contrario.
	const bool moveToRightPage();
	//Obtiene la p�gina web actual en la pesta�a actual.
	const std::optional<WebPage> getCurrentPage();
	
	// 5. Gesti�n de marcadores
	//Agrega un marcador
	const bool addBookmark(const WebPage& page, const std::vector<std::string>& tags);	
	//Eliminar un marcador por �ndice
	const bool removeBookmarkByIndex(const size_t index);
	//Obtiene todos los marcadores
	const std::vector<Bookmark>& getBookmarks() const;
	//Obtiene marcadores por etiqueta
	std::vector<Bookmark> getBookmarksByTag(const std::string& tag);

	// 6. Persistencia de datos
	//Serializa el estado del navegador a un archivo y retorna true si la serializaci�n fue exitosa, false en caso contrario.
	bool serialize(std::ofstream& out);
	//Deserializa el estado del navegador desde un archivo. True si la deserializaci�n fue exitosa, false en caso contrario.
	bool deserialize(std::ifstream& in);

private:
	//Gestor de pesta�as
	TabManager tabManager;
	//Gestor de marcadores
	BookmarkManager bookmarkManager;
	//Gestor de b�squedas
	SearchManager searchManager;
	//Indica si el modo de b�squeda privada est� activado.
	bool isPrivate;
};