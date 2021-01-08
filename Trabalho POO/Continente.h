#ifndef CONTINENTE_H
#define CONTINENTE_H

#include "Territorio.h"

using namespace std;

class Continente : public Territorio {
public:
	Continente(string n,int res, int criacaoP, int criacaoO):Territorio(n,res,criacaoP,criacaoO,1){};
	virtual string getAsString() const override;
	virtual bool ContinenteOuIlha() const override;
};

class Planicie : public Continente{
public:
	Planicie(string nome, int res = 5, int criacaoP = 1, int criacaoO = 1) : Continente(nome, res, criacaoP, criacaoO) {};
};

class Montanha : public Continente {
public:
	Montanha(string nome, int res = 6, int criacaoP = 1, int criacaoO = 0) : Continente(nome, res, criacaoP, criacaoO) {};
	
};

class Fortaleza : public Continente {
public:
	Fortaleza(string nome, int res = 8, int criacaoP = 0, int criacaoO = 0) : Continente(nome, res, criacaoP, criacaoO) {};
};

class Mina : public Continente {
public:
	Mina(string nome, int res = 5, int criacaoP = 1, int criacaoO = 2) : Continente(nome, res, criacaoP, criacaoO) {};
};

class Duna : public Continente {
public:
	Duna(string nome, int res = 4, int criacaoP = 1, int criacaoO = 0) : Continente(nome, res, criacaoP, criacaoO) {};
};

class Castelo : public Continente {
public:
	Castelo(string nome, int res = 7, int criacaoP = 1, int criacaoO = 3) : Continente(nome, res, criacaoP, criacaoO) {};
};


#endif