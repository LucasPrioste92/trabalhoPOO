#ifndef LOJA_H
#define LOJA_H

#include <vector>
#include "Tecnologia.h"

class Tecnologia;
class Imperio;

using namespace std;
class Loja{
	vector <Tecnologia*> tecnologiaDisponivel;
public:
	Loja();
	const vector<Tecnologia*> &getTecnologias() const { return tecnologiaDisponivel; }
	bool verificarFundos(int ouro, string nomeTec, Imperio& i);
	string getAsString() const;
	~Loja() = default;
};
ostream& operator<<(ostream& os, const Loja& l); //listar tecnologias 
#endif
