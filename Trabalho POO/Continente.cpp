#include "Continente.h"

string Continente::getAsString() const{
	ostringstream os;
	os << Territorio::getAsString();
	os << "Tipo: Continente\n";
	os << "\n------------------------------\n";
	return os.str();
}

bool Continente::ContinenteOuIlha() const{
	return true;
}
