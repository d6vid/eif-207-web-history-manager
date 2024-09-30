#pragma once

#include <deque>
#include <optional>
#include <stdexcept>
#include "WebPage.h"
#include "Serializable.h"
#include "Policies.h"

//Esta clase representa el historial de páginas web visitadas

class History : public Serializable {
public:
	//Este es un método para crear un history
	static History create(const std::deque<WebPage>& visitedPages = {}, std::optional<size_t> currentIndex = std::nullopt);
	//Añade una página web al historial
	bool addPage(const WebPage& webPage);
	//Obtiene la página web actual
	const std::optional<WebPage> getCurrentPage() const;
	//Obtiene las páginas web visitadas
	const std::deque<WebPage>& getVisitedPages() const;
	//Mueve el índica a la página anterior en el historial
	bool moveToLeftPage();
	//Mueve el índice a la página siguiente en el historial
	bool moveToRightPage();
	//Elimina las paginas setteadas segun el valor maximo dado
	bool removePages(size_t max);
	//Verifica si el historial está vacío y si lo está retorna true y retorna false en caso contrario
	bool isEmpty() const;
	//Este método aplica las políticas definidas al historial
	bool applyPolicy(Policies policies);
	//Este método serializa el historial a un flujo de salida
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