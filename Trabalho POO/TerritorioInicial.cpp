#include "TerritorioInicial.h"

string TerritorioInicial::getAsString() const{
	ostringstream os;
	os << Territorio::getAsString();
	os << "Tipo: TerritorioInicial\n";
	os << "\n------------------------------\n";
	return os.str();
}
