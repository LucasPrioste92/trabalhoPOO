#include "Imperio.h"
#include <fstream>
#include <string>
#include <vector>

int tI=0; //variavel global para verificar se o territorio inicial ja foi criado

bool verificaNomesTerritorios(string nomeVerificar) {
	string nomes[9] = { "TerritorioInicial","Planicie","Montanha","Fortaleza","Mina","Duna","Castelo","Refugio","Pescaria" };
	for (int i = 0; i < 9; i++) {
		if (nomes[i] == nomeVerificar)
			return true;
	}
	return false;
}

Imperio::Imperio(int forcMili, Mundo& m, Loja& l) {
	forcaMilitar = forcMili;
	armazem = 3;
	cofre = 3;
	maxForcaMilitar = 3;
	ouro = 0;
	produtos = 0;
	resistenciaExtra = false;
	loja = &l;
	mundo = &m;
	mundo->adicionaTerritorio("TerritorioInicial", 1);
	tomaAssalto("TerritorioInicial",0,0);
}

bool Imperio::atualizarPontos(){
	for(auto i : listaImperiosConquistados){
		pontosVitoria += i->getPontosVitoria();
	}
	return true;
}

int Imperio::pontuacaoFinal(){
	pontosVitoria += tecnologiaComprada.size();
	if(tecnologiaComprada.size() == loja->getTecnologias().size()){
		pontosVitoria += 1;
	}
	if(listaImperiosConquistados.size() == mundo->getTerritorios().size()){
		pontosVitoria += 3;
	}
	return pontosVitoria;
}

bool Imperio::conquistaTerritorio(const string &nomeTerritorio, int fatorSorte,int turno,int ano){
	bool existe=false;
	for (auto i : mundo->getTerritorios()) {
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
Territorio *Imperio::perdeTerritorio(const string& nomeTerritorio)
{
	auto it = listaImperiosConquistados.begin();
	while (it < listaImperiosConquistados.end()) {
		if ((*it)->getNomeTerritorio() == nomeTerritorio) {
			Territorio* out = *it;
			if (out->desligaImperio(this) == false)
				return nullptr;
			listaImperiosConquistados.erase(it);
			return out;
		}
		it++;
	}
	return nullptr;
	
}
bool Imperio::compraTecnologia(const string& nomeTec){
	
	if(loja->verificarFundos(ouro, nomeTec, *this)==true){
		for (auto t : loja->getTecnologias()) {
			if (nomeTec == t->getNome()) {
				tecnologiaComprada.push_back(t);
				t->acaoTecnologia();
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
string Imperio::tomaAssalto(string arg2,int turno,int ano){
	ostringstream os;
	for(auto t: mundo->getTerritorios()){
		if(t->getNomeTerritorio() == arg2){
			if (t->ligaImperio(this, turno, ano) == false){
				os << "Ja Conquistado <" << arg2 << ">\n";
				return os.str();
			}
			listaImperiosConquistados.push_back(t);
			os << "Conquistado <" << arg2 << ">\n";
			return os.str();
		}
	}
	os << "Nao existe <" << arg2 << ">\n";
	return os.str();
}
string Imperio::tomaAssaltoTec(string arg2){
	ostringstream os;
	
	for (auto t : loja->getTecnologias()) {
		if (arg2 == t->getNome()) {
			if (t->ligaImperio(this) == false) {
				os << "Tecnologia ja adquirida.\n";
				return os.str();
			}
			tecnologiaComprada.push_back(t);
			t->acaoTecnologia();
			os << "Tecnologia adquirida <" << arg2 << ">\n";
			return os.str();
		}
	}
	

	/*for(auto l: loja->getTecnologias()){
		if(l->getNome() == arg2){
			if (l->ligaImperio(this) == false) {
				os << "Ja tem tecnologia <" << arg2 << ">\n";
				return os.str();
			}
			tecnologiaComprada.push_back(l);
			os << "Tecnologia adquirida <" << arg2 << ">\n";
			return os.str();
		}
	}
	os << "Nao existe essa tecnologia <" << arg2 << ">\n";*/
	return os.str();
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