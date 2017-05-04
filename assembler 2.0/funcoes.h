#include <iostream> //IO (printf, scanf, etc)
#include <fstream> //IO de arquivos (fopen, etc)
#include <sstream> //Manipulação de strings
#include <iomanip> //Manipulaçao de IO (printar decimal como binario)
#include <vector> //TAD de lista
#include <stack> //TAD de pilha
#include <bitset> //Variável do tipo binario

using namespace std;

//Anotações:
/*
	a = b.to_string(); //Como jogar binario em string
	b = bitset<3>(a);  //Como jogar string em binario
	pilha.push(bitset<8>(string("11110000"))); //Como jogar binario na pilha
*/
typedef struct Tabela_tipos{
	string nome_operacao;
	int tipo_operacao;
}Tabela_tipos;

typedef struct Label{
	string nome_label;
	int endereco_label;
}Label;

int busca_tipo(string, vector<Tabela_tipos>);
int busca_label(string, vector<Label>);
string num_reg(string);
void traduz_programa_fonte(ifstream*, vector<bitset<8> >&, vector<Label>, vector<Tabela_tipos>);
void preenche_lista_labels(ifstream*, vector<Label>&);
void escreve_cabecalho_mif(ofstream*);
void preenche_tabela_tipos(vector<Tabela_tipos>&);