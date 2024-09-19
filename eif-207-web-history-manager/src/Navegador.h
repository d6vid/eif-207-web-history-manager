#pragma once

#include <vector>
#include "Tab.h"

class Navegador {
public:
	Navegador();
	void nuevoTab();
	void cerrarTab(int);
	bool volver(int);
	bool avanzar();
	bool url(int, const WebPage&);
	void mostrarTabs();
	~Navegador();


private:
	std::vector<Tab>tabs;

};

