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
};
ostream &operator<<(ostream &os, const Imperio &i);
void boasVindas();
bool verificaNomesTerritorios(string nomeVerificar);
#endif