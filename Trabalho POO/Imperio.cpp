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
	ouro = 2;
	produtos = 1;
	resistenciaExtra = false;
	m.adicionaTerritorio("TerritorioInicial", 1);
	conquistaTerritorio("TerritorioInicial",m,0);
}

bool Imperio::conquistaTerritorio(const string &nomeTerritorio, Mundo &m, int fatorSorte){
	bool existe=false;
	for (auto i : m.getTerritorios()) {
		if (nomeTerritorio == i->getNomeTerritorio()) {
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
				if (i->ligaImperio(this) == false)
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
bool Imperio::compraTecnologia(const string& nomeTec, Loja& l){
	for (auto i : l.getTecnologias()) {
		if (nomeTec == i->getNome()) {
			if(ouro >= i->getCusto()){
				ouro = ouro - i->getCusto();
				tecnologiaComprada.push_back(i);
				return true;
			}else{
				return false;
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
void Imperio::recolher(){
	for(auto i : listaImperiosConquistados){
		if(produtos<=armazem){
			produtos = produtos + i->getProdutos();
		}
		if(ouro<=cofre){
			ouro = ouro + i->getCriacaoOuro();
		}
	}
}
string Imperio::getAsString() const{
	ostringstream os;
	os << "Territorios Conquistados:\n";
	for (auto i : listaImperiosConquistados) {
		os << "  -> " << i->getNomeTerritorio() << "\n";
		os << "  -> " << i->getResistencia() << "\n";
		os << " ----------------------------- " << "\n";
	}
	return os.str();
}

ostream &operator<<(ostream &os, const Imperio &i) {
	os << i.getAsString() << "\n";
	return os;
}