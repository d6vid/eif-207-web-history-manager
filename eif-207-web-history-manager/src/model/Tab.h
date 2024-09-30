#pragma once

#include "History.h"
#include "Policies.h"

//Este m�todo obtiene la duraci�n m�xima que una entrada puedo permanecer en el historial

class Tab : public Serializable {
public:
	//Este m�todo permite crear una pesta�a
	static Tab create(const History& history = History::create());
	//Este m�todo avanza a la siguiente p�ginas en el historial
	bool goForward();
	//Este m�todo retrocede a la p�gina anterior en el historial
	bool goBackward();
	//Este m�todo establece la p�gina actual de la pesta�a
	bool setCurrentPage(const WebPage& page, const bool track);
	//Este m�todo obtiene la p�gina actual de la pesta�a
	std::optional<WebPage> getCurrentPage() const;
	//Este m�todo verifica si la pesta�a tiene p�ginas en su historial
	bool hasPages() const;
	//Obtiene el historial de la pesta�a
	const History& getHistory() const;
	//Aplica politicas dadas
	void applyPolicies(Policies policies);
	//Serializa la pesta�a en flujo de salida
	virtual bool serialize(std::ofstream& out);
	//Deserializa la pesta�a desde un flujo de entrada
	virtual bool deserialize(std::ifstream& in);
	//Destructor de la clase
	~Tab();
private:
	Tab(const History& history = History::create(), const std::optional<WebPage>& currentPage = std::nullopt);
	History history;
	std::optional<WebPage> currentPage;
};