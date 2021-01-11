#include "Eventos.h"
#include "Imperio.h"
#include <sstream>
#include <random>
#include <time.h>

string Eventos::acaoEvento(Imperio& i, Mundo& m,int ano,int turno){
    return string();
}

string Eventos::getAsString() const{
    ostringstream os;
    os << "Nome: " << nome << "\n";
    return os.str();
}

int Eventos::getRealUniform(int min, int max) {
    //use time to get seed value for srand
    srand((unsigned int)time(NULL));

    // generate random number between min and max
    int rNum = (min)+(rand() % (max));

    return rNum;
}

string RecursoAbandonado::acaoEvento(Imperio& i,Mundo& m,int ano, int turno){
    ostringstream os;
    if(ano==1){
        if(i.getProdutos() < i.getArmazem()){
            i.setProdutos(i.getProdutos()+produto);
            os << "Ganhou um produto abandonado.\n";
        }else{
            os << "Ja tem o maximo de produtos.\n";
        }
    }else if(ano==2){
        if (i.getOuro() < i.getCofre()) {
            i.setOuro(i.getOuro()+ouro);
            os << "Ganhou um ouro abandonado.\n";
        }
        else {
            os << "Ja tem o maximo de ouro.\n";
        }
    }
    return os.str();
}

string RecursoAbandonado::getAsString() const{
    ostringstream os;
    os << Eventos::getAsString();
    os << "um recurso abandonado foi encontrado e fornece ao império uma unidade de produtos ou de ouro\n";
    return os.str();
}

string Invasao::acaoEvento(Imperio& i, Mundo &m, int ano, int turno){
    ostringstream os;
    default_random_engine re;
    fatorSorte = getRealUniform(1, 6);
  
    int total = i.getTerritoriosConquistados().size()-1;
    int resultado = 0;
    int res = i.getTerritoriosConquistados()[total]->getResistencia();
    bool verificaTecnologia = i.verificarTecnologia("defesasTerritoriais");
    if(verificaTecnologia == true){
        res += i.getResistenciaExtra();
    }
    if(ano==1)
        resultado = fatorSorte + forca1;
    else
        resultado = fatorSorte + forca2;
    if(res < resultado){
        string auxNome = i.getTerritoriosConquistados()[total]->getNomeTerritorio();
        i.perdeTerritorio(auxNome);
        os << "Conquistaram o seu Territorio <" << auxNome << ">\n";
    }else{
        os << "Tentaram conquistar o seu Territorio <" << i.getTerritoriosConquistados()[total]->getNomeTerritorio() << "> mas nao conseguiram.\n";
    }
    return os.str();
}

string Invasao::getAsString() const{
    ostringstream os;
    os << Eventos::getAsString();
    os << "um qualquer outro imperio concorrente, do qual nem sequer existe qualquer registo, esta a tentar conquistar um dos territorios do jogador\n";
    return os.str();
}

string AliancaDiplomatica::acaoEvento(Imperio& i, Mundo& m, int ano, int turno){
    ostringstream os;
    if(i.getForcaMilitar() < i.getMaxForcaMilitar()){
        i.setForcaMilitar(i.getForcaMilitar()+aumentaForca);
        os << "Alianca Feita, ganhou mais uma forca militar.\n";
    }else{
        os << "Alianca Feita.\n";
    }
    return os.str();
}

string AliancaDiplomatica::getAsString() const{
    ostringstream os;
    os << Eventos::getAsString();
    os << "foi assinada uma aliança com um outro imperio do qual tambem nao existe nenhum registo\n";
    return os.str();
}

string SemEvento::acaoEvento(Imperio& i, Mundo& m, int ano, int turno){
    ostringstream os;
    os << "Sem Evento, Podem dormir descansados.\n";
    return os.str();
}

string SemEvento::getAsString() const{
    ostringstream os;
    os << Eventos::getAsString();
    os << "nada ocorre e todos podem dormir descansados\n";
    return os.str();
}
