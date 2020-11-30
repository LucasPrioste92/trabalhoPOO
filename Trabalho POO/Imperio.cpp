#include "Imperio.h"
#include <fstream>
#include <string>

int tI=0;

string Imperio::getAsString() const {
	ostringstream os;
	os << "Territorios Disponiveis:\n";
	for (auto i : listaImperiosDisponiveis)
		os << "  -> " << i->getNomeTerritorio() << "\n";
	return os.str();
}

bool verificaNomesTerritorios(string nomeVerificar) {
	string nomes[9] = { "TerritorioInicial","Planicie","Montanha","Fortaleza","Mina","Duna","Castelo","Refugio","Pescaria" };
	for (int i = 0; i < 9; i++) {
		if (nomes[i] == nomeVerificar)
			return true;
	}
	return false;
}

bool Imperio::adicionaTerritorio(const string &nomeTerritorio,int n) {
	if(verificaNomesTerritorios(nomeTerritorio)==false){
		cout << "O nome do Territorio nao existe. (" << nomeTerritorio << ") logo o territorio nao foi criado.\n";
		return false;
	}

	if(nomeTerritorio == "TerritorioInicial"){
		if(n>1)
			n=1;
		if(tI>0){
			cout << "O Territorio Inicial ja foi criado.\n";
			return false;
		}
		tI++;
	}
	if(n>=1){
		for(int i = 0; i<n;i++){
			listaImperiosDisponiveis.push_back(new Territorio(nomeTerritorio));
		}
		return true;
	}else{
		cout << "O n nao e valido. (" << n << ") logo o territorio " << nomeTerritorio << " nao foi criado.\n";
		return false;
	}
}

bool Imperio::verificaNomesTerritoriosCriados(const string nomeTerritorio) const{
	for (auto i : listaImperiosDisponiveis){
		if(nomeTerritorio == i->getNomeTerritorio()){
			return true;
		}else{
			return false;
		}
	}
}

void Imperio::listar(string nomeTerritorio, const Imperio &i){
	int existe = 0;
	for(auto i : listaImperiosDisponiveis){
		if (nomeTerritorio == i->getNomeTerritorio()) {
			existe = 1;
			cout << i->getNomeTerritorio() << endl;
			cout << "Resistencia: " << i->getResistencia() << endl;
			cout << "Pontos de Vitoria: " << i->getPontosVitoria() << endl;
			cout << "Criacao de Ouro: " << i->getCriacaoOuro() << endl;
			cout << "Criacao de Produto: " << i->getProdutos() << endl;
			if(i->getConquistado() == 1)
				cout << "Territorio Conquistado.\n";
			else
				cout << "Territorio nao Conquistado.\n";
		}
	}
	if(existe==0)
		cout << "Territorio nao existe.\n";	
}

void boasVindas(){
	cout << "Seja Bem Vindo ao Jogo Conquista e Expansao territorial.\n";
	cout << "No começo de cada jogo o jogador possui um territorio e objetivo e conquistar novos territorios.\n";
	cout << "Cada territorio ira ter diferentes carateristicas.\n";
	cout << "A duracao do jogo e de 12 turnos, 6 turnos equivale a 1 ano.\n";
	cout << "Boa sorte para o teu imperio.\n\n\n";
}
void comandos(){
	cout << "Estes serao os comandos que podera usar durante a configuracao do jogo:\n";
	cout << "  -> carrega (comando usado para carregar um ficheiro .txt com os territorios a criar)\n";
	cout << "  -> cria (comando usado para criar n territorios, exemplo (cria Duna 3), ira criar 3 dunas)\n";
	cout << "Quando pretender terminar a configuracao digite 'feito'.\n";
}
void Imperio::carregaConfig(string nomeFicheiro, Imperio &i){
	ifstream file(nomeFicheiro);
	string comandoTexto, nomeTerritorio, linha;
	int numero;
	if (file.is_open()) {
		while (getline(file, linha)) {
			istringstream stream(linha);
			stream >> comandoTexto >> nomeTerritorio >> numero; //obter valores linha
			if (comandoTexto == "cria") {
				if (i.adicionaTerritorio(nomeTerritorio, numero) == true) {
					cout << "Territorio " << nomeTerritorio << " adicionado com sucesso!!!\n";
				}
				else {
					cout << "Nao foi possivel adicionar o Territorio " << nomeTerritorio << "!!!\n";
				}
			}
		}
	}
	else {
		cout << "Nao foi possivel abrir o ficheiro.\n";
	}
	file.close();
}

ostream &operator<<(ostream &os, const Imperio &i) {
	os << i.getAsString() << "\n";
	return os;
}