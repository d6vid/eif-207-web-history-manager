#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Serializable.h"

//Esta clase representa la p�gina web con URL, dominio y t�tulo

class WebPage : public Serializable {
public:
	//Este m�todo crea una p�gina web
	static WebPage create(const std::string& url, const std::string& domain, const std::string& title);
	//Obtiene la URL de la p�gina web
	const std::string& getUrl() const;
	//Obtiene el dominio de la p�gina web
	const std::string& getDomain() const;
	//Obtiene el t�tulo de la p�gina web
	const std::string& getTitle() const;
	//Serializa la p�gina web a un flujo de salida
	bool serialize(std::ofstream& out);
	//Deserializa la p�gina web desde un flujo de entrada
	bool deserialize(std::ifstream& in);
	//Constructor por defecto
	WebPage();
	//Destructor de la clase WewbPage
	~WebPage();
private:
	WebPage(const std::string& url, const std::string& domain, const std::string& title);
	std::string url;
	std::string domain;
	std::string title;
};