#pragma once

#include <deque>
#include <optional>
#include <stdexcept>
#include "WebPage.h"
#include "Serializable.h"
#include "Policies.h"

//Esta clase representa el historial de p�ginas web visitadas

class History : public Serializable {
public:
	//Este es un m�todo para crear un history
	static History create(const std::deque<WebPage>& visitedPages = {}, std::optional<size_t> currentIndex = std::nullopt);
	//A�ade una p�gina web al historial
	bool addPage(const WebPage& webPage);
	//Obtiene la p�gina web actual
	const std::optional<WebPage> getCurrentPage() const;
	//Obtiene las p�ginas web visitadas
	const std::deque<WebPage>& getVisitedPages() const;
	//Mueve el �ndica a la p�gina anterior en el historial
	bool moveToLeftPage();
	//Mueve el �ndice a la p�gina siguiente en el historial
	bool moveToRightPage();
	//Elimina las paginas setteadas segun el valor maximo dado
	bool removePages(size_t max);
	//Verifica si el historial est� vac�o y si lo est� retorna true y retorna false en caso contrario
	bool isEmpty() const;
	//Este m�todo aplica las pol�ticas definidas al historial
	bool applyPolicy(Policies policies);
	//Este m�todo serializa el historial a un flujo de salida
	bool serialize(std::ofstream& out);
	//Deserializa el historial desde un flujo de entrada
	bool deserialize(std::ifstream& in);
	//Destructor de la clase History
	~History();
private:
	History(const std::deque<WebPage>& visitedPages = {}, std::optional<size_t> currentIndex = std::nullopt);
	std::deque<WebPage> visitedPages;
	std::optional<size_t> currentIndex;
};