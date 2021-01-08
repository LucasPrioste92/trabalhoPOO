#ifndef TERRITORIOINICIAL_H
#define TERRITORIOINICIAL_H

#include "Territorio.h"

class TerritorioInicial : public Territorio {
public:
	TerritorioInicial(string nome="TerritorioInicial",int res=9,int criacaoP=1, int criacaoO=1) : Territorio(nome, res, criacaoP, criacaoO, 0) {};
	virtual string getAsString() const override;
};

#endif