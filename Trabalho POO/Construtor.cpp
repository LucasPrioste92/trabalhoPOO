#include "Construtor.h"
#include "Grava.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

bool bloquearPassa = false;
bool bloquearConquista = false;
bool compraFeita = false;
bool adquire = false;
bool bloquearTrocas = false;
bool primeiraVez = true;
bool fase4Pri = true;


Construtor::Construtor(int t, int a, Loja& l, Mundo& m, Imperio& i,Grava &g){
	turno=t, ano=a, fatorSorte=0, fase=0, loja=&l, mundo=&m, imperio=&i,evento=0,grava=&g;
	eventosPossiveis.push_back(new RecursoAbandonado);
	eventosPossiveis.push_back(new Invasao);
	eventosPossiveis.push_back(new AliancaDiplomatica);
	eventosPossiveis.push_back(new SemEvento);
}

Construtor& Construtor::operator=(const Construtor& c)
{
	if (this == &c)
		return *this;
	turno = c.turno;
	ano = c.ano;
	fase = c.fase;
	fatorSorte = c.fatorSorte;
	evento = c.evento;
	imperio = c.imperio;
	mundo = c.mundo;
	loja = c.loja;
	grava = c.grava;
	vector <Eventos*> eventosPossiveis;
	vector <string> comandos;
	
	eventosPossiveis.clear();
	for (auto e : c.eventosPossiveis) {
		eventosPossiveis.push_back(e);
	}
	comandos.clear();
	for (auto c : c.comandos) {
		comandos.push_back(c);
	}
	
	return *this;
}



string Construtor::avancaFase(){
	ostringstream os;
	if(fase==4)
		fase = 1;
	else
		fase++;
	
	os << "A avancar para a fase: " << fase << "\n";
	return os.str();
}

string Construtor::lerComando(string comando){
    ostringstream os;

	string comandoPrincipal,arg1,arg2Toma;
	int arg2;

	istringstream stream(comando);
	stream >> comandoPrincipal >> arg1 >> arg2; //obter valor comando

	if (comandoPrincipal == "toma"){
		istringstream stream2(comando);
		stream2 >> comandoPrincipal >> arg1 >> arg2Toma;
	}

    if(comandosExistentes(comandoPrincipal)==false){
        os << "Comando <" << comandoPrincipal << "> nao existe!!!";
        return os.str();
    }

    if (comandoPrincipal == "carrega") {
		ifstream file(arg1);
		string comandoFile, arg1File, arg2TomaFile, linha;
		int arg2File;
		if (file.is_open()) {
			while (getline(file, linha) && turno <= 6 && ano <= 2) {
				istringstream stream(linha);
				stream >> comandoFile >> arg1File >> arg2File; //obter valores linha
				if(comandoFile == "toma")
					stream >> comandoFile >> arg1File >> arg2TomaFile;

				os << tratarComando(comandoFile,arg1File,arg2File,arg2TomaFile) << "\n";
				comandoFile.clear();
				arg1File.clear();
				arg2TomaFile.clear();
				arg2File = 0;
			}
		}else {
			os << "Nao foi possivel abrir o ficheiro.\n";
		}
		file.close();
    }else{
        os << tratarComando(comandoPrincipal,arg1,arg2,arg2Toma);
    }
    return os.str();
}

bool Construtor::comandosExistentes(string comando){
    for(auto c : comandos)
        if(c==comando)
            return true;
    return false;
}

string Construtor::tratarComando(string comando, string arg1, int arg2, string arg2Toma){
	ostringstream os;
	string comandosDebug[6] = {"toma","modifica","fevento","grava","ativa","apaga"};

	mundo->atualizarValores(turno, ano); // atualizar os valores dos territorios

	if(primeiraVez==true){ //se for a primeira vez a entrar sorteia um evento
		default_random_engine re;
		evento = getRealUniform(0, eventosPossiveis.size()-1);
		primeiraVez = false;
	}

	for (int z = 0; z <= 6; z++) {
		if (comando == comandosDebug[z] || comando == "lista") {
			if(comando == "toma"){
				os << acaoComandoToma(comando,arg1,arg2Toma);
			}else{
				os << acaoComando(comando, arg1, arg2);
			}
			
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
		imperio->atualizarPontos(); //atualizar os pontos
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
		if(comando=="avanca")
			os << acaoComando(comando, arg1, arg2);
		else
			os << "O comando <" << comando << "> nao pode ser utilizado neste momento.";
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
		os << lista(arg1);
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
			primeiraVez = true;
			fase4Pri = true;
			os << "Turno a comecar: " << turno << ", Ano: " << ano << "\n";
			os << avancaFase();
		}else{
			os << avancaFase();
			if(fase==2){
				imperio->recolher();
				os << "Recolhidos produtos e ouro\n";
			}else if(fase==4){
				if (fase4Pri == true) {
					os << eventosPossiveis[evento]->acaoEvento(*imperio, *mundo, ano, turno);
					if (imperio->getTerritoriosConquistados().size() == 0) {
						turno = 1; //para terminar o jogo, sem territorios
						ano = 3;
					}
					fase4Pri = false;
				}
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
		if(imperio->compraTecnologia(arg1)==true){
			os << "Comprou com sucesso a tecnologia: " << arg1 << "\n";
			adquire=true;
		}else{
			os << "Falha a comprar a tecnologia: " << arg1 << "\n";
		}
	}else if (comando == "modifica") {
		if (arg1 == "ouro"){
			imperio->setOuro(imperio->getOuro()+arg2);
		}else if(arg1=="prod"){
			imperio->setProdutos(imperio->getProdutos() + arg2);
		}
	}else if (comando == "fevento") {
		int tamanho = eventosPossiveis.size();
		for(int i=0; i < tamanho; i++){
			if(eventosPossiveis[i]->getNome() == arg1){
				evento = i;
				primeiraVez=false;
			}
		}
	}
	else if (comando == "grava") {
	os << grava->adicionaSave(*imperio, *this, *mundo, *loja, arg1);
	}
	else if (comando == "ativa") {
	os << grava->carregaSave(arg1, *imperio, *this, *mundo);
	}
	else if (comando == "apaga") {
	os << grava->removeSave(arg1);
	}
	return os.str();
}

string Construtor::acaoComandoToma(string comando, string arg1, string arg2){
	ostringstream os;
	if (comando == "toma") {
		if (arg1 == "terr") {
			os << imperio->tomaAssalto(arg2,turno,ano) << "\n";
		}
		else if (arg1 == "tec") {
			os << imperio->tomaAssaltoTec(arg2) << "\n";
		}
		else
			os << "O argumento <" << arg1 << "> nao e valido\n";
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
	
	if (imperio->conquistaTerritorio(nomeTerritorio, fatorSorte,turno,ano) == true){
		os << "Territorio <" << nomeTerritorio << "> conquistado com sucesso.";
		imperio->atualizarPontos();
	}
	else
		os << "Territorio <" << nomeTerritorio << "> nao foi conquistado.";
	return os.str();
}

string Construtor::lista(string arg1){
	ostringstream os;
	
	os << "Turno: " << turno << ", ano: " << ano << ", ultimo fator sorte: " << fatorSorte << "\n";
	os << *imperio;
	if(arg1.empty())
		os << *mundo;
	else
		os << mundo->listaTerritorio(arg1);
	os << *loja;
	os << eventosPossiveis[evento]->getAsString();
	os << "Pontuacao: " << imperio->getPontuacao() << "\n";
	return os.str();
}

int Construtor::getRealUniform(int min, int max) {
	//use time to get seed value for srand
	srand((unsigned int)time(NULL));

	// generate random number between min and max
	int rNum = (min)+(rand() % (max));

	return rNum;
}
