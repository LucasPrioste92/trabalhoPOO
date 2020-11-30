#include "Territorio.h"

int nP,nM,nF,nMin,nD,nC,nR,nPs;

Territorio::Territorio(string nomeTipo){
    stringstream ss;
    
    // não deixar que o territorio inicial seja criado mais que uma vez
    if(nomeTipo == "TerritorioInicial" ){
        tipoTerritorio = 0;
        nome = nomeTipo;
        resistencia = 9;
        criacaoProdutos = 1;
        criacaoOuro = 1;
        pontosVitoria = 0;
        conquistado = 1;
    }else if (nomeTipo == "Planicie") {
        nP++;
        tipoTerritorio = 1;
        ss << nomeTipo << nP;
        nome = ss.str();
        resistencia = 5;
        criacaoProdutos = 1;
        criacaoOuro = 1;
        pontosVitoria = 1;
        conquistado = 0;
    }else if (nomeTipo == "Montanha") {
        nM++;
        tipoTerritorio = 1;
        ss << nomeTipo << nM;
        nome = ss.str();
        resistencia = 6;
        criacaoProdutos = 0;
        criacaoOuro = 0;
        pontosVitoria = 1;
        conquistado = 0;
    }else if (nomeTipo == "Fortaleza") {
        nF++;
        tipoTerritorio = 1;
        ss << nomeTipo << nF;
        nome = ss.str();
        resistencia = 8;
        criacaoProdutos = 0;
        criacaoOuro = 0;
        pontosVitoria = 1;
        conquistado = 0;
    }else if (nomeTipo == "Mina") {
        nMin++;
        tipoTerritorio = 1;
        ss << nomeTipo << nMin;
        nome = ss.str();
        resistencia = 5;
        criacaoProdutos = 0;
        criacaoOuro = 1;
        pontosVitoria = 1;
        conquistado = 0;
    }else if (nomeTipo == "Duna") {
        nD++;
        tipoTerritorio = 1;
        ss << nomeTipo << nD;
        nome = ss.str();
        resistencia = 4;
        criacaoProdutos = 1;
        criacaoOuro = 0;
        pontosVitoria = 1;
        conquistado = 0;
    }else if (nomeTipo == "Castelo") {
        nC++;
        tipoTerritorio = 1;
        ss << nomeTipo << nC;
        nome = ss.str();
        resistencia = 7;
        criacaoProdutos = 3;
        criacaoOuro = 1;
        pontosVitoria = 1;
        conquistado = 0;
    }else if (nomeTipo == "Refugio") {
        nR++;
        tipoTerritorio = 2;
        ss << nomeTipo << nR;
        nome = ss.str();
        resistencia = 9;
        criacaoProdutos = 0;
        criacaoOuro = 1;
        pontosVitoria = 2;
        conquistado = 0;
    }else if (nomeTipo == "Pescaria") {
        nPs++;
        tipoTerritorio = 2;
        ss << nomeTipo << nPs;
        nome = ss.str();
        resistencia = 9;
        criacaoProdutos = 2;
        criacaoOuro = 0;
        pontosVitoria = 2;
        conquistado = 0;
    }else {
        return;
    }
    
    
    
    
}

ostream &operator<<(ostream &os, const Territorio &t) {
    os << "Territorio : " << t.getNomeTerritorio() << ", resistencia " << t.getResistencia() << ", criacao de ouro " << t.getCriacaoOuro() << ", criacao de produto " << t.getProdutos() << ", pontos por conquista " << t.getPontosVitoria();
    return os;
}