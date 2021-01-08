#ifndef IMPERIO_H
#define IMPERIO_H

#include <iostream>
#include <string>
#include <vector>
#include "Mundo.h"
#include "Territorio.h"
#include "TerritorioInicial.h"
#include "Continente.h"
#include "Ilhas.h"
#include "Tecnologia.h"
#include "Loja.h"

class Loja;
class Tecnologia;

using namespace std;

class Imperio{
	vector <Territorio*> listaImperiosConquistados;
	vector <Tecnologia*> tecnologiaComprada;
	int produtos;
	int ouro;
	int armazem; //capacidade max 3 produtos
	int cofre; //capacidade max 3 cofre
	int forcaMilitar; 
	int maxForcaMilitar; //max 5
	int pontosVitoria;
	int resistenciaExtra;
public:
	Imperio(int forcMili,Mundo &m); //construtor
	int getOuro() const{return ouro;}
	bool setOuro(int o) {return ouro=o;}
	int getProdutos()const {return produtos;}
	bool setProdutos(int p) {return produtos=p;}
	int getMaxForcaMilitar() const {return maxForcaMilitar;}
	bool setMaxForcaMilitar(int m) {return maxForcaMilitar=m;}
	int getResistenciaExtra() const{return resistenciaExtra;}
	bool setResistenciaExtra(int r){return resistenciaExtra = r;}
	bool setPontosVitoria(int i) { return pontosVitoria = i; } //mudar os pontos de vitoria
	int getCofre() const{return cofre;}
	bool setCofre(int c){return cofre=c;}
	int getArmazem() const { return armazem; }
	bool setArmazem(int a) { return armazem = a; }
	bool conquistaTerritorio(const string& nomeTerritorio, Mundo& m, int fatorSorte); //conquistar um determinado territorio
	bool compraTecnologia(const string &nomeTec, Loja &l);
	bool verificarTecnologia(string nome) const;
	bool verificarOuro() const { return ouro > cofre; }
	bool verificarPro() const { return produtos > armazem; }
	bool ajustarValoresOuro();
	bool ajustarValoresProduto();
	void recolher();
	string getAsString() const;
};
ostream &operator<<(ostream &os, const Imperio &i); //listar imperio com territorios conquistados

#endif