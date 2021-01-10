#include "Interface.h"
#include <iostream>
#include <fstream>
#include <string>

void Interface::iniciarInterface(){
    /* Atributos do comando */
    string comando, arg1;
    int arg2;
    string resposta;
    /* ------------------- */
    /* Iniciar Construtor e Obter Valores do Construtor */
    
    
    Loja loja;
    Mundo mundo("mundo");
    Imperio imperio(2, mundo);

    Construtor construtor(1, 1,loja,mundo,imperio);
    int ano = construtor.getAno();
    int turno = construtor.getTurno();
    /* ----------------------------------------------- */
    cout << "Seja Bem Vindo!!!" << endl;
    do {
        /*reset ao comando*/
        comando.clear();
        arg1.clear();
        arg2 = 0;

        getline(cin, comando); //obter comando
        istringstream stream(comando);
        stream >> comando >> arg1 >> arg2; //obter valores linha

        resposta = construtor.lerComando(comando, arg1, arg2);
        cout << resposta << endl;

        turno = construtor.getTurno();
        ano = construtor.getAno();
    } while (turno <= 6 && ano <= 2);
}
