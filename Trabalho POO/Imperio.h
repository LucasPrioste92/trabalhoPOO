#ifndef IMPERIO_H
#define IMPERIO_H


#include <vector>

#include "Mundo.h"
#include "Loja.h"

class Mundo;
class Tecnologia;
class Territorio;
class Loja;

using namespace std;

class Imperio{
	vector <Territorio*> listaImperiosConquistados;
	vector <Tecnologia*> tecnologiaComprada;
	Mundo *mundo = nullptr;
	Loja *loja = nullptr;
	int produtos;
	int ouro;
	int armazem; //capacidade max 3 produtos
	int cofre; //capacidade max 3 cofre
	int forcaMilitar; 
	int maxForcaMilitar; //max 5
	int pontosVitoria;
	int resistenciaExtra;
public:
	Imperio(int forcMili,Mundo &m, Loja &l); //construtor
	const vector<Territorio*>& getTerritoriosConquistados() const { return listaImperiosConquistados; }
	int getPontuacao() const {return pontosVitoria;}
	bool atualizarPontos();
	int pontuacaoFinal();
	int getForcaMilitar() const {return forcaMilitar;}
	bool setForcaMilitar(int f) {return forcaMilitar=f;}
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
	bool conquistaTerritorio(const string &nomeTerritorio, int fatorSorte, int turno, int ano); //conquistar um determinado territorio
	Territorio *perdeTerritorio(const string &nomeTerritorio);
	bool compraTecnologia(const string& nomeTec);
	bool verificarTecnologia(string nome) const;
	bool verificarOuro() const { return ouro > cofre; }
	bool verificarPro() const { return produtos > armazem; }
	bool ajustarValoresOuro();
	bool ajustarValoresProduto();
	int recolherOuro() const;
	int recolherProdutos() const;
	void recolher();
	bool maisMilitar();
	string tomaAssalto(string arg2, int turno, int ano);
	string tomaAssaltoTec(string arg2);
	string getAsString() const;
};
ostream &operator<<(ostream &os, const Imperio &i); //listar imperio com territorios conquistados

#endif