#ifndef GRAVA
#define GRAVA

#include "Mundo.h"
#include <tuple>


class GravaMundo
{
private:
	vector<tuple<string, Mundo>> copias;
public:
	GravaMundo() = default;
	int adicionaSave(Mundo& cp, const string& nome);
	bool removeSave(const string& nome);
	bool existeSave(const string& nome, const Mundo** novo) const;
	~GravaMundo() = default;
};


#endif // !GRAVAMUNDO_H


