#include "Territorio.h"

Territorio::Territorio(string n, int res, int criacaoPro, int criacaoO, int pontos) {
    nome = n;
    resistencia = res;
    criacaoProdutos = criacaoPro;
    criacaoOuro = criacaoO;
    pontosVitoria = pontos;
}

bool Territorio::ligaImperio(Imperio *i){
    if (imperio != nullptr || i == nullptr)
        return false;
    imperio = i;
    return  true;
}

bool Territorio::desligaImperio(Imperio *i){
    if (imperio != i)
        return false;
    imperio = nullptr;
    return true;
}

bool Territorio::ContinenteOuIlha() const{
    return false;
}

string Territorio::getAsString() const{
    ostringstream os;
    os << "\n------------------------------\n";
    os << nome << endl;
    os << "Resistencia: " << resistencia << endl;
    os << "Pontos de Vitoria: " << pontosVitoria << endl;
    os << "Criacao de Ouro: " << criacaoOuro << endl;
    os << "Criacao de Produto: " << criacaoProdutos << endl;
    if(imperio == nullptr)
        os << "Territorio nao conquistado\n";
    else
        os << "Territorio conquistado\n";
    
    return os.str();
}




ostream &operator<<(ostream &os, const Territorio &t) {
    os << "Territorio : " << t.getNomeTerritorio() << ", resistencia " << t.getResistencia() << ", criacao de ouro " << t.getCriacaoOuro() << ", criacao de produto " << t.getProdutos() << ", pontos por conquista " << t.getPontosVitoria();
    return os;
}