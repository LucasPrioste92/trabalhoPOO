#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>


class Imperio;

using namespace std;

class Territorio{
	string nome;
	int resistencia;
	int pontosVitoria;
	Imperio* imperio = nullptr;
protected:
	int criacaoProdutos;
	int criacaoOuro;
	int turnoConquistado;
	int anoConquistado;
public:
	Territorio(string n, int res, int criacaoPro, int criacaoO, int pontos);
	string getNomeTerritorio() const { return nome; }
	int getResistencia() const { return resistencia; }
	int getProdutos() const { return criacaoProdutos; }
	int getCriacaoOuro() const { return criacaoOuro; }
	int getPontosVitoria() const { return pontosVitoria; }
	int setResistencia(int r) {return resistencia = r;}
	int getTurno() const{return turnoConquistado;}
	int getAno() const{return anoConquistado;}
	bool conquistado() const;
	bool ligaImperio(Imperio*,int turno,int ano); //associar territorio a imperio
	bool desligaImperio(Imperio*); //desassociar territorio a imperio
	virtual bool ContinenteOuIlha() const = 0; //true = continente, false = ilha
	virtual bool mudaProdOuro(int turno,int ano) = 0;
	virtual string getAsString() const;
	virtual ~Territorio() {};
};
ostream &operator<<(ostream &os, const Territorio &t);


#endif