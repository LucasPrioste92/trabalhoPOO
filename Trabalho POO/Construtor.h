#ifndef CONSTRUTOR_H
#define CONSTRUTOR_H

#include <vector>
#include <string>


#include "Imperio.h"

class Imperio;
class Loja;
class Mundo;

using namespace std;
class Construtor{
	int turno;
	int ano;
	int fase;
	int fatorSorte;
	Imperio *imperio = nullptr;
	Mundo *mundo = nullptr;
	Loja *loja = nullptr;
	vector <string> comandos = {"cria","carrega","conquista","passa","maisouro","maisprod","maismilitar","adquire","lista","avanca","grava","ativa","apaga","toma","modifica","fevento"};
public:
	Construtor(int t, int a,Loja &l, Mundo &m,Imperio &i) : turno(t), ano(a), fatorSorte(0), fase(0), loja(&l), mundo(&m), imperio(&i){};
	/*Getters and setters*/
	int getTurno() const {return turno;}
	int setTurno(int t) {return turno = t;}
	int getAno() const {return ano;}
	int setAno(int a) { return ano = a; }
	string avancaFase();
	/*-------------------*/
	string lerComando(string comando, string arg1, int arg2);
	bool comandosExistentes(string comando);
	string tratarComando(string comando,string arg1, int arg2);
	string acaoComando(string comando,string arg1,int arg2);
	bool adicionaTerritorio(string nomeTerritorio, int arg2);
	string conquistaTerritorio(string nomeTerritorio);
	string listaMundo(string arg1);
	int getRealUniform(int min, int max);
};

#endif