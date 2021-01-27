#include "Interface.h"
#include <iostream>
#include <fstream>
#include <string>

void Interface::iniciarInterface(){
    /* Atributos do comando */
    string comando;
    string resposta;
    /* ------------------- */
    /* Iniciar Construtor e Obter Valores do Construtor */
    
    Grava grava;
    Loja loja;
    Mundo mundo("mundo");
    Imperio imperio(2, mundo,loja);

    Construtor construtor(1, 1,loja,mundo,imperio,grava);
    int ano = construtor.getAno();
    int turno = construtor.getTurno();
    /* ----------------------------------------------- */
    cout << "Seja Bem Vindo!!!" << endl;
    do {
        /*reset ao comando*/
        comando.clear();

        getline(cin, comando); //obter comando
        
        resposta = construtor.lerComando(comando);
        cout << resposta << endl;

        turno = construtor.getTurno();
        ano = construtor.getAno();
    } while (turno <= 6 && ano <= 2);
    cout << "Pontuacao Final: " << imperio.pontuacaoFinal() <<  endl;

}
