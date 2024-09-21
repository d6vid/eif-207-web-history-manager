#pragma once

#include <vector>
#include "Tab.h"

class Navegador {
public:
	Navegador();
	void nuevoTab();
	void cerrarTab(int);
	void visitarPaginaEnTab(int, const WebPage&);
	void mostrarHistorialDeTab(int);
	bool volver(int);
	bool avanzar(int);
	bool url(int, const WebPage&);
	void mostrarTabs();
	void cambiarPestanaIzquierda();
	void cambiarPestanaDerecha();
	void mostrarPestanaActiva() const;
	int getCurrentTabIndex() const; // Nuevo método
	~Navegador();


private:
	std::vector<Tab>tabs;
	int currentTabIndex;

};

