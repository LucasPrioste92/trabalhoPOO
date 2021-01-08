#include "Loja.h"

Loja::Loja(){
	tecnologiaDisponivel.push_back(new DronesMilitares);
	tecnologiaDisponivel.push_back(new MisseisTeleguiados);
	tecnologiaDisponivel.push_back(new DefesasTerritoriais);
	tecnologiaDisponivel.push_back(new BolsaDeValores);
	tecnologiaDisponivel.push_back(new BancoCentral);
}
