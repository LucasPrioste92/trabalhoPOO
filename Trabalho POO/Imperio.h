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
	Imperio(string nomeImperio,string nomePlayer) : nome(nomeImperio),nomeImperador(nomePlayer){}; //construtor
	bool adicionaTerritorio(const string &nomeTerritorio,int n); //adicionar territorio ao vetor
	string getNomeImperio() const { return nome;} //obter nome Imperio
	string getNomeImperador() const { return nomeImperador;} //obter nome Imperador
	string getAsString() const; //obter o Imperio
	bool setTurno(int i) {return turno = i;} //mudar o turno
	bool setPontosVitoria(int i) { return pontosVitoria = i; } //mudar os pontos de vitoria
	bool verificaNomesTerritoriosCriados(const string nomeTerritorio) const; //verifica se o nome passado existe no vetor
	void listar(string nomeTerritorio); // listar as informacoes sobre um determinado territorio
	void carregaConfig(string nomeFicheiro); //carregar ficheiro txt com a configuracao do imperio
	string listarImperio() const; // listar todos os territorios disponiveis
	bool conquistaTerritorio(const string &nomeTerritorio); //conquistar um determinado territorio
};
ostream &operator<<(ostream &os, const Imperio &i); //listar imperio com territorios conquistados
void boasVindas(); //mensagem de boas vindas com explicacao
void comandos(); //lista comandos de configuracao
bool verificaNomesTerritorios(string nomeVerificar); //verifica se o nome do territorio enviado existe
void inicio(); //lista comandos a usar no jogo

#endif