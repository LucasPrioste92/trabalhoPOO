#include "Imperio.h"
#include <fstream>
#include <string>

int tI=0; //variavel global para verificar se o territorio inicial ja foi criado

bool verificaNomesTerritorios(string nomeVerificar) {
	string nomes[9] = { "TerritorioInicial","Planicie","Montanha","Fortaleza","Mina","Duna","Castelo","Refugio","Pescaria" };
	for (int i = 0; i < 9; i++) {
		if (nomes[i] == nomeVerificar)
			return true;
	}
	return false;
}

Imperio::Imperio(int forcMili, Mundo& m) {
	forcaMilitar = forcMili;
	armazem = 3;
	cofre = 3;
	maxForcaMilitar = 3;
	ouro = 0;
	produtos = 0;
	resistenciaExtra = false;
	m.adicionaTerritorio("TerritorioInicial", 1);
	conquistaTerritorio("TerritorioInicial",m,0,0,0);
}

bool Imperio::conquistaTerritorio(const string &nomeTerritorio, Mundo &m, int fatorSorte,int turno,int ano){
	bool existe=false;
	for (auto i : m.getTerritorios()) {
		if (nomeTerritorio == i->getNomeTerritorio()) {
			if(fatorSorte==0){
				if (i->ligaImperio(this, turno, ano) == false)
					return false;
				listaImperiosConquistados.push_back(i);
				return true;
			}
			int totalForca = fatorSorte + forcaMilitar;
			if(i->ContinenteOuIlha() == false){ //é ilha, fazer verificacoes
				int nTerritoriosConquistados = listaImperiosConquistados.size();
				if (nTerritoriosConquistados < 5)
					return false;

				existe = verificarTecnologia("misseisTeleguiados");
				if(existe == false)
					return false;
			}
			if (totalForca >= i->getResistencia()) { //se o valor for superior ou igual a resistencia conquista
				if (i->ligaImperio(this,turno,ano) == false)
					return false;
				listaImperiosConquistados.push_back(i);
				return true;
			}else { // senao nao conquista
				if (forcaMilitar - 1 >= 0)
					forcaMilitar = forcaMilitar - 1;
				return false;
			}
		}
	}
	return false;
}
bool Imperio::perdeTerritorio(const string& nomeTerritorio, Mundo& m)
{
	for (int i=0; i< listaImperiosConquistados.size();i++) {
		if (nomeTerritorio == listaImperiosConquistados[i]->getNomeTerritorio()) {
			listaImperiosConquistados[i]->desligaImperio(this);
			listaImperiosConquistados.erase(listaImperiosConquistados.begin()+i);
			return true;
		}
	}
	return false;
}
bool Imperio::compraTecnologia(const string& nomeTec, Loja& l){
	
	if(l.verificarFundos(ouro, nomeTec, *this)==true){
		for (auto t : l.getTecnologias()) {
			if (nomeTec == t->getNome()) {
				tecnologiaComprada.push_back(t);
				return true;
			}
		}
	}
	return false;
}
bool Imperio::verificarTecnologia(string nome) const{
	for (auto t : tecnologiaComprada) {
		if (t->getNome() == nome)
			return true;
	}
	return false;
}
bool Imperio::ajustarValoresOuro(){
	ouro = ouro +1;
	produtos = produtos -2;
	return true;
}
bool Imperio::ajustarValoresProduto() {
	ouro = ouro - 2;
	produtos = produtos + 1;
	return true;
}
int Imperio::recolherOuro() const{
	int producao=0;
	for (auto i : listaImperiosConquistados) {
		producao += i->getCriacaoOuro();
	}
	return producao;
}
int Imperio::recolherProdutos() const{
	int producao = 0;
	for (auto i : listaImperiosConquistados) {
		producao += i->getProdutos();
	}
	return producao;
}
void Imperio::recolher(){
	int aux=0;
	for(auto i : listaImperiosConquistados){
		if(produtos<=armazem){
			aux = armazem-produtos;
			if(aux<=i->getProdutos())
				produtos = produtos + aux;
			else
				produtos = produtos + i->getProdutos();
		}
		if(ouro<=cofre){
			aux = cofre - ouro;
			if (aux <= i->getCriacaoOuro())
				ouro = ouro + aux;
			else
				ouro = ouro + i->getCriacaoOuro();
		}
	}
}
bool Imperio::maisMilitar(){
	if (forcaMilitar >= maxForcaMilitar) {
		return false;
	}else{
		if(produtos>=1 && ouro>=1){
			produtos--;
			ouro--;
			forcaMilitar++;
			return true;
		}else{
			return false;
		}
	}
	return false;
}
string Imperio::getAsString() const{
	ostringstream os;
	os << "Territorios Conquistados:\n";
	for (auto i : listaImperiosConquistados) {
		os << "  -> " << i->getNomeTerritorio() << ", resistencia: " << i->getResistencia() << "\n";
	}
	os << "Produtos: " << produtos << ", Capacidade Maxima: " << armazem << ", Producao Atual: " << recolherProdutos() << "\n";
	os << "Ouro: " << ouro << ", Capacidade Maxima: " << cofre << ", Producao Atual: " << recolherOuro() << "\n";
	os << "Forca Militar: " << forcaMilitar << ", Maxima Forca Militar: " << maxForcaMilitar << "\n";
	return os.str();
}

ostream &operator<<(ostream &os, const Imperio &i) {
	os << i.getAsString() << "\n";
	return os;
}