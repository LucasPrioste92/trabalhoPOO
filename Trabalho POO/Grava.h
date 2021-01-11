#ifndef GRAVA
#define GRAVA

#include "Construtor.h"
#include <tuple>

class Construtor;

using namespace std;
class Grava{
	vector<tuple<string, Construtor,Imperio,Mundo, Loja>> copias;
public:
	Grava() = default;
	string adicionaSave(Imperio& i, Construtor& c, Mundo& m, Loja& l, const string& nomeSave);
	bool verificaNomeGrava(string nome);
	string removeSave(const string& nome);
	string carregaSave(const string& nome, Imperio& i, Construtor& c, Mundo &m, Loja& l);
	~Grava() = default;
};


#endif // !GRAVAMUNDO_H


