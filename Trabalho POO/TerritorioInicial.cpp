#include "TerritorioInicial.h"

string TerritorioInicial::getAsString() const{
	ostringstream os;
	os << Territorio::getAsString();
	os << "Tipo: TerritorioInicial\n";
	os << "\n------------------------------\n";
	return os.str();
}

bool TerritorioInicial::ContinenteOuIlha() const{
	return true;
}

bool TerritorioInicial::mudaProdOuro(int turno, int ano)
{
	return false;
}
