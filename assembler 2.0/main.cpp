#include "funcoes.h"

int main(int argc, char const *argv[]){
	vector< bitset<8> > memoria(256, 0); //Lista de 256 binarios de 8 bits iniciados com 0
	stack< bitset<8> > pilha; //Pilha que pode ter até 127 elementos de 8 bits
	bitset<16> regs_uso_geral[8], //Registradores de uso geral
				stackpt, //Stack pointer
				sdr, // Dado recém lido ou a ser escrito na pilha
				buffer1, buffer2, //Recebem os operandos a serem tratados
				ir, //Instruction Register (guarda a instrução a ser decod.)
				mar, //Armazena um endereço a ser lido ou escrito na mem.
				mdr, //Dado recém lido ou a ser escrito na mem.
				status; //Flag halt-bit (se setada interrompe o programa)
	int			pc=0; //Program counter (end. de memoria da próx. instr.)
	ifstream entrada; //InputFile em assembly
	ofstream saida; //OutputFile em formato .mif
	stringstream instrucao; //String manipulável que guarda a instrução atual lida do arq.
	string le_instrucao; //String normal que le do arquivo (nao da pra usar a stringstream)
	vector<Label> lista_labels; //Lista do tipo Label que guarda o nome e endereço de cada label


	entrada.open(argv[1]); //Abre o arquivo de entrada usando o primeiro argumento
	saida.open("saida.mif"); //Cria o arquivo de saida

	//Escreve o cabeçalho do arquivo tipo .mif
	escreve_cabecalho_mif(&saida);

	//Preenche a lista de labels com o nome e endereço de cada uma
	preenche_lista_labels(&entrada, &lista_labels); //Passagem 1

	//O arquivo foi todo lido, então precisamos resetar para ler denovo
	entrada.clear(); //Limpa a flag EOS (End of File)
	entrada.seekg(0, ios::beg); //Volta a ler do inicio do arquivo
	
	traduz_programa_fonte(&entrada, memoria, lista_labels); //Passagem 2

	for(int i=0; i<55; i++, pc++){
		cout << hex << setw(2) << setfill('0') << uppercase << pc << " : " << memoria[i] << ";" << endl; //Printa a memoria
	}

	entrada.close();
	saida.close();
	return 0;
}

	// Printa a lista de labels
	// for(int i=0; i<lista_labels.size(); i++){
	// 	cout << lista_labels[i].nome_label << " - ";
	// 	cout << hex << lista_labels[i].endereco_label << endl;
	// }