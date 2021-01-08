#include "Tecnologia.h"

bool Tecnologia::acaoTecnologia(Imperio &i){
    return false;
}

bool DronesMilitares::acaoTecnologia(Imperio &i){
    if (i.getMaxForcaMilitar() == maxForcaMilitar)
        return false;
    i.setMaxForcaMilitar(maxForcaMilitar);
    return true;
}

bool DefesasTerritoriais::acaoTecnologia(Imperio& i){
    i.setResistenciaExtra(resistencia);
    return true;
}

bool BancoCentral::acaoTecnologia(Imperio& i){
    if(i.getArmazem() != maxArmazem)
        i.setArmazem(maxArmazem);
    if (i.getCofre() != maxCofre)
        i.setCofre(maxCofre);
    return true;
}
