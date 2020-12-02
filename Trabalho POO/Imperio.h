#ifndef IMPERIO_H
#define IMPERIO_H

#include <iostream>
#include <string>
#include <vector>
#include "Territorio.h"

using namespace std;

class Imperio{
	vector <Territorio*> listaImperiosDisponiveis;
	string nome;
	string nomeImperador;
	int turno;
	int pontosVitoria;
public:
	Imperio(string nomeImperio,string nomePlayer) : nome(nomeImperio),nomeImperador(nomePlayer){};
	bool adicionaTerritorio(const string &nomeTerritorio,int n);
	string getNomeImperio() const { return nome;}
	string getNomeImperador() const { return nomeImperador;}
	string getAsString() const;
	bool setTurno(int i) {return turno = i;}
	bool setPontosVitoria(int i) { return pontosVitoria = i; }
	bool verificaNomesTerritoriosCriados(const string nomeTerritorio) const;
	void listar(string nomeTerritorio);
	void carregaConfig(string nomeFicheiro);
	string listarImperio() const;
	bool conquistaTerritorio(const string &nomeTerritorio);
};
ostream &operator<<(ostream &os, const Imperio &i);
void boasVindas();
void comandos();
bool verificaNomesTerritorios(string nomeVerificar);
void inicio();



#endif