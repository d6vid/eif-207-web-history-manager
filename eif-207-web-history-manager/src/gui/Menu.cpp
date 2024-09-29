#include "Menu.h"

Menu::Menu(Browser& browser) : browser(browser){}

void Menu::showMenu() {
    std::cout << "╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "        Administrador historial de navegacion " << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
    std::cout << "  [1]  Visitar un sitio web" << std::endl;
    std::cout << "  [2]  Agregar marcador" << std::endl;
    std::cout << "  [3]  Nueva pestaña" << std::endl;
    std::cout << "  [4]  Buscar y filtrar historial" << std::endl;
    std::cout << "  [5]  Navegación privada" << std::endl;
    std::cout << "  [6]  Importar/Exportar" << std::endl;
    std::cout << "  [7]  Configuración de políticas" << std::endl;
    std::cout << "  [8]  Salir" << std::endl;

    auto currentPage = browser.getCurrentPage();
    if (currentPage) {
        std::cout << "\n\nSitio actual: " << currentPage->getUrl() << " - " << currentPage->getTitle() << std::endl;
    }
    else {
        std::cout << "\n\nNo hay sitio actual." << std::endl;
    }
}

void Menu::handleOption(int option) {
    switch (option) {
    case 1:
        goToWebsite();
        break;
    case 2:
        addBookmark();
        break;
    case 3:
        browser.openTab();
        std::cout << "---Nueva pestaña abierta---" << std::endl;
        break;
    case 4:
        searchHistory();
        break;
    case 5:
        browser.switchPrivateSearch();
        std::cout << "Modo de navegación privada activado/desactivado." << std::endl;
        break;
    case 6:
        importExport();
        break;
    case 7:
        configurePolicies();
        break;
    case 8:
        std::cout << "Saliendo..." << std::endl;
        exit(0);
    default:
        std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        break;
    }

    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (browser.moveToLeftPage()) {
                std::cout << "Navegando a la página anterior." << std::endl;
            }
            else {
                std::cout << "No hay páginas anteriores." << std::endl;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (browser.moveToRightPage()) {
                std::cout << "Navegando a la página siguiente." << std::endl;
            }
            else {
                std::cout << "No hay páginas siguientes." << std::endl;
            }
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if (browser.moveToLeftTab()) {
                std::cout << "Cambiando a la pestaña anterior." << std::endl;
            }
            else {
                std::cout << "No hay pestañas anteriores." << std::endl;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (browser.moveToRightTab()) {
                std::cout << "Cambiando a la pestaña siguiente." << std::endl;
            }
            else {
                std::cout << "No hay pestañas siguientes." << std::endl;
            }
        }
        Sleep(100); 
    }
}


void Menu::goToWebsite() {
    std::string url;
    std::cout << "Ingrese el URL del sitio web: ";
    std::cin >> url;
    if (browser.searchPage(url)) {
        std::cout << "Navegando a: " << url << std::endl;
    }
    else {
        std::cout << "404 – Not Found" << std::endl;
    }
}

void Menu::addBookmark() {
    std::string url, tag;
    std::cout << "Ingrese el URL del marcador: ";
    std::cin >> url;
    std::cout << "Ingrese una etiqueta para el marcador: ";
    std::cin >> tag;
    auto currentPage = browser.getCurrentPage();
    if (currentPage && browser.addBookmark(*currentPage, { tag })) {
        std::cout << "Marcador agregado: " << url << std::endl;
    }
    else {
        std::cout << "Error al agregar el marcador." << std::endl;
    }
}


void Menu::searchHistory() {
    std::string tag;
    std::cout << "Ingrese la etiqueta para buscar en el historial: ";
    std::cin >> tag;
    std::string bookmarks = browser.getBookmarksByTag(tag);
    std::cout << "Marcadores encontrados: " << bookmarks << std::endl;
}

void Menu::importExport() {

}

void Menu::configurePolicies() {

}