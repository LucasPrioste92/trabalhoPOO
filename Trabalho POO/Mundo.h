#ifndef MUNDO_H 
#define MUNDO_H

#include <vector>
#include "Territorio.h"
#include "TerritorioInicial.h"
#include "Continente.h"
#include "Ilhas.h"

using namespace std;

class Mundo{
	string nome;
	vector<Territorio*> territoriosDisponiveis;
public:
	Mundo(string n) : nome(n){}; //construtor, possibilidade de no futuro ter varios mundos
	/* Getters and setters */
	bool adicionaTerritorio(string nomeTerritorio, int n); //nome do territorio a adicionar e quantas vezes
	const vector<Territorio*> &getTerritorios() const{ return territoriosDisponiveis; }
	/* Funcoes para Vetor de Territorios */
	bool alteraResistencia(string nome, int r);
	/* Funcoes que devolvem strings */
	string getAsString() const; //obter o Mundo
	/* Funcoes de Verificação */
	bool verificarNomes(string nomeVerificar); //funcao para verificar se o nome do territorio é possivel
	bool verificaNomesTerritoriosCriados(const string nomeTerritorio) const; //verifica se o nome passado existe no vetor
	string listaTerritorio(string nomeTerritorio) const; //obter informacoes sobre determinado territorio
};
ostream& operator<<(ostream & os, const Mundo &m); //listar mundo com territorios
#endif // !MUNDO_H 