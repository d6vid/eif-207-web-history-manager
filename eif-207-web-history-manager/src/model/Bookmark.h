#pragma once

#include <vector>
#include "WebPage.h"

//Esta clase representa un marcador para una p�gina web con etiquetas asociadas

class Bookmark : public Serializable {
public:
    //M�todo para crear un Bookmark
    static Bookmark create(const WebPage& page, const std::vector<std::string>& tags);
    //Obtiene la p�gina web marcada
    const WebPage& getPage() const;
    //M�todo que obtiene las etiquetas asociadas con el marcador
    const std::vector<std::string>& getTags() const;
    // Este m�todo verifica si una etiqueta espec�fica est� asociada con el marcador
    const bool hasTag(const std::string& tag) const;
    //Este m�todo serializa el marcador a un flujo de salida
    bool serialize(std::ofstream& out);
    //Este m�todo deserializa el marcador desde un flujo de entrada
    bool deserialize(std::ifstream& in);
    //Representaci�n en cadena del marcador
    std::string toString() const;
    //Destructor de la clase Bookmark
    ~Bookmark();
private:
    Bookmark(const WebPage& page, const std::vector<std::string>& tags);
    WebPage page;
    std::vector<std::string> tags;
};