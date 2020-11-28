#include <iostream>
#include "Territorio.h"
#include "Imperio.h"

using namespace std;
int main(){
    string nomeImperador,nomeImperio;
    boasVindas();
    cout << "Para Iniciar o jogo teremos de obter duas informacoes.\n";
    cout << "O seu nome: ";
    cin >> nomeImperador;
    cout << "Imperador " << nomeImperador << " qual sera o nome do seu imperio: ";
    cin >> nomeImperio;
    Imperio imperio(nomeImperio,nomeImperador);
    cout << "Iremos adiconar agora o seu Territorio Inicial.\n";
    imperio.adicionaTerritorio("TerritorioInicial",1);
    /*imperio.adicionaTerritorio("Duna", 5);
    imperio.adicionaTerritorio("Montanha", 3);
    imperio.adicionaTerritorio("TerritorioInicial", 1);
    imperio.adicionaTerritorio("Duna", -2);
    imperio.adicionaTerritorio("Duna", 2);*/
    cout << imperio;
    
    /*Territorio t1("TerritorioInicial");
    Territorio t2("Mina");
    Territorio t3("Mina");
    cout << t1 << endl;
    cout << t3 << endl;*/
}