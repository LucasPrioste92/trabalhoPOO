#include <iostream>
#include <fstream>
#include <string>
#include "Territorio.h"
#include "Imperio.h"


using namespace std;
int main(){
    string nomeImperador,nomeImperio,comando,arg1;
    int turnos=0, arg2;
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
    do{
       arg2=0;
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
           imperio.carregaConfig(arg1, imperio);
       }else {
           cout << "Comando nao existe.\n";
       }
    }while(comando!="feito");
    /*if (comando == "conquista") {
        cin >> arg1;

    }
    else if (comando == "lista") {
        cin >> arg1;
        if (arg1 == "all") {
            cout << imperio;
        }
        else {
            imperio.listar(arg1, imperio);
        }
    }*/
    cout << "Iremos mostrar agora o seu Imperio.\n";
    cout << imperio;
}