#ifndef CONSTRUTOR_H
#define CONSTRUTOR_H

#include <vector>
#include "Interface.h"
#include "Imperio.h"
#include "Mundo.h"


class Construtor{
	int turno;
	int ano;
	int fase;
	int fatorSorte;
	vector <string> comandos = {"cria","carrega","conquista","passa","maisouro","maisprod","maismilitar","adquire","lista","avanca","grava","ativa","apaga","toma","modifica","fevento"};
public:
	Construtor(int t, int a) : turno(t), ano(a), fatorSorte(0), fase(0){};
	/*Getters and setters*/
	int getTurno() const {return turno;}
	int setTurno(int t) {return turno = t;}
	int getAno() const {return ano;}
	int setAno(int a) { return ano = a; }
	/*-------------------*/
	string lerComando(string comando, string arg1, int arg2, Mundo &m, Imperio &i);
	bool comandosExistentes(string comando);
	string tratarComando(string comando,string arg1, int arg2, Mundo &m, Imperio &i);
	string acaoComando(string comando,string arg1,int arg2, Mundo&m, Imperio &i);
	bool adicionaTerritorio(string nomeTerritorio, int arg2,Mundo &m);
	string conquistaTerritorio(string nomeTerritorio,Imperio &i, Mundo &m);
	string listaMundo(Mundo &m,string arg1);
	double getRealUniform(int min, int max);
};

#endif