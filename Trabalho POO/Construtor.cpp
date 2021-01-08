#include "Construtor.h"

#include <random>
#include <ctime>

bool bloquearPassa = false;
bool bloquearConquista = false;

bool recolher = false;

string Construtor::lerComando(string comando, string arg1, int arg2, Mundo& m, Imperio& i){
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
				os << tratarComando(comandoFile,arg1File,arg2File,m,i) << "\n";
				comandoFile.clear();
				arg1File.clear();
				arg2File = 0;
			}
		}else {
			os << "Nao foi possivel abrir o ficheiro.\n";
		}
		file.close();
    }else{
        os << tratarComando(comando,arg1,arg2,m,i);
    }
    return os.str();
}

bool Construtor::comandosExistentes(string comando){
    for(auto c : comandos)
        if(c==comando)
            return true;
    return false;
}

string Construtor::tratarComando(string comando, string arg1, int arg2, Mundo& m, Imperio& i){
	ostringstream os;
	string comandosDebug[3] = {"toma","modifica","fevento"};
	for (int z = 0; z <= 3; z++) {
		if (comando == comandosDebug[z] || comando == "lista") {
			os << acaoComando(comando, arg1, arg2, m, i);
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
		os << acaoComando(comando, arg1, arg2, m, i);
		return os.str();
	}
	

	if(fase==1){ //se a fase for 1
		if(comando=="conquista" && bloquearConquista==false)
			os << acaoComando(comando, arg1, arg2, m, i);
		else if(comando=="passa" && bloquearPassa==false){
			os << acaoComando(comando,arg1,arg2,m,i);
		}else if(comando=="avanca" && (bloquearConquista==true || bloquearPassa==true)){
			os << acaoComando(comando,arg1,arg2,m,i);
		}else{
			os << "O comando <" << comando << "> nao pode ser utilizado neste momento.";
		}
	}else if(fase==2){
		if(recolher==false){ //recolher produtos no inicio da fase
			i.recolher();
			recolher =true;
		}
		if(comando=="maisouro" || comando=="maisprod"){
			os << acaoComando(comando,arg1,arg2,m,i);
		}else if(comando=="avanca"){
			os << acaoComando(comando,arg1,arg2,m,i);
		}else{
			os << "O comando <" << comando << "> nao pode ser utilizado neste momento.";
		}
	}else if(fase==3){
		
	}else if (fase == 4) {

	}
	return os.str();
}

string Construtor::acaoComando(string comando, string arg1, int arg2, Mundo& m, Imperio& i){
	ostringstream os;
	if (comando == "cria") {
		if (adicionaTerritorio(arg1, arg2, m) == true)
			os << "Territorio <" << arg1 << "> adicionado com sucesso.";
		else
			os << "Algo correu mal, Territorio <" << arg1 << "> nao adicionado.";
	}
	else if (comando == "lista") {
		os << listaMundo(m, arg1);
	}
	else if (comando == "conquista") {
		bloquearPassa = true;
		os << conquistaTerritorio(arg1, i, m);
	}
	else if (comando == "avanca") {
		if(fase==4){
			recolher=false;
			fase=1;
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
			os << "Turno a comecar: " << turno << ", Ano: " << ano << "\n";
		}else{
			fase++;
			os << "A avancar para a fase: "<<fase<<"\n";
		}
		bloquearConquista = false;
		bloquearPassa = false;
	}else if(comando=="passa"){
		bloquearConquista = true;
		os << "Fase Bloqueada, quando quiser avancar digite <avanca>\n";
	}
	else if (comando == "maisouro") {
		bool tecnologia = i.verificarTecnologia("bolsaDeValores");
		if(tecnologia==false){
			os << "Nao tem a tecnologia Bolsa de Valores\n";
		}else{
			if(i.getProdutos() < 2){
				os << "Nao tem produtos suficientes\n";
				return os.str();
			}else {
				if(i.verificarOuro() == true){
					os << "A capacidade de ouro ja esta no maximo\n";
					return os.str();
				}else{
					i.ajustarValoresOuro();
					os << "Ganhou mais 1 de ouro e perdeu 2 de produtos\n";
					fase++;
				}
			}

		}
		return os.str();
	}
	else if (comando == "maisprod") {
		bool tecnologia = i.verificarTecnologia("bolsaDeValores");
		if (tecnologia == false) {
			os << "Nao tem a tecnologia Bolsa de Valores\n";
		}
		else {
			if (i.getOuro() < 2) {
				os << "Nao tem ouro suficiente\n";
				return os.str();
			}
			else {
				if (i.verificarPro() == true) {
					os << "A capacidade de ouro ja esta no maximo\n";
					return os.str();
				}
				else {
					i.ajustarValoresProduto();
					os << "Ganhou mais 1 de produtos e perdeu 2 de ouro\n";
					fase++;
					os << "A avancar para a fase: " << fase << "\n";
				}
			}

		}
		return os.str();
	}
	return os.str();
}

bool Construtor::adicionaTerritorio(string nomeTerritorio, int arg2, Mundo& m){
	return m.adicionaTerritorio(nomeTerritorio, arg2);
}

string Construtor::conquistaTerritorio(string nomeTerritorio, Imperio& i, Mundo& m){
	ostringstream os;
	default_random_engine re;
	int fatorSorte = getRealUniform(1, 6);
	
	if (i.conquistaTerritorio(nomeTerritorio, m, fatorSorte) == true)
		os << "Territorio <" << nomeTerritorio << "> conquistado com sucesso.";
	else
		os << "Territorio <" << nomeTerritorio << "> nao foi conquistado.";
	return os.str();
}

string Construtor::listaMundo(Mundo& m, string arg1){
	ostringstream os;
	if(arg1.empty())
		os << m;
	else
		os << m.listaTerritorio(arg1);
	return os.str();
}

double Construtor::getRealUniform(int min, int max) {
	max++;
	static default_random_engine e(time(0));
	static uniform_real_distribution<double> d(min, max);

	return d(e);
}
