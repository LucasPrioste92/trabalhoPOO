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
public:
	Imperio(string nomeImperio,string nomePlayer) : nome(nomeImperio),nomeImperador(nomePlayer){};
	bool adicionaTerritorio(const string &nomeTerritorio,int n);
	string getNomeImperio() const { return nome;}
	string getNomeImperador() const { return nomeImperador;}
	string getAsString() const;
	bool verificaNomesTerritoriosCriados(const string nomeTerritorio) const;
	void listar(string nomeTerritorio, const Imperio &i);
	void carregaConfig(string nomeFicheiro,Imperio& i);
};
ostream &operator<<(ostream &os, const Imperio &i);
void boasVindas();
void comandos();
bool verificaNomesTerritorios(string nomeVerificar);



#endif