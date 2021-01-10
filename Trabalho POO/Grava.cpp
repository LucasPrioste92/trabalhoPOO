#include "Grava.h"
#include <tuple>

int GravaMundo::adicionaSave(Mundo& cp, const std::string& nome) {

    if (!copias.empty()) {
        for (const auto& x : copias) {
            if (std::get<0>(x) == nome) {
                return -1;
            }
        }
    }
    try { // pode falhar as copias --> alocacao de memoria
        copias.emplace_back(std::make_tuple(nome, cp));
    }
    catch (...) {
        removeSave(nome); // se por acaso ocorreu introducao no vetor entao remove; se nao existir nao faz nada
        return -2;
    }
    return 1;
}

bool GravaMundo::removeSave(const std::string& nome) {
    for (auto ptr = copias.begin(); ptr != copias.end(); ptr++) {
        if (std::get<0>((*ptr)) == nome) {
            copias.erase(ptr); // nao necessita de liberta espaco porque o objeto Mundo tem um destrutor que o faz. ao remover do vetor esse e chamado
            return true;
        }
    }
    return false;
}

bool GravaMundo::existeSave(const std::string& nome, const Mundo** novo) const {

    for (auto& x : copias) {
        if (std::get<0>(x) == nome) {
            *novo = &(std::get<1>(x));
            return true;
        }
    }
    return false;
}