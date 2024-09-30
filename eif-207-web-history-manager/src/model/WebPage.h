#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Serializable.h"

//Esta clase representa la página web con URL, dominio y título

class WebPage : public Serializable {
public:
	//Este método crea una página web
	static WebPage create(const std::string& url, const std::string& domain, const std::string& title);
	//Obtiene la URL de la página web
	const std::string& getUrl() const;
	//Obtiene el dominio de la página web
	const std::string& getDomain() const;
	//Obtiene el título de la página web
	const std::string& getTitle() const;
	//Serializa la página web a un flujo de salida
	bool serialize(std::ofstream& out);
	//Deserializa la página web desde un flujo de entrada
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