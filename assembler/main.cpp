#include "func.h"

int main(int argc, char const *argv[]){
	ifstream entrada;
	ofstream saida;
	string pega_linha, operador;
	stringstream linha;

	entrada.open(argv[1]);
	saida.open("saida.mif");

	saida << "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n" << endl;
	//inicio do programa ********************************

	getline(entrada, pega_linha, '\n'); //Lê a próxima linha inteira
	linha << pega_linha;				//copia a linha no stringStream
	// cout << linha.str() << endl;		
	linha >> operador;					//copia a primeira info da string
	cout << operador << endl;
	cout << operador_binario(operador) << endl;
	

	//fim do programa **********************************
	saida << "END;" << endl;
	
	entrada.close();
	saida.close();

	return 0;
}