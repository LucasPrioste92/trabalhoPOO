#include "Tecnologia.h"
#include "Imperio.h"

bool Tecnologia::ligaImperio(Imperio*i){
    if (imperio != nullptr || i == nullptr)
        return false;
    imperio = i;
    return  true;
}

bool Tecnologia::desligaImperio(Imperio*i){
    if (imperio != i)
        return false;
    imperio = nullptr;
    return true;
}

bool Tecnologia::acaoTecnologia(){
    return false;
}

string Tecnologia::getAsString() const{
    ostringstream os;
    os << "Nome: " << nome << ", Preco: " << custo << "\n";
    if(imperio==nullptr)
        os << "Estado: Nao Comprado\n";
    else
        os << "Estado: Comprado\n";
    return os.str();
}

bool DronesMilitares::acaoTecnologia(){
    
    if (imperio->getMaxForcaMilitar() == maxForcaMilitar)
        return false;
    imperio->setMaxForcaMilitar(maxForcaMilitar);
    return true;
}

string DronesMilitares::getAsString() const
{
    ostringstream os;
    os << "Drones Militares: passar o limite máximo da força militar para 5\n";
    os << Tecnologia::getAsString();
    return os.str();
}

bool DefesasTerritoriais::acaoTecnologia(){
    imperio->setResistenciaExtra(resistencia);
    return true;
}

string DefesasTerritoriais::getAsString() const{
    ostringstream os;
    os << "Defesas Territoriais: : e um equipamento especial de defesa que acrescenta 1 unidade a resistencia do territorio invadido durante um evento de invasao\n";
    os << Tecnologia::getAsString();
    return os.str();
}

bool BancoCentral::acaoTecnologia(){
   
    if(imperio->getArmazem() != maxArmazem)
        imperio->setArmazem(maxArmazem);
    if (imperio->getCofre() != maxCofre)
        imperio->setCofre(maxCofre);
    return true;
}

string BancoCentral::getAsString() const
{
    ostringstream os;
    os << "Banco Central: esta tecnologia permite aumentar em duas unidades a capacidade de armazenamento do armazem e do cofre do imperio \n";
    os << Tecnologia::getAsString();
    return os.str();
}

string MisseisTeleguiados::getAsString() const
{
    ostringstream os;
    os << "Misseis Teleguiados: esta tecnologia e necessaria para conquistar ilhas\n";
    os << Tecnologia::getAsString();
    return os.str();
}

string BolsaDeValores::getAsString() const
{
    ostringstream os;
    os << "Bolsa de Valores: sistema comercial que torna possíveis as trocas entre produtos e ouro \n";
    os << Tecnologia::getAsString();
    return os.str();
}

ostream& operator<<(ostream& os, const Tecnologia& t)
{
    os << t.getAsString();
    return os;
}
