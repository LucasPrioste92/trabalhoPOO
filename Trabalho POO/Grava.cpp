#include "Grava.h"
#include <tuple>

string Grava::adicionaSave(Imperio& i, Construtor& c, Mundo& m, Loja& l, const string& nomeSave) {
    ostringstream os;
    if (verificaNomeGrava(nomeSave) == false) {
        copias.push_back(tuple<string, Construtor, Imperio, Mundo, Loja>(nomeSave, c, i, m, l));
        os << "Save guardado com sucesso <" << nomeSave << ">\n";
    }
    else {
        os << "O nome do Save ja existe.\n";
    }
    return os.str();
}

bool Grava::verificaNomeGrava(string nome) {
    for (auto& tuple : copias) {
        if (get<0>(tuple) == nome) {
            return true;
        }
    }
    return false;
}

string Grava::removeSave(const string& nome) {
    ostringstream os;
    auto it = copias.begin();
    while (it < copias.end()) {
        if (get<0>(*it) == nome) {
            copias.erase(it);
            os << "Apagado com sucesso <" << nome << ">\n";
            return os.str();
        }
        it++;
    }
    os << "A gravacao com o nome <" << nome << "> nao existe.\n";
    return os.str();
}

string Grava::carregaSave(const string& nome, Imperio& i, Construtor& c, Mundo& m) {
    ostringstream os;
    for (auto& cop : copias) {
        if (get<0>(cop) == nome) {

            c = get<1>(cop);
            i = get<2>(cop);
            m = get<3>(cop);
          
            os << "Carregado com sucesso <" << nome << ">\n";
            return os.str();
        }
    }
    os << "A gravacao com o nome <" << nome << "> nao existe.\n";
    return os.str();
}