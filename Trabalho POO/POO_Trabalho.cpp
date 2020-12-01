#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

void ClearScreen()
{
    cout << string(100, '\n');
}
bool ProcuraCaractersInvalidos(const string& str) {
    for (char i : str) {
        if (i >= 'a' && i <= 'z') {
            continue;
        }
        else if (i >= 'A' && i <= 'Z')
            continue;
        else if (i >= '0' && i <= '9')
            continue;
        else if (i == ' ')
            continue;
        else
            return true;
    }
    return false;
}
int verificanumero(const int numero) {
    if (numero <= 0) {
        return 1;
    }
    else
        return 5;
}
int verificatipot(const string& tipo) {
    if (tipo == "Planicie" || tipo == "Montanha" || tipo == "Fortaleza" || tipo == "Mina" || tipo == "Duna" || tipo == "Castelo" || tipo == "Refugio" || tipo == "Pescaria") {
        return 5;
    }
    else
        return 1;
}
int Verifica_comando_fich_zero(string& o) {
    if (o == "lista") {
        //EXECUTA COMANDO LISTA 
        return 5;
    }
    if (o == "avanca") {
        //EXECUTA COMANDO AVANCA
        return 5;
    }
    if (o == "passa") {
        //EXECUTA COMANDO PASSA
        return 5;
    }
    if (o == "maisouro") {
        //EXECUTA COMANDO MAISOURO
        return 5;
    }
    if (o == "maisprod") {
        //EXECUTA COMANDO MAISPROD
        return 5;
    }
    if (o == "maismilitar") {
        //EXECUTA COMANDO MAISMILITAR
        return 5;
    }
    return -1;
}
int Verifica_comando_fich_um(string& outra,string& arg) {
    if (outra == "conquista") {
        cout << "O comando conquista vai ser executada !" << endl;
        //CRIAR METODO QUE VERIFICA SE EXISTE O TERRITORIO
        return 5;
    }
    if (outra == "adquire"){
        //VERIFICAR SE JA TEM ESSA TECNOLOGIA
        return 5;
    }
    if (outra == "lista") {
        //VERIFICAR SE O TERRITORIO ESPECIFICO EXISTE
        return 5;
    }
    if (outra == "grava") {
        //FAZER COMANDO GRAVA
        return 5;
    }
    if (outra == "ativa") {
        //VERICAR SE O NOME A SER ATIVADO EXISTE
        return 5;
    }
    if (outra == "apaga") {
        //VERIFICAR SE O NOME QUE VAI SER APAGADO EXISTE
        return 5;
    }
    if (outra == "fevento") {
        //EXECUTAR COMANDO
        return 5;
    }
    return -1;
}
int Verifica_comando_fich_dois(string& outra, string& arg1, string& arg2) {
    if (outra == "cria") {
        if ((verificatipot(arg1)) == 5) {
            int n;
            istringstream teste(arg2);
            teste >> n;
            if ((verificanumero(n)) == 5) {
                cout << "Comando valido!" << endl;
                cout << "Vamos criar --> " << arg1 << " Numero de quantas vao ser criadas --> " << n << endl;
                //INSERIR COMANDO
                return 5;
            }
            if ((verificanumero(n)) == 1) {
                cout << "Numero de territorios invalido!" << endl;
                return 1;
            }
        }
        if ((verificatipot(arg1)) == 1) {
            cout << "Tipo de territorio nao reconhecido!" << endl;
            return 1;
        }
    }
    if (outra == "toma") {
        //FAZER A VERIFICACAO
        return 5;
    }
    return -1;
}
int Executa_comando_fich(string& li) {
    string outra, arg1, arg2;
    int n = 0;
    char space = ' ';
    
    
    for (size_t i = 0; i < li.size(); ++i)
        if (li[i] == ' ')
            n++;
    istringstream buff(li);
    if (buff.fail()) {
        return 1;
    }
    if (n == 0) {
        buff >> outra;
        if ((Verifica_comando_fich_zero(outra)) == 5) {
            cout << "Comando executado com sucesso! " << endl;
            return 5;
        }
    }
    if (n == 1) {
        buff >> outra >> arg1;
        if ((Verifica_comando_fich_um(outra,arg1)) == 5) {
            cout << "Comando executado com sucesso! " << endl;
            return 5;
        }
    }
    if (n == 2) {
        buff >> outra >> arg1 >> arg2;
        if ((Verifica_comando_fich_dois(outra, arg1, arg2)) == 5) {
            cout << "Comando executado com sucesso! " << endl;
            return 5;
        }
    }
    return 1;
}
int le_dados(string& nomefich, vector<string*>& comandos) {
    ifstream ficheiro(nomefich);
    string comando;
    string linha;
    int nlinha = 0;
    if (ficheiro) {
        while (getline(ficheiro, linha)) {
            nlinha++;
            if (ProcuraCaractersInvalidos(linha)) {
                cout << "\nA linha --> " << nlinha << "contem caracteres invalidos!" << endl;
                cout << "A ignorar!" << endl;
                continue;
            }
            if ((Executa_comando_fich(linha)) == 5) {

            }
        }
    }
    ficheiro.close();
    return 1;
}
bool verifica_comando(std::string comando, const std::string& comp) {

    std::transform(comando.begin(), comando.end(), comando.begin(), ::tolower);
    return comando == comp;
}
bool setEstado() {
    return true;
}
int verifica_fich(string& comando, const string& com, string& nomefich) {
    string outra;

    if (comando.length() <= 0)
        return 2;
    istringstream buff(comando);

    if (buff >> outra && verifica_comando(outra, "carrega")) {
        if (buff >> nomefich) {
            return 5;
        }
        else {
           std::cout << "\nUSO: carrega <NomeFicheiro>" << "\n";
           return 1;
        }
    }
    cout << "Ficheiro nao reconhecido! " << endl;
    return -1;
 }
int criaterritorios(string& comando, const string& com) {
    string  outra,tipoterritorio;
    int nterritorios;
    if (comando.length() <= 0)
        return 2;
    istringstream buff(comando);

    buff >> outra >> tipoterritorio >> nterritorios;
    if (buff.fail()) {
        return 1;
    }
    if (com == outra) {
        if ((verificatipot(tipoterritorio)) == 5) {
            if ((verificanumero(nterritorios)) == 5) {
                cout << "Comando valido!" << endl;
                cout << "Vamos criar --> " << tipoterritorio << " Numero de quantas vao ser criadas --> " << nterritorios << endl;
                //INSERIR COMANDO
                return 5;
            }
            if ((verificanumero(nterritorios)) == 1) {
                cout << "Numero de territorios invalido!" << endl;
                return 1;
            }
        }
        if ((verificatipot(tipoterritorio)) == 1) {
            cout << "Tipo de territorio nao reconhecido!" << endl;
            return 1;
        }
    }
    return -1;
}
int conquistaterritorio(string& comando, const string& com) {
    string outra,tipoterritorio;

    if (comando.length() <= 0) {
        return 2;
    }
    istringstream buff(comando);

    buff >> outra >> tipoterritorio;

    if (buff.fail()) {
        return 1;
    }

    if (outra == com) {
        //FAZER A VERIFICACAO NO VETOR PARA VER SE O NOME JA EXISTE
        //EXECUTAR O COMANDO CONQUISTA SE A VERIFICACAO ANTERIOR SE VERIFICAR
        return 5;
    }
    return -1;
}
int Executa_comando(string& comando,bool &aberto) {
    string nomefich;
    string arg1;


    int v;
   
    vector<string> args;
    vector<string*> comandos;

    if (comando.length() <= 0) {
        return -10;
    }
    if (aberto == false) {
        if ((v = verifica_fich(comando, "carrega", nomefich)) == 5) {
            cout << "Carregou com sucesso --> " << nomefich << endl;
            le_dados(nomefich, comandos);
            aberto = true;
        }
    }
    if ((v = criaterritorios(comando, "cria")) == 5) {
        cout << "Criado o territorio com sucesso" << endl;
    }
    if ((v = conquistaterritorio(comando, "conquista")) == 5) {
        cout << "Conquistado com sucesso!" << endl;
    }
    return -1;
}
int menu() {
    string comando;
    bool aberto = false;
    do {
        //ClearScreen();
        cout << "--------------------- TP POO ---------------- " << endl;
        cout << "Para listar os comandos disponiveis escreva --> <ajuda>" << endl;
        cout << "Insira um comando --> " ;
        getline(cin, comando);
        if (Executa_comando(comando,aberto) == -20) {
            break;
        }
    } 
    while (true);
    return -1;
}
int main()
{
    menu();
}