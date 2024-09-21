#include "Navegador.h"

Navegador::Navegador() : currentTabIndex(0) {} // Asegúrate de inicializar currentTabIndex

void Navegador::nuevoTab() {
	tabs.emplace_back(Tab());
    currentTabIndex = tabs.size() - 1;
}

/*void Navegador::cerrarTab(int i) {
    if (i >= 0 && i < tabs.size()) {
        tabs.erase(tabs.begin() + i);
    }
}*/

void Navegador::cerrarTab(int tabIndex) {
    if (tabIndex >= 0 && tabIndex < tabs.size()) {
        tabs.erase(tabs.begin() + tabIndex);
        if (currentTabIndex >= tabs.size()) {
            currentTabIndex = tabs.size() - 1; // Ajustar el índice si es necesario
        }
    }
}

bool Navegador::volver(int i) {
    if (i >= 0 && i < tabs.size()) {
        return tabs[i].goBackward();
    }
    return false;
}

bool Navegador::avanzar(int i) {
    if (i >= 0 && i < tabs.size()) {
        return tabs[i].goForward();
    }
    return false;
}

bool Navegador::url(int i, const WebPage& pagina) {
    if (i >= 0 && i < tabs.size()) {
        return tabs[i].setCurrentPage(pagina);
    }
    return false;
}

void Navegador::mostrarTabs() {
    for (size_t i = 0; i < tabs.size(); ++i) {
        std::cout << "Tab " << i << ": ";
        auto currentPage = tabs[i].getCurrentPage();
        if (currentPage) {
            std::cout << currentPage->getUrl() << " - " << currentPage->getTitle() << std::endl;
        }
        else {
            std::cout << "Error con la pagina" << std::endl;
        }
    }
}


void Navegador::visitarPaginaEnTab(int i, const WebPage& pagina) {
    if (i >= 0 && i < tabs.size()) {
        tabs[i].setCurrentPage(pagina);
    }
}

void Navegador::mostrarHistorialDeTab(int i) {
    if (i >= 0 && i < tabs.size()) {
        tabs[i].mostrarHistorial();
    }
}

void Navegador::cambiarPestanaIzquierda() {
    if (currentTabIndex > 0) {
        --currentTabIndex;
    }
}

void Navegador::cambiarPestanaDerecha() {
    if (currentTabIndex < tabs.size() - 1) {
        ++currentTabIndex;
    }
}

void Navegador::mostrarPestanaActiva() const {
    std::cout << "Pestaña activa: " << currentTabIndex << std::endl;
    auto currentPage = tabs[currentTabIndex].getCurrentPage();
    if (currentPage) {
        std::cout << currentPage->getUrl() << " - " << currentPage->getTitle() << std::endl;
    }
    else {
        std::cout << "No hay página cargada" << std::endl;
    }
}

int Navegador::getCurrentTabIndex() const {
    return currentTabIndex;
}

Navegador::~Navegador() {}

//Diferencia del porque usar emplace_back en lugar de usar push_back: https://www.geeksforgeeks.org/vectoremplace_back-c-stl/