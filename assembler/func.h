#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

#include <stdio.h>

using namespace std;

typedef struct Formato{
	string operador_bin;
	string reg1_bin;
	string reg2_bin;
	string un5;
	int num_operandos;
	int PC;
}Formato;

typedef struct Label{
	string nome_label;
	int endereco_label;
}Label;

void preenche_lista_labels(vector<Label>*, int, string);
Formato decode(string);
string num_reg(string);