#include "func.h"

int main(int argc, char const *argv[]){
	//Variáveis
	int PC = -1;
	ifstream entrada; //arquivo em assembly
	ofstream saida;   //arquivo em binário

	string pega_linha, operador; //strings
	stringstream linha;

	formato instruction;
	//**********

	entrada.open(argv[1]); 	//Abrindo arquivo com assembly
	saida.open("saida.mif");//Criando arquivo de saida

	//Cabeçalho do arquivo tipo .mif
	saida << "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n" << endl;
	//inicio do programa ********************************

	while(getline(entrada, pega_linha, '\n')){ //Lê a próxima linha inteira
		linha.str(string()); //Apaga o buffer da string
		linha << pega_linha; //Copia a linha no stringStream
		// cout << linha.str() << endl; //printa a linha (debug)
		instruction = decode(linha.str());

		//printa a instrução (debug)
		PC++; cout << hex << setw(2) << setfill('0') << uppercase << PC << "        :  "; //Valor do PC
		cout << instruction.operador_bin + instruction.reg1_bin << ";" << endl;	  //Primeiros 8 bits da instrução
		PC++; cout << hex << setw(2) << setfill('0') << uppercase << PC << "        :  "; //Valor do PC
		cout << instruction.reg2_bin + instruction.un5 << ";" <<  endl;			  //Últimos 8 bits da instrução
	}

	//fim do programa **********************************
	saida << "END;" << endl;
	
	entrada.close();
	saida.close();

	return 0;
}