#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <deque>
#include "WebPage.h"

//Esta clase representa las políticas para gestionar el historial de páginas web

class Policies {
public:
    //Constructor de la clase Policy
    Policies(int max, std::chrono::seconds duration);
    //Esto limita el tamaño del historial a un número máximo de entradas
    std::deque<WebPage> limit(std::deque<WebPage>& history);
    //Este método establece el número máximo de entradas permitidas en el historial
    void setmax(int maxEntries);
    //Este método obtiene el número máximo de entradas permitidas en el historial
    int getmax() const;
    //Este método establece la duración máxima que una entrada puede permanecer en el historial
    void setduration(std::chrono::seconds duration);
    //Este método obtiene la duración máxima que una entrada puedo permanecer en el historial
    std::chrono::seconds getduration() const;

private:
    int max;
    std::chrono::seconds duration;
};