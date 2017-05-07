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
	vector<Tabela_tipos> lista_tipos(22);

	preenche_tabela_tipos(lista_tipos);

	entrada.open(argv[1]); //Abre o arquivo de entrada usando o primeiro argumento
	saida.open(argv[2]); //Cria o arquivo de saida

	//Escreve o cabeçalho do arquivo tipo .mif
	escreve_cabecalho_mif(&saida);

	//Preenche a lista de labels com o nome e endereço de cada uma
	preenche_lista_labels(&entrada, lista_labels); //Passagem 1

	//Transforma cada instrução lida em seu equivalente binário
	traduz_programa_fonte(&entrada, memoria, lista_labels, lista_tipos, pilha); //Passagem 2

	//Printa o conteúdo da memória no arquivo de saída
	printa_memoria(&entrada, &saida, memoria);	

	entrada.close();
	saida.close();
	return 0;
}

/*
	//Printa a lista de tipos
	// for (int i = 0; i < lista_tipos.size(); ++i){
	// 	cout << lista_tipos[i].nome_operacao << "\t";
	// 	cout << lista_tipos[i].tipo_operacao << endl;
	// }
	// cout << lista_tipos.size() << " instruções" << endl;

	// Printa a lista de labels
	for(int i=0; i<lista_labels.size(); i++){
		cout << lista_labels[i].nome_label << " - ";
		cout << hex << lista_labels[i].endereco_label << endl;
	}
	
	A fazer:
	//Terminar a função traduz_programa_fonte()
	//TIRAR O LIMITE DE 55 DA SAÍDA (ta assim só pra teste)
	//Escrever e testar os programas em assembly (testar no CPUSim)

	Fazer ao menos dois programas em Assembly que, juntos, executem ao menos dois
	terços das instruções da máquina Swombat (melhor testar todas) e ao menos uma
	chamada de função ou procedimento.

	Pra rodar o TP usar sempre "make run" 
*/