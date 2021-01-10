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

bool Pescaria::mudaProdOuro(int turno, int ano){
	// Em cada turno do primeiro ano produz 2 unidades de
	//produtos; em cada turno do segundo ano produz 4 unidades de produtos.
	if(ano==1){
		criacaoProdutos=2;
	}else{
		criacaoProdutos=4;
	}
	return false;
}
