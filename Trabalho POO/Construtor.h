#ifndef CONSTRUTOR_H
#define CONSTRUTOR_H

#include <vector>
#include <string>


#include "Imperio.h"
#include "Eventos.h"

class Imperio;
class Loja;
class Mundo;
class Eventos;
class Grava;

using namespace std;
class Construtor{
	int turno;
	int ano;
	int fase;
	int fatorSorte;
	int evento;
	Imperio *imperio = nullptr;
	Mundo *mundo = nullptr;
	Loja *loja = nullptr;
	Grava* grava = nullptr;
	vector <Eventos*> eventosPossiveis; 
	vector <string> comandos = {"cria","carrega","conquista","passa","maisouro","maisprod","maismilitar","adquire","lista","avanca","grava","ativa","apaga","toma","modifica","fevento"};
public:
	Construtor(int t, int a,Loja &l, Mundo &m,Imperio &i, Grava& g);
	Construtor& operator=(const Construtor &c);
	/*Getters and setters*/
	int getTurno() const {return turno;}
	int setTurno(int t) {return turno = t;}
	int getAno() const {return ano;}
	int setAno(int a) { return ano = a; }
	string avancaFase();
	/*-------------------*/
	string lerComando(string comando);
	bool comandosExistentes(string comando);
	string tratarComando(string comando,string arg1, int arg2, string arg2Toma);
	string acaoComando(string comando,string arg1,int arg2);
	string acaoComandoToma(string comando, string arg1, string arg2);
	bool adicionaTerritorio(string nomeTerritorio, int arg2);
	string conquistaTerritorio(string nomeTerritorio);
	string lista(string arg1);
	int getRealUniform(int min, int max);
	~Construtor() = default;
};

#endif