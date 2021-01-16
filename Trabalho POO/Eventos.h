#ifndef EVENTOS_H
#define EVENTOS_H

#include <vector>
#include <string>

class Imperio;
class Mundo;

using namespace std;
class Eventos{
	string nome;
public:
	Eventos(string n) : nome(n){};
	string getNome() const{return nome;}
	virtual string acaoEvento(Imperio &i, Mundo& m, int ano, int turno) = 0;
	virtual string getAsString() const;
	int getRealUniform(int min, int max);
	virtual ~Eventos() {};
};

class RecursoAbandonado : public Eventos {
	int ouro;
	int produto;
public:
	RecursoAbandonado(string n = "recursoAbandonado",int o = 1,int pro=1) : ouro(o),produto(pro), Eventos(n) {};
	virtual string acaoEvento(Imperio& i, Mundo& m, int ano, int turno) override;
	virtual string getAsString() const override;
	virtual ~RecursoAbandonado() override {};
};

class Invasao : public Eventos {
	int fatorSorte;
	int forca1;
	int forca2;
public:
	Invasao(string n = "invasao",int f1=2,int f2=3) : forca1(f1),forca2(f2),fatorSorte(0), Eventos(n) {};
	virtual string acaoEvento(Imperio& i, Mundo& m, int ano, int turno) override;
	virtual string getAsString() const override;
	virtual ~Invasao() override {};
};
class AliancaDiplomatica : public Eventos {
	int aumentaForca;
public:
	AliancaDiplomatica(string n = "aliancaDiplomatica", int a = 1) : aumentaForca(a),Eventos(n) {};
	virtual string acaoEvento(Imperio& i, Mundo& m,int ano, int turno) override;
	virtual string getAsString() const override;
	virtual ~AliancaDiplomatica() override {};
};
class SemEvento : public Eventos {
public:
	SemEvento(string n = "semEvento") : Eventos(n) {};
	virtual string acaoEvento(Imperio& i,Mundo &m, int ano, int turno) override;
	virtual string getAsString() const override;
	virtual ~SemEvento() override {};
};


#endif