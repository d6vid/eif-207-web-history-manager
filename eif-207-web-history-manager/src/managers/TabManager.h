#pragma once

#include "Tab.h"
#include "Policies.h"
#include <vector>
#include <optional>

//Esta clase gestiona un vector de pestañas permitiendo agregar, eliminitar y navegar entre ellas

class TabManager : public Serializable {
public:
	//Se crea una instancia de TabManager
	static TabManager create(const std::vector<Tab>& tabs = {}, const std::optional<size_t> currentTab = std::nullopt);
	//Este método agrega una nueva pestaña y retorna true si se agregó correctamente
	const bool addTab(const Tab& tab = Tab::create());
	//Elimina una pestaña por índice y retorna true si se eliminó correctamente
	const bool removeTab(const size_t index);
	//Elimina la pestaña actual y retorna true si se eliminó correctamente
	const bool removeCurrentTab();
	//Este método obtiene la pestaña actual
	const std::optional<Tab> getCurrentTab();
	//Obtiene el índice de la pestaña actual
	const std::optional<size_t> getCurrentTabIndex();
	//Mueve a la pestaña a la izquierda y retorna true si el movimiento fue exitoso
	const bool moveToLeftTab();
	//Mueve a la pestaña a la derecha y retorna true si el movimiento fue exitoso
	const bool moveToRightTab();
	//Mueve una pestaña por índice y retorna true si fue exitoso
	const bool moveToTabByIndex(const size_t index);
	//Este método se mueve a la última pestaña y retorna true si el movimiento fue exitoso
	const bool moveToLastTab();
	//Este método mueve la pestaña actual a la página anterior y retorna true si el movimiento fue exitoso
	const bool moveCurrentTabToLeftPage();
	//Mueve la pestaña actual a la página siguiente y retorna true si el movimiento fue exitoso
	const bool moveCurrentTabToRightPage();
	//Agrega una página web a la pestaña actual y retorna true si se agregó correctamente
	const bool addPageToTab(const WebPage& page);
	//Activa o desactiva el seguimiento del historial
	void switchHistoryTracking(const bool state);
	//Serializa el estado del gestor de pestañas a un archivo y retorna true si la serialización fue exitosa
	bool serialize(std::ofstream& out);
	//Deserializa el estado del gestor de pestañas desde un archivo y retorna true si la deserialización fue exitosa
	bool deserialize(std::ifstream& in);
	void applyPolicies();
	//Destructor de la clase TabManager
	~TabManager();
private:
	//Constructor privado para inicializar con pestañas
	TabManager(const std::vector<Tab>& tabs = {}, const std::optional<size_t> currentTab = std::nullopt);
	std::vector<Tab> tabs;
	std::optional<size_t> currentTab;
	bool isPrivate;
};