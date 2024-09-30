#pragma once

#include <vector>
#include "Bookmark.h"

/*La clase BookMarkManager administra un vector de marcadores permitiendo agregar, eliminar y recuperar marcadores*/

class BookmarkManager : public Serializable {
public:
    /*Se crea una instancia de la clase BookmarkManager*/
    static BookmarkManager create(const std::vector<Bookmark> bookmarks = {});
    //Método para agregar un marcador que retorna true si se agregó correctamente
    const bool addBookmark(const Bookmark& bookmark);
    //Método que elimina un marcador por índice y retorna true si se eliminó correctamente
    const bool removeBookmark(const int index);
    //Método que obtiene todos los marcadores
    const std::vector<Bookmark>& getBookmarks() const;
    //Método que obtiene los marcadores por etiqueta
    std::vector<Bookmark> getBookmarksByTag(const std::string& tag);
    //Método que serializa los marcadores de un archivo y retorna true si fue exitosa
    bool serialize(std::ofstream& out);
    //Deserializa los marcadores desde un archivo y retorna true si esta fue exitosa
    bool deserialize(std::ifstream& in);
    //Destructor de BookManager
    ~BookmarkManager();
private:
    //Constructor privado para inicializar los marcadores
    BookmarkManager(const std::vector<Bookmark> bookmarks = {});
    //Vector de marcadores
    std::vector<Bookmark> bookmarks;
};