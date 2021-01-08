#ifndef LOJA_H
#define LOJA_H

#include <vector>
#include "Tecnologia.h"

class Tecnologia;

using namespace std;
class Loja{
	vector <Tecnologia*> tecnologiaDisponivel;
public:
	Loja();
	const vector<Tecnologia*> &getTecnologias() const { return tecnologiaDisponivel; }
};
#endif
