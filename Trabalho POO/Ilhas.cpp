#include "Ilhas.h"

string Ilhas::getAsString() const{
	ostringstream os;
	os << Territorio::getAsString();
	os << "Tipo: Ilha\n";
	os << "\n------------------------------\n";
	return os.str();
}

bool Ilhas::ContinenteOuIlha() const{
	return false;
}
