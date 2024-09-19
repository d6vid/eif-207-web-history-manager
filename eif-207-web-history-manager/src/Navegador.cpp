#include "Navegador.h"

Navegador::Navegador(){ }

void Navegador::nuevoTab() {
	tabs.emplace_back(Tab());
}

void Navegador::cerrarTab() {

}


//Diferencia del porque usar emplace_back en lugar de usar push_back: https://www.geeksforgeeks.org/vectoremplace_back-c-stl/