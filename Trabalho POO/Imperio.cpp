#include "Imperio.h"

int tI=0;

string Imperio::getAsString() const {
	ostringstream os;
	os << "Imperio : " << getNomeImperio() << ", Imperador : " << getNomeImperador() << "\n";
	for (auto i : listaImperiosDisponiveis)
		if(i->getConquistado()==1)
			os << "  " << i->getNomeTerritorio() << "\n";
	return os.str();
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
bool verificaNomesTerritorios(string nomeVerificar){
	string nomes[9] = {"TerritorioInicial","Planicie","Montanha","Fortaleza","Mina","Duna","Castelo","Refugio","Pescaria"};
	for(int i=0;i<sizeof(nomes);i++){
		if(nomes[i] == nomeVerificar)
			return true;
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


ostream &operator<<(ostream &os, const Imperio &i) {
	os << i.getAsString() << "\n";
	return os;
}