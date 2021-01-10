#include "Loja.h"
#include "Imperio.h"
#include <sstream>


Loja::Loja(){
	tecnologiaDisponivel.push_back(new DronesMilitares);
	tecnologiaDisponivel.push_back(new MisseisTeleguiados);
	tecnologiaDisponivel.push_back(new DefesasTerritoriais);
	tecnologiaDisponivel.push_back(new BolsaDeValores);
	tecnologiaDisponivel.push_back(new BancoCentral);
}

bool Loja::verificarFundos(int ouro,string nomeTec,Imperio &i){
	for (auto t : tecnologiaDisponivel) {
		if (nomeTec == t->getNome()) {
			if(t->ligaImperio(&i)==false){
				return false;
			}
			if (ouro >= t->getCusto()) {
				i.setOuro(ouro - t->getCusto());
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

string Loja::getAsString() const
{
	ostringstream os;
	for(auto t : tecnologiaDisponivel){
		os << t->getAsString() << "\n";
	}
	return os.str();
}

ostream& operator<<(ostream& os, const Loja& l)
{
	os << l.getAsString();
	return os;
}
