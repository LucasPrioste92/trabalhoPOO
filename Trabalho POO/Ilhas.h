#ifndef ILHAS_H
#define ILHAS_H

#include "Territorio.h"

class Ilhas : public Territorio {
public:
	Ilhas(string n, int res, int criacaoP, int criacaoO) : Territorio(n, res, criacaoP, criacaoO, 2) {};
	virtual string getAsString() const override;
	virtual bool ContinenteOuIlha() const override;
	virtual ~Ilhas() override {};
	virtual bool mudaProdOuro(int turno, int ano)=0; //n tinha
};

class RefugioPiratas : public Ilhas {
public:
	RefugioPiratas(string nome,int res=9,int criacaoP=0,int criacaoO=1) : Ilhas(nome, res, criacaoP, criacaoO) {};
	virtual ~RefugioPiratas() override {};
	virtual bool mudaProdOuro(int turno, int ano); //n tinha
};

class Pescaria : public Ilhas {
public:
	Pescaria(string nome, int res = 9, int criacaoP = 2, int criacaoO = 0) : Ilhas(nome, res, criacaoP, criacaoO) {};
	virtual bool mudaProdOuro(int turno, int ano) override;
	virtual ~Pescaria() override {};
};

#endif