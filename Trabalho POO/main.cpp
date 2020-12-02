#include <iostream>
#include <fstream>
#include <string>
#include "Territorio.h"
#include "Imperio.h"


using namespace std;
int main(){
    string nomeImperador,nomeImperio,comando,arg1;
    int turnos=1, arg2;
    boasVindas();
    cout << "Para Iniciar o jogo teremos de obter duas informacoes.\n";
    cout << "O seu nome: ";
    cin >> nomeImperador;
    cout << "Imperador " << nomeImperador << " qual sera o nome do seu imperio: ";
    cin >> nomeImperio;
    Imperio imperio(nomeImperio,nomeImperador);
    cout << "Iremos adiconar agora o seu Territorio Inicial.\n";
    imperio.adicionaTerritorio("TerritorioInicial",1);
    comandos();
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); //descarta o input buffer
    do{
       comando.clear();
       arg1.clear();
       arg2 = 0;
       getline(cin, comando);
       istringstream stream(comando);
       stream >> comando >> arg1 >> arg2; //obter valores linha
       if (comando == "cria") {
            if (imperio.adicionaTerritorio(arg1, arg2) == true) {
                cout << "Territorio " << arg1 << " adicionado com sucesso!!!\n";
            }else {
                cout << "Nao foi possivel adicionar o Territorio " << arg1 << "!!!\n";
            }
       }else if (comando == "carrega") {
           imperio.carregaConfig(arg1);
       }else if(comando == "feito"){
           cout << "Configuracao feita!\n\n\n"; 
       }else{
           cout << "Comando nao existe.\n";
       }
    }while(comando!="feito");
    cout << imperio.listarImperio() << endl;
    inicio();
    
    do{
        comando.clear();
        arg1.clear();
        getline(cin, comando);
        istringstream stream(comando);
        stream >> comando >> arg1; //obter valores linha
        if (comando == "conquista") {
            if(imperio.conquistaTerritorio(arg1)==true)
                cout << arg1 << " conquistado!!!\n";
            else
                cout << arg1 << " nao foi conquistado!!!\n";

        }else if (comando == "lista") {
            if (arg1.empty()) {
                cout << imperio;
            }else {
                imperio.listar(arg1);
            }
        }else if(comando=="avanca" || comando == "passa"){
            cout << "A avancar 1 turno.\n";
            cout << "Turno a terminar: " << turnos << "\n";
            turnos++;
            imperio.setTurno(turnos); 
            cout << "Turno a comecar: " << turnos << "\n";
        }else{
            cout << "Comando nao Existe!!!\n";
        }
        
    } while (turnos <= 12);
    cout << "\n\n\n\n\nIremos mostrar agora o seu Imperio " << imperio.getNomeImperador() << "\n";
    cout << imperio.listarImperio() << endl;
}