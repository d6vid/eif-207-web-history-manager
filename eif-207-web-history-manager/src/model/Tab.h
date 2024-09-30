#pragma once

#include "History.h"
#include "Policies.h"

//Este método obtiene la duración máxima que una entrada puedo permanecer en el historial

class Tab : public Serializable {
public:
	//Este método permite crear una pestaña
	static Tab create(const History& history = History::create());
	//Este método avanza a la siguiente páginas en el historial
	bool goForward();
	//Este método retrocede a la página anterior en el historial
	bool goBackward();
	//Este método establece la página actual de la pestaña
	bool setCurrentPage(const WebPage& page, const bool track);
	//Este método obtiene la página actual de la pestaña
	std::optional<WebPage> getCurrentPage() const;
	//Este método verifica si la pestaña tiene páginas en su historial
	bool hasPages() const;
	//Obtiene el historial de la pestaña
	const History& getHistory() const;
	//Aplica politicas dadas
	void applyPolicies(Policies policies);
	//Serializa la pestaña en flujo de salida
	virtual bool serialize(std::ofstream& out);
	//Deserializa la pestaña desde un flujo de entrada
	virtual bool deserialize(std::ifstream& in);
	//Destructor de la clase
	~Tab();
private:
	Tab(const History& history = History::create(), const std::optional<WebPage>& currentPage = std::nullopt);
	History history;
	std::optional<WebPage> currentPage;
};