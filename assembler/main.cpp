#include "func.h"
#include <bitset>

int main(int argc, char const *argv[]){

	// int a = -1;
	// bitset<8> b(a);
	// cout << b << endl;
	//Variáveis
	int PC = 0;
	ifstream entrada; //arquivo em assembly
	ofstream saida;   //arquivo em binário

	string pega_linha, operador; //strings
	stringstream linha;

	Formato instruction;

	vector<Label> lista_labels; //Vetor do tipo Label
	// vector<> lista_opcodes;
	int *memoria = new int[255]; //Memoria com 256 posições de inteiro
	//**********

	entrada.open(argv[1]); 	 //Abrindo arquivo com assembly
	saida.open("saida.mif"); //Criando arquivo de saida

	//Cabeçalho do arquivo tipo .mif
	saida << "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n" << endl;
	//inicio do programa ********************************

	//Preenche uma lista com as labels e o endereço de cada label
	while(getline(entrada, pega_linha, '\n')){
		linha.str(string()); //Apaga o buffer da string
		linha << pega_linha; //Copia a linha no stringStream

		preenche_lista_labels(&lista_labels, PC, linha.str());
		PC += 2;
	}

	PC = 0; //Reseta o PC
	entrada.clear(); //Limpa a flag EOS (End of File)
	entrada.seekg(0, ios::beg); //Volta ao inicio do arquivo

	while(getline(entrada, pega_linha, '\n')){ //Lê a próxima linha inteira
		linha.str(string()); //Apaga o buffer da string
		linha << pega_linha; //Copia o conteúdo de pega_linha em linha
		// cout << linha.str() << endl; //printa a linha (debug)
		instruction = decode(linha.str());

		//printa a instrução (debug)
		cout << hex << setw(2) << setfill('0') << uppercase << PC << "        :  "; 	//Valor do PC
		cout << instruction.operador_bin + instruction.reg1_bin << ";" << endl; PC++;	//Primeiros 8 bits da instrução
		cout << hex << setw(2) << setfill('0') << uppercase << PC << "        :  "; 	//Valor do PC
		cout << instruction.reg2_bin + instruction.un5 << ";" <<  endl; PC++;			//Últimos 8 bits da instrução
	}

	//fim do programa **********************************
	saida << "END;" << endl;
	
	entrada.close();
	saida.close();

	return 0;
}