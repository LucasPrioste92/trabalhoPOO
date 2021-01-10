#include "Construtor.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <tuple>


bool bloquearPassa = false;
bool bloquearConquista = false;
bool compraFeita = false;
bool adquire = false;
bool bloquearTrocas = false;


string Construtor::avancaFase(){
	ostringstream os;
	if(fase==4)
		fase = 1;
	else
		fase++;
	
	os << "A avancar para a fase: " << fase << "\n";
	return os.str();
}

string Construtor::lerComando(string comando, string arg1, int arg2){
    ostringstream os;
    if(comandosExistentes(comando)==false){
        os << "Comando <" << comando << "> nao existe!!!";
        return os.str();
    }
    if (comando == "carrega") {
		ifstream file(arg1);
		string comandoFile, arg1File, linha;
		int arg2File;
		if (file.is_open()) {
			while (getline(file, linha) && turno <= 6 && ano <= 2) {
				istringstream stream(linha);
				stream >> comandoFile >> arg1File >> arg2File; //obter valores linha
				os << tratarComando(comandoFile,arg1File,arg2File) << "\n";
				comandoFile.clear();
				arg1File.clear();
				arg2File = 0;
			}
		}else {
			os << "Nao foi possivel abrir o ficheiro.\n";
		}
		file.close();
    }else{
        os << tratarComando(comando,arg1,arg2);
    }
    return os.str();
}

bool Construtor::comandosExistentes(string comando){
    for(auto c : comandos)
        if(c==comando)
            return true;
    return false;
}

string Construtor::tratarComando(string comando, string arg1, int arg2){
	ostringstream os;
	string comandosDebug[3] = {"toma","modifica","fevento"};

	mundo->atualizarValores(turno, ano); // atualizar os valores dos territorios

	for (int z = 0; z <= 3; z++) {
		if (comando == comandosDebug[z] || comando == "lista") {
			os << acaoComando(comando, arg1, arg2);
			return os.str();
		}
	}
	if(fase==0 && comando!="cria"  && comando!="avanca"){ //fase de configuracao
		os << "Comando <" << comando <<"> ainda nao pode ser executado na fase de configuracao.";
		return os.str();
	}else if (fase > 0 && comando == "cria") {
		os << "Nao pode executar o comando <" << comando << "> porque a fase de configuracao ja terminou.";
		return os.str();
	}else if(fase==0 && (comando == "cria" || comando == "avanca")){
		os << acaoComando(comando, arg1, arg2);
		return os.str();
	}
	
	
	if(fase==1){ //se a fase for 1
		if(comando=="conquista" && bloquearConquista==false)
			os << acaoComando(comando, arg1, arg2);
		else if(comando=="passa" && bloquearPassa==false){
			os << acaoComando(comando,arg1,arg2);
		}else if(comando=="avanca" && (bloquearConquista==true || bloquearPassa==true)){
			os << acaoComando(comando,arg1,arg2);
		}else{
			os << "O comando <" << comando << "> nao pode ser utilizado neste momento.";
		}
		
	}else if(fase==2){
		if(comando=="maisouro" || comando=="maisprod"){
			os << acaoComando(comando,arg1,arg2);
		}else if(comando=="avanca"){
			os << acaoComando(comando,arg1,arg2);
		}else{
			os << "O comando <" << comando << "> nao pode ser utilizado neste momento.";
		}
	}else if(fase==3){
		if(comando=="maismilitar" || comando=="adquire" || comando == "avanca"){
			os << acaoComando(comando, arg1, arg2);
		}else{
			os << "O comando <" << comando << "> nao pode ser utilizado neste momento.";
		}
		
	}else if (fase == 4) {
		os << acaoComando(comando, arg1, arg2);
	}
	return os.str();
}

string Construtor::acaoComando(string comando, string arg1, int arg2){
	ostringstream os;
	if (comando == "cria") {
		if (adicionaTerritorio(arg1, arg2) == true)
			os << "Territorio <" << arg1 << "> adicionado com sucesso.";
		else
			os << "Algo correu mal, Territorio <" << arg1 << "> nao adicionado.";
	}
	else if (comando == "lista") {
		os << listaMundo(arg1);
	}
	else if (comando == "conquista") {
		bloquearPassa = true;
		os << conquistaTerritorio(arg1);
	}
	else if (comando == "avanca") {
		if(fase==4){
			os << "A avancar 1 turno.\n";
			os << "Turno a terminar: " << turno << ", Ano: " << ano << "\n";
			if (turno == 6 && ano == 1) {
				turno = 1;
				ano = 2;
			}
			else if (turno == 6 && ano == 2) {
				turno++;
				os << "Acabou o jogo.\n";
				return os.str();
			}
			else {
				turno++;
			}
			compraFeita = false;
			adquire = false;
			bloquearTrocas = false;
			os << "Turno a comecar: " << turno << ", Ano: " << ano << "\n";
			os << avancaFase();
		}else{
			os << avancaFase();
			if(fase==2){
				imperio->recolher();
				os << "Recolhidos produtos e ouro\n";
			}
		}
		bloquearConquista = false;
		bloquearPassa = false;
	}else if(comando=="passa"){
		bloquearConquista = true;
		os << "Fase Bloqueada, quando quiser avancar digite <avanca>\n";
	}
	else if (comando == "maisouro") {
		if (bloquearTrocas == true) {
			os << "Nao pode fazer mais trocas neste turno.\n";
			return os.str();
		}
		bool tecnologia = imperio->verificarTecnologia("bolsaDeValores");
		if(tecnologia==false){
			os << "Nao tem a tecnologia Bolsa de Valores\n";
		}else{
			if(imperio->getProdutos() < 2){
				os << "Nao tem produtos suficientes\n";
				return os.str();
			}else {
				if(imperio->verificarOuro() == true){
					os << "A capacidade de ouro ja esta no maximo\n";
					return os.str();
				}else{
					imperio->ajustarValoresOuro();
					os << "Ganhou mais 1 de ouro e perdeu 2 de produtos\n";
					bloquearTrocas=true;
				}
			}

		}
		return os.str();
	}
	else if (comando == "maisprod") {
		if (bloquearTrocas == true) {
			os << "Nao pode fazer mais trocas neste turno.\n";
			return os.str();
		}
		bool tecnologia = imperio->verificarTecnologia("bolsaDeValores");
		if (tecnologia == false) {
			os << "Nao tem a tecnologia Bolsa de Valores\n";
		}
		else {
			if (imperio->getOuro() < 2) {
				os << "Nao tem ouro suficiente\n";
				return os.str();
			}
			else {
				if (imperio->verificarPro() == true) {
					os << "A capacidade de produto ja esta no maximo\n";
					return os.str();
				}
				else {
					imperio->ajustarValoresProduto();
					os << "Ganhou mais 1 de produtos e perdeu 2 de ouro\n";
					bloquearTrocas = true;
				}
			}

		}
		return os.str();
	}else if(comando=="maismilitar"){
		if(compraFeita==true){
			os << "Ja comprou neste turno, so pode no seguinte.";
			return os.str();
		}
		if(imperio->maisMilitar() == true){
			os << "A forca militar depois da compra: " << imperio->getForcaMilitar() << "\n";
			compraFeita = true;
		}else{
			os << "Falha na aquisicao militar\n";
		}
		return os.str();
	}else if(comando=="adquire"){
		if(adquire==true){
			os << "Ja comprou tecnologia neste turno.";
			return os.str();
		}
		if(imperio->compraTecnologia(arg1,*loja)==true){
			os << "Comprou com sucesso a tecnologia: " << arg1 << "\n";
			adquire=true;
		}else{
			os << "Falha a comprar a tecnologia: " << arg1 << "\n";
		}
	}
		else if (comando == "grava") {
		int x;
		if ((x = gravaTudo->adicionaSave(mundo, arg2)) == -1)
			cout << "\nO save < " << arg2 << ">ja se encontra guardado!\n\n";
		else if (x == -2) {
			std::cout << "\nO Pedido para guardar informacao foi recusado. Excepcao apanhada!!\n\n";
		}
		else {
			std::cout << "\nO Save <" << arg2 << "> foi guardado com sucesso no vetor!\n\n";
		}
		}
		else if (comando == "ativa") {
		const Mundo *novo;
		
		if (gravaTudo->existeSave(arg2, &novo)) {
			mundo = *novo;
			cout << "\nO conteudo do Mundo foi atualizado de acordo com o Save!\n";
		}
		else {
			std::cout << "\nO Save <" << arg2 << "> nao foi encontrado no vetor!\n\n";
		}
		}
		else if (comando == "apaga") {
		if (gravaTudo->removeSave(arg2)) {
			std::cout << "\nO save <" << arg2 << "> foi apagado com sucesso do historico!\n\n";
		}
		else {
			std::cout << "\nO save <" << arg2 << "> nao foi encontrado no vetor!>\n\n";
		}
	}
	return os.str();
}

bool Construtor::adicionaTerritorio(string nomeTerritorio, int arg2){
	return mundo->adicionaTerritorio(nomeTerritorio, arg2);
}

string Construtor::conquistaTerritorio(string nomeTerritorio){
	ostringstream os;
	default_random_engine re;
	fatorSorte = getRealUniform(1, 6);
	
	if (imperio->conquistaTerritorio(nomeTerritorio, *mundo, fatorSorte,turno,ano) == true)
		os << "Territorio <" << nomeTerritorio << "> conquistado com sucesso.";
	else
		os << "Territorio <" << nomeTerritorio << "> nao foi conquistado.";
	return os.str();
}

string Construtor::listaMundo(string arg1){
	ostringstream os;
	
		
		
		//● Evento que vai ocorrer(nome, resumo dos efeitos)
		//● Pontuação final
	os << "Turno: " << turno << ", ano: " << ano << ", ultimo fator sorte: " << fatorSorte << "\n";
	os << *imperio;
	if(arg1.empty())
		os << *mundo;
	else
		os << mundo->listaTerritorio(arg1);
	os << *loja;
	return os.str();
}

int Construtor::getRealUniform(int min, int max) {
	max++;
	static default_random_engine e(time(0));
	static uniform_real_distribution<double> d(min, max);

	return d(e);
}