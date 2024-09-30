#pragma once

#include <vector>
#include "WebPage.h"

//Esta clase representa un marcador para una página web con etiquetas asociadas

class Bookmark : public Serializable {
public:
    //Método para crear un Bookmark
    static Bookmark create(const WebPage& page, const std::vector<std::string>& tags);
    //Obtiene la página web marcada
    const WebPage& getPage() const;
    //Método que obtiene las etiquetas asociadas con el marcador
    const std::vector<std::string>& getTags() const;
    // Este método verifica si una etiqueta específica está asociada con el marcador
    const bool hasTag(const std::string& tag) const;
    //Este método serializa el marcador a un flujo de salida
    bool serialize(std::ofstream& out);
    //Este método deserializa el marcador desde un flujo de entrada
    bool deserialize(std::ifstream& in);
    //Representación en cadena del marcador
    std::string toString() const;
    //Destructor de la clase Bookmark
    ~Bookmark();
private:
    Bookmark(const WebPage& page, const std::vector<std::string>& tags);
    WebPage page;
    std::vector<std::string> tags;
};