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

bool Planicie::mudaProdOuro(int turno, int ano){
	if(ano==1){
		criacaoOuro=1;
		criacaoProdutos=1;
	}else if(ano==2){
		criacaoOuro = 1;
		criacaoProdutos = 2;
	}
	return true;
}

bool Montanha::mudaProdOuro(int turno, int ano){
	int auxiliarTurno = turnoConquistado;
	if(auxiliarTurno==0)
		return true;
	if(ano==2){ //colocar os turnos de 1 a 12 para poder ser mais facil verificar se foi conquistado a 2 turnos
		turno += 6;
		auxiliarTurno += 6;
	}
	if (turno - auxiliarTurno == 0 || turno - auxiliarTurno == 1) {
		criacaoOuro = 0;
		criacaoProdutos = 0;
		return true;
	}else {
		criacaoOuro = 0;
		criacaoProdutos = 1;
		return true;
	}
	return false;
}



bool Mina::mudaProdOuro(int turno, int ano){
	if(turno<=3){
		criacaoOuro = 1;
		criacaoProdutos=0;
		return true;
	}else{
		criacaoOuro = 2;
		criacaoProdutos = 0;
		return true;
	}
	return false;
}


bool Castelo::mudaProdOuro(int turno, int ano){
	if(turno <=2){
		criacaoProdutos = 3;
		return true;
	}
	else{
		criacaoProdutos = 0;
		return true;
	}
	return false;
}
