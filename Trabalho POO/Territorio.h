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
	int criacaoProdutos;
	int criacaoOuro;
	int pontosVitoria;
	Imperio *imperio = nullptr;
public:
	Territorio(string n, int res, int criacaoPro, int criacaoO, int pontos);
	string getNomeTerritorio() const { return nome; }
	int getResistencia() const { return resistencia; }
	int getProdutos() const { return criacaoProdutos; }
	int getCriacaoOuro() const { return criacaoOuro; }
	int getPontosVitoria() const { return pontosVitoria; }
	int setResistencia(int r) {return resistencia = r;}
	bool ligaImperio(Imperio*); //associar territorio a imperio
	bool desligaImperio(Imperio*); //desassociar territorio a imperio
	virtual bool ContinenteOuIlha() const; //true = continente, false = ilha
	virtual string getAsString() const;
};
ostream &operator<<(ostream &os, const Territorio &t);


#endif