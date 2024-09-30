#pragma once

#include "Tab.h"
#include "Policies.h"
#include <vector>
#include <optional>

//Esta clase gestiona un vector de pesta�as permitiendo agregar, eliminitar y navegar entre ellas

class TabManager : public Serializable {
public:
	//Se crea una instancia de TabManager
	static TabManager create(const std::vector<Tab>& tabs = {}, const std::optional<size_t> currentTab = std::nullopt);
	//Este m�todo agrega una nueva pesta�a y retorna true si se agreg� correctamente
	const bool addTab(const Tab& tab = Tab::create());
	//Elimina una pesta�a por �ndice y retorna true si se elimin� correctamente
	const bool removeTab(const size_t index);
	//Elimina la pesta�a actual y retorna true si se elimin� correctamente
	const bool removeCurrentTab();
	//Este m�todo obtiene la pesta�a actual
	const std::optional<Tab> getCurrentTab();
	//Obtiene el �ndice de la pesta�a actual
	const std::optional<size_t> getCurrentTabIndex();
	//Mueve a la pesta�a a la izquierda y retorna true si el movimiento fue exitoso
	const bool moveToLeftTab();
	//Mueve a la pesta�a a la derecha y retorna true si el movimiento fue exitoso
	const bool moveToRightTab();
	//Mueve una pesta�a por �ndice y retorna true si fue exitoso
	const bool moveToTabByIndex(const size_t index);
	//Este m�todo se mueve a la �ltima pesta�a y retorna true si el movimiento fue exitoso
	const bool moveToLastTab();
	//Este m�todo mueve la pesta�a actual a la p�gina anterior y retorna true si el movimiento fue exitoso
	const bool moveCurrentTabToLeftPage();
	//Mueve la pesta�a actual a la p�gina siguiente y retorna true si el movimiento fue exitoso
	const bool moveCurrentTabToRightPage();
	//Agrega una p�gina web a la pesta�a actual y retorna true si se agreg� correctamente
	const bool addPageToTab(const WebPage& page);
	//Activa o desactiva el seguimiento del historial
	void switchHistoryTracking(const bool state);
	//Serializa el estado del gestor de pesta�as a un archivo y retorna true si la serializaci�n fue exitosa
	bool serialize(std::ofstream& out);
	//Deserializa el estado del gestor de pesta�as desde un archivo y retorna true si la deserializaci�n fue exitosa
	bool deserialize(std::ifstream& in);
	void applyPolicies();
	//Destructor de la clase TabManager
	~TabManager();
private:
	//Constructor privado para inicializar con pesta�as
	TabManager(const std::vector<Tab>& tabs = {}, const std::optional<size_t> currentTab = std::nullopt);
	std::vector<Tab> tabs;
	std::optional<size_t> currentTab;
	bool isPrivate;
};