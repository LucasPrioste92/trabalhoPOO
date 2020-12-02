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
		}
	}
	return false;
}

void Imperio::listar(string nomeTerritorio){
	int existe = 0;
	for(auto i : listaImperiosDisponiveis){
		if (nomeTerritorio == i->getNomeTerritorio()) {
			existe = 1;
			cout << "\n------------------------------\n";
			cout << i->getNomeTerritorio() << endl;
			cout << "Resistencia: " << i->getResistencia() << endl;
			cout << "Pontos de Vitoria: " << i->getPontosVitoria() << endl;
			cout << "Criacao de Ouro: " << i->getCriacaoOuro() << endl;
			cout << "Criacao de Produto: " << i->getProdutos() << endl;
			if(i->getConquistado() == 1)
				cout << "Territorio Conquistado.\n";
			else
				cout << "Territorio nao Conquistado.\n";
			cout << "------------------------------\n";
		}
	}
	if(existe==0)
		cout << "Territorio nao existe.\n";	
}

bool Imperio::conquistaTerritorio(const string &nomeTerritorio){
	if(verificaNomesTerritoriosCriados(nomeTerritorio)==true){
		for (auto i : listaImperiosDisponiveis) {
			if (nomeTerritorio == i->getNomeTerritorio()) {
				i->setConquistado(1);
				return true;
			}
		}
	}else{
		cout << "O territorio " << nomeTerritorio << " nao existe!!!\n";
		return false;
	}
	return false;
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

void inicio(){
	cout << "A configuracao esta completa, vamos dar agora inicio ao jogo, estes sao os comandos disponiveis: \n";
	cout << "  -> conquista (comando usado para conquistar um territorio, exemplo (conquista Duna1), ira tentar conquistar a Duna1)\n";
	cout << "  -> lista (comando para listar todos os territorios, se quisermos ver um em especifico passamos o nome do territorio)\n";
	cout << "  -> passa (comando usado quando nao se pretende fazer nada no turno)\n";
	cout << "  -> avanca (comando para continuar para o proximo turno)\n";
	cout << "O jogo termina ao fim de 12 turnos, cada 6 turnos correspondem a 1 ano.\n";
} 

void Imperio::carregaConfig(string nomeFicheiro){
	ifstream file(nomeFicheiro);
	string comandoTexto, nomeTerritorio, linha;
	int numero;
	if (file.is_open()) {
		while (getline(file, linha)) {
			istringstream stream(linha);
			stream >> comandoTexto >> nomeTerritorio >> numero; //obter valores linha
			if (comandoTexto == "cria") {
				if (adicionaTerritorio(nomeTerritorio, numero) == true) {
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

string Imperio::listarImperio() const{
	ostringstream os;
	os << "Imperio " << getNomeImperio() << endl;
	os << "Territorios Conquistados:\n";
	for (auto i : listaImperiosDisponiveis)
		if(i->getConquistado()==1)
			os << "  -> " << i->getNomeTerritorio() << "\n";
	return os.str();
}

ostream &operator<<(ostream &os, const Imperio &i) {
	os << i.getAsString() << "\n";
	return os;
}