#include "Mundo.h"


bool tI = false; //variavel global para verificar se o territorio inicial ja foi criado
int countP, countM, countF, countMI, countD, countC, countRI, countPI;

Mundo& Mundo::operator=(const Mundo& m){
	if (this == &m)
		return *this;
	nome = m.nome;
	
	territoriosDisponiveis.clear();
	for (auto m : m.territoriosDisponiveis) {
		territoriosDisponiveis.push_back(m);
	}
	return *this;
}

bool Mundo::adicionaTerritorio(string nomeTerritorio, int n){
	int i;
	if (n < 1)
		return false;

	if (nomeTerritorio == "TerritorioInicial") {
		if (n != 1) //numero de vezes a criar
			return false;
		if (tI==true) //ja foi criado
			return false;
		tI=true;
		territoriosDisponiveis.push_back(new TerritorioInicial());
		return true;
	}
	else if (nomeTerritorio == "Planicie") {
		for (i = 0; i < n; i++){
			countP++;
			territoriosDisponiveis.push_back(new Planicie(nomeTerritorio+to_string(countP)));
		}
		return true;
	}
	else if (nomeTerritorio == "Montanha") {
		for (i = 0; i < n; i++){
			countM++;
			territoriosDisponiveis.push_back(new Montanha(nomeTerritorio + to_string(countM)));
		}
		return true;
	}
	else if (nomeTerritorio == "Fortaleza") {
		for (i = 0; i < n; i++){
			countF++;
			territoriosDisponiveis.push_back(new Fortaleza(nomeTerritorio + to_string(countF)));
		}
		return true;
	}
	else if (nomeTerritorio == "Mina") {
		for (i = 0; i < n; i++){
			countMI++;
			territoriosDisponiveis.push_back(new Mina(nomeTerritorio + to_string(countMI)));
		}
		return true;
	}
	else if (nomeTerritorio == "Duna") {
		for (i = 0; i < n; i++){
			countD++;
			territoriosDisponiveis.push_back(new Duna(nomeTerritorio + to_string(countD)));
		}
		return true;
	}
	else if (nomeTerritorio == "Castelo") {
		for (i = 0; i < n; i++){
			countC++;
			territoriosDisponiveis.push_back(new Castelo(nomeTerritorio + to_string(countC)));
		}
		return true;
	}
	else if (nomeTerritorio == "RefugioPiratas") {
		for (i = 0; i < n; i++){
			countRI++;
			territoriosDisponiveis.push_back(new RefugioPiratas(nomeTerritorio + to_string(countRI)));
		}
		return true;
	}
	else if (nomeTerritorio == "Pescaria") {
		for (i = 0; i < n; i++){
			countPI++;
			territoriosDisponiveis.push_back(new Pescaria(nomeTerritorio + to_string(countPI)));
		}
		return true;
	}
		
	return false;
}

bool Mundo::verificarNomes(string nomeVerificar){
	string nomes[9] = { "TerritorioInicial","Planicie","Montanha","Fortaleza","Mina","Duna","Castelo","Refugio","Pescaria" };
	for (int i = 0; i < 9; i++) {
		if (nomes[i] == nomeVerificar)
			return true;
	}
	return false;
}

bool Mundo::verificaNomesTerritoriosCriados(const string nomeTerritorio) const {
	for (auto i : territoriosDisponiveis) {
		if (nomeTerritorio == i->getNomeTerritorio()) {
			return true;
		}
	}
	return false;
}

string Mundo::listaTerritorio(string nomeTerritorio) const{
	ostringstream os;
	int existe = 0;
	for (auto i : territoriosDisponiveis) {
		if (nomeTerritorio == i->getNomeTerritorio()) {
			existe = 1;
			os << i->getAsString();
		}
	}
	if (existe == 0)
		os << "Territorio nao existe.";
	return os.str();
}

void Mundo::atualizarValores(int turno,int ano){
	for(auto t : territoriosDisponiveis){
		t->mudaProdOuro(turno,ano);
	}
}

string Mundo::getAsString() const {
	ostringstream os;
	os << "Territorios Criados nao conquistados:\n";
	for (auto i : territoriosDisponiveis){
		if(i->conquistado() == false)
			os << "  -> " << i->getNomeTerritorio() << ", resistencia: " << i->getResistencia() << "\n";
	}
	return os.str();
}
bool Mundo::alteraResistencia(string nome, int r){
	if (verificaNomesTerritoriosCriados(nome) == true) {
		for (auto i : territoriosDisponiveis) {
			if (nome == i->getNomeTerritorio()) {
				i->setResistencia(r);
				return true;
			}
		}
	}
	return false;
}
ostream& operator<<(ostream& os, const Mundo& m) {
	os << m.getAsString() << "\n";
	return os;
}