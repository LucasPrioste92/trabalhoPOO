#ifndef TECNOLOGIA_H
#define TECNOLOGIA_H


#include <string>

class Imperio;

using namespace std;
class Tecnologia{
	string nome;
	int custo;
	Imperio *imperio = nullptr;
public:
	Tecnologia(string n,int c) : nome(n),custo(c){};
	int getCusto() const {return custo;}
	string getNome() const {return nome;}
	virtual bool ligaImperio(Imperio*); //associar territorio a imperio
	virtual bool desligaImperio(Imperio*); //desassociar territorio a imperio
	virtual bool acaoTecnologia(Imperio &i);
	virtual string getAsString() const;
};
ostream& operator<<(ostream& os, const Tecnologia& t); //listar tecnologias 


class DronesMilitares : public Tecnologia {
	int maxForcaMilitar;
public:
	DronesMilitares(string n="drone", int c=5, int maxForca=5) : maxForcaMilitar(maxForca),Tecnologia(n, c) {};
	virtual bool acaoTecnologia(Imperio &i) override;
	virtual string getAsString() const override;
};

class MisseisTeleguiados : public Tecnologia {
public:
	MisseisTeleguiados(string n = "misseisTeleguiados", int c = 4) : Tecnologia(n, c) {};
	virtual string getAsString() const override;
};

class DefesasTerritoriais : public Tecnologia {
	int resistencia;
public:
	DefesasTerritoriais(string n = "defesasTerritoriais", int c = 4, int res = 1) : resistencia(res), Tecnologia(n, c) {};
	virtual bool acaoTecnologia(Imperio& i) override;
	virtual string getAsString() const override;
};

class BolsaDeValores : public Tecnologia {
public:
	BolsaDeValores(string n = "bolsaDeValores", int c = 2) : Tecnologia(n, c) {};
	virtual string getAsString() const override;
};

class BancoCentral : public Tecnologia {
	int maxCofre,maxArmazem;
public:
	BancoCentral(string n = "bancoCentral", int c = 4, int mC = 5, int mA = 5) : maxCofre(mC),maxArmazem(mA), Tecnologia(n, c) {};
	virtual bool acaoTecnologia(Imperio& i) override;
	virtual string getAsString() const override;
};

#endif