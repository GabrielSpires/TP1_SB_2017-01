#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <stdio.h>

using namespace std;

typedef struct formato{
	string operador_bin;
	string reg1_bin;
	string reg2_bin;
	string un5;
	int num_operandos;
}formato;

formato decode(string pega_linha);
string num_reg(string reg);