#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <deque>
#include "WebPage.h"

//Esta clase representa las pol�ticas para gestionar el historial de p�ginas web

class Policies {
public:
    //Constructor de la clase Policy
    Policies(int max, std::chrono::seconds duration);
    //Esto limita el tama�o del historial a un n�mero m�ximo de entradas
    std::deque<WebPage> limit(std::deque<WebPage>& history);
    //Este m�todo establece el n�mero m�ximo de entradas permitidas en el historial
    void setmax(int maxEntries);
    //Este m�todo obtiene el n�mero m�ximo de entradas permitidas en el historial
    int getmax() const;
    //Este m�todo establece la duraci�n m�xima que una entrada puede permanecer en el historial
    void setduration(std::chrono::seconds duration);
    //Este m�todo obtiene la duraci�n m�xima que una entrada puedo permanecer en el historial
    std::chrono::seconds getduration() const;

private:
    int max;
    std::chrono::seconds duration;
};