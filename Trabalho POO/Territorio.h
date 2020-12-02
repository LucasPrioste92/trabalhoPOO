#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

class Territorio{
	int tipoTerritorio; //0 - territorio Inicial, 1 - continente, 2 - ilha 
	string nome;
	int resistencia;
	int criacaoProdutos;
	int criacaoOuro;
	int pontosVitoria;
	int conquistado;  // se conquistado fica a 1 senao 0
public:
	Territorio(string nomeTipo);
	string getNomeTerritorio() const { return nome; }
	int getResistencia() const { return resistencia; }
	int getProdutos() const { return criacaoProdutos; }
	int getCriacaoOuro() const { return criacaoOuro; }
	int getPontosVitoria() const { return pontosVitoria; }
	int getConquistado() const { return conquistado; }
	bool setConquistado(int i) { return conquistado = i;}
};
ostream &operator<<(ostream &os, const Territorio &t);


#endif