#ifndef TECNOLOGIA_H
#define TECNOLOGIA_H

#include <string>
#include "Imperio.h"

using namespace std;
class Tecnologia{
	string nome;
	int custo;
public:
	Tecnologia(string n,int c) : nome(n),custo(c){};
	int getCusto() const {return custo;}
	string getNome() const {return nome;}
	virtual bool acaoTecnologia(Imperio &i);
};

class DronesMilitares : public Tecnologia {
	int maxForcaMilitar;
public:
	DronesMilitares(string n="drone", int c=5, int maxForca=5) : maxForcaMilitar(maxForca),Tecnologia(n, c) {};
	virtual bool acaoTecnologia(Imperio &i) override;
};

class MisseisTeleguiados : public Tecnologia {
public:
	MisseisTeleguiados(string n = "misseisTeleguiados", int c = 4) : Tecnologia(n, c) {};
};

class DefesasTerritoriais : public Tecnologia {
	int resistencia;
public:
	DefesasTerritoriais(string n = "defesasTerritoriais", int c = 4, int res = 1) : resistencia(res), Tecnologia(n, c) {};
	virtual bool acaoTecnologia(Imperio& i) override;
};

class BolsaDeValores : public Tecnologia {
public:
	BolsaDeValores(string n = "bolsaDeValores", int c = 2) : Tecnologia(n, c) {};
};

class BancoCentral : public Tecnologia {
	int maxCofre,maxArmazem;
public:
	BancoCentral(string n = "bancoCentral", int c = 4, int mC = 5, int mA = 5) : maxCofre(mC),maxArmazem(mA), Tecnologia(n, c) {};
	virtual bool acaoTecnologia(Imperio& i) override;
};

#endif