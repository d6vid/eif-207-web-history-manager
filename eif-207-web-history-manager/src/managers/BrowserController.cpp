#include "BrowserController.h"

BrowserController::BrowserController() : browser(Browser()) {}

void BrowserController::showMenu() {
    std::cout << "\033[H\033[J"; 
    std::string menu =
        "╔═══════════════════════════════════════════════════╗\n"
        "          Historial de navegacion web \n"
        "╚═══════════════════════════════════════════════════╝\n"
        "  [1]  Visitar un sitio web\n"
        "  [2]  Agregar marcador\n"
        "  [3]  Nueva pestaña\n"
        "  [4]  Buscar y filtrar marcadores\n"
        "  [5]  Navegación privada\n"
        "  [6]  Importar/Exportar\n"
        "  [7]  Configuración de políticas\n"
        "  [8]  Salir\n\n *** Oprima un numero o use las flechas direccionales para ingresar una opcion ***\n\n"
        "  ******************************************************************************************************************* ";

    auto& currentTabIndex = browser.getCurrentTabIndex();
    if (currentTabIndex) {
        menu.append("\n\n[ -> Tab Actual: " + std::to_string((*currentTabIndex) + 1) + "]\n");
        auto& currentPage = browser.getCurrentPage();
        if (currentPage) {
            menu.append("[-> -> Pagina Actual: " + (*currentPage).getUrl() + " - " + (*currentPage).getTitle() + "]\n");
        }
        else {
            menu.append("[-> -> No hay sitio actual]");
        }
    }
    else {
        menu.append("\n\n[-> No hay tab actual]");
    }

    std::cout << menu;
}


void BrowserController::handleMenuOption() {
    for (char key = '1'; key <= '5'; ++key) {
        if (GetAsyncKeyState(key) & 0x8000) {
            switch (key) {
                case '1': {
                    goToWebsite();
                    break;
                }  
                case '2': {
                    addBookmark();
                    break;
                }
                case '3': {
                    openTab();
                    break;
                }
                case '4': {
                    showAndSelectBookmark();
                    break;
                }
                case '5': {
                    switchIncognito();
                    break;
                }
            }
        }
    }

    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        if (!browser.moveToRightTab()) {
            std::cout << "\033[H\033[J";
            std::cout << "---No hay mas tabs hacia la derecha :(---   " << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if (!browser.moveToLeftTab()) {
            std::cout << "\033[H\033[J";
            std::cout << "---No hay mas tabs hacia la izquierda :(---" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (!browser.moveToLeftPage()) {
            std::cout << "\033[H\033[J";
            std::cout << "---No hay mas paginas hacia la izquierda :(---   " << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if (!browser.moveToRightPage()) {
            std::cout << "\033[H\033[J";
            std::cout << "---No hay mas paginas hacia la derecha :(---" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void BrowserController::openTab() {
    std::cout << "\033[H\033[J";
    browser.openTab();
    std::cout << "---Nueva pestaña abierta :))))))---" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void BrowserController::goToWebsite() {
    std::cout << "\033[H\033[J"; 
    std::string url;
    std::cout << "Ingrese el URL del sitio web: ";
    std::getline(std::cin, url);
    if (browser.getCurrentTab()) {
        if (browser.searchPage(url)) {
            std::cout << "\n" << "Navegando a: " << url << std::endl;
        }
        else {
            std::cout << "\n" << "404 – Not Found" << std::endl;
        }
    }
    else {
        std::cout << "\n" << "No hay tabs abiertos. Por favor abra un tab" << url << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void BrowserController::addBookmark() {
    std::cout << "\033[H\033[J"; 
    std::string url, tagsStream;
    std::cout << "Ingrese el URL del marcador: ";
    std::getline(std::cin, url);
    std::cout << "Ingrese una lista de etiquetas para el marcador (cada una separada por \", \"): ";
    std::getline(std::cin, tagsStream);
    std::vector<std::string> tags;
    std::stringstream ss(tagsStream);
    std::string tag;
    while (std::getline(ss, tag, ',')) {
        tag.erase(std::remove_if(tag.begin(), tag.end(), ::isspace), tag.end());
        if (!tag.empty()) {
            tags.push_back(tag);
        }
    }
    auto selectedPage = browser.getPageByUrl(url);
    if (selectedPage && browser.addBookmark(*selectedPage, tags)) {
        std::cout << "Marcador agregado: " << url << std::endl;
    }
    else {
        std::cout << "---Error al agregar el marcador:(---" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void BrowserController::showAndSelectBookmark() {
    std::cout << "\033[H\033[J";
    std::string tag;
    int option;
    std::cout << "Ingrese la etiqueta para buscar en el historial de marcadores: ";
    std::getline(std::cin, tag);
    std::cout << "\033[H\033[J";
    auto& bookmarks = browser.getBookmarksByTag(tag);
    if (!bookmarks.empty()) {
        std::cout << "Marcadores encontrados: \n";
        for (int i = 0; i < bookmarks.size(); i++) {
            std::cout << i << ". " + bookmarks.at(i).toString();
        }
        std::cout << "\n\n" << "Seleccione un marcador por visitar segun su numero de indice: ";
        std::string option;
        std::getline(std::cin, option);
        auto& selectedBookmark = bookmarks.at(std::stoi(option));
        std::cout << "\033[H\033[J";
        if (browser.searchPage(selectedBookmark.getPage().getUrl())) {
            std::cout << "\n" << "Navegando a: " << selectedBookmark.getPage().getUrl() << std::endl;
        }
        else {
            std::cout << "\n" << "---Error con el marcador o opcion invalida:(---";
        }
    }
    else {
        std::cout << "---No hay marcadores registrados bajo esa etiqueta :(---";
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void BrowserController::switchIncognito() {
    std::cout << "\033[H\033[J";
    browser.switchPrivateSearch();
    std::cout << "\n" << "---Se ha " << ((browser.getIsPrivate()) ? "activado" : "desactivado") << " la navegacion privada : )-- - ";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

/*
void BrowserController::searchHistory() {
    cleanConsole();
    std::string tag;
    std::cout << "Ingrese la etiqueta para buscar en el historial: ";
    std::cin >> tag;
    auto& bookmarks = browser.getBookmarksByTag(tag);
    std::cout << "Marcadores encontrados: " << bookmarks << std::endl;
}

void BrowserController::importExport() {
    cleanConsole();
}

void BrowserController::configurePolicies() {
    cleanConsole();
}
*/