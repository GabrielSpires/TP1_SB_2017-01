#include "funcoes.h"

int busca_tipo(string campo, vector<Tabela_tipos> lista_tipos){
	for (int i = 0; i < lista_tipos.size(); i++){ //Passa  pela lista de tipos
		if (campo == lista_tipos[i].nome_operacao){ //Testa se o campo foi encontrado
			return lista_tipos[i].tipo_operacao; //Retorna o numero do tipo da instrução
		}
	}
	return -1; //Retorna -1 se nao encontrar nada (erro)
}

int busca_label(string nome_campo, vector<Label> lista_labels){

	for(int i=0; i<lista_labels.size(); i++){
		if(lista_labels[i].nome_label == nome_campo){
			return lista_labels[i].endereco_label;
		}
	}
	return -1;
}

string num_reg(string reg){
	string reg_num;

	if (reg == "A0"){
		reg_num = "000";
	}
	else if (reg == "A1"){
		reg_num = "001";
	}
	else if (reg == "A2"){
		reg_num = "010";
	}
	else if (reg == "A3"){
		reg_num = "011";
	}
	else if (reg == "A4"){
		reg_num = "100";
	}
	else if (reg == "A5"){
		reg_num = "101";
	}
	else if (reg == "A6"){
		reg_num = "110";
	}
	else if (reg == "A7"){
		reg_num = "111";
	}

	return reg_num;
}

void traduz_programa_fonte(ifstream *entrada, vector< bitset<8> > &memoria, vector<Label> lista_labels, vector<Tabela_tipos> lista_tipos){
	stringstream instrucao; //String manipulável que guarda a instrução
	string le_instrucao, //Usada no getline() pra ler o arquivo
		   campo, //Recebe um a um os campos da instrução
		   operador, reg1, reg2, addr, un; //Operandos possiveis
	int pc = 0, addr_int, tipo; //addr_int é a variável que converte o endereço de string p/ int

	while(getline(*entrada, le_instrucao, '\n')){
		instrucao.str(string("")); //Limpa a string pra ler a proxima
		instrucao.clear(); //Apaga o buffer da string
		instrucao << le_instrucao; //Joga a string de le_instrucao na variavel instrucao
		instrucao >> campo; //Lê a primeira informação da instrucao (operador ou label)
		
		if(campo[0] == '_') instrucao >> campo; //Se leu uma label, leia o prox. campo

		tipo = busca_tipo(campo, lista_tipos); //Busca na lista qual o tipo da instrução
		
		if (tipo == 1){ //exit, return |op|un| |5|11|
			if (campo == "exit"){
				memoria[pc] = bitset<8>(string("00000000")); //Escreve 8 zeros na memoria
				memoria[pc+1] = bitset<8>(string("00000000")); //Escreve 8 zeros na memoria
			}
			if (campo == "return"){
				/*
					A  fazer...
				*/
			}
		}
		else if (tipo == 2){ //loadi, storei, jmpz, jmpn |op|reg|addr| |5|3|8|
			if (campo == "loadi") operador = "00001"; //Binário do operador loadi
			if (campo == "storei") operador = "00010";//Binário do operador storei
			if (campo == "jmpz") operador = "01000"; //Binário do operador jmpz
			if (campo == "jmpn") operador = "01001"; //Binário do operador jmp
			
			instrucao >> campo; //Lê o próximo campo
			reg1 = num_reg(campo); //Binário do registrador correspondente
			
			instrucao >> campo; //Lê o próximo campo
			if(campo[0] != '_'){ //Testa se o campo é um numero ou se é IO				
				if (campo == "IO"){ //Se o registrador for o de E/S entao a posição de mem. é a 254
					addr = bitset<8>(254).to_string();
				}
				else { //Se for um numero é só converter pra inteiro e ler da memoria
					istringstream(campo) >> addr_int; //Converte o end. lido em int
					addr = bitset<8>(addr_int).to_string(); //Converte o inteiro em binario e o binario em string
				}
			}
			else{ //O campo é uma variavel que começa com "_"
				addr = bitset<8>(busca_label(campo, lista_labels)).to_string(); //Senão busca o end. da variavel
			}

			memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
			memoria[pc+1] = bitset<8>(addr); //Escreve o segundo byte
		}
		else if (tipo == 3){ //add, subtract, multiply, divide, move, load, store, negate |op|reg|reg|un| |5|3|3|5|
			if (campo == "add") operador = "00011";
			if (campo == "subtract") operador = "00100";
			if (campo == "multiply") operador = "00101";
			if (campo == "divide") operador = "00110";
			if (campo == "move") operador = "01010";
			if (campo == "load") operador = "01011";
			if (campo == "store") operador = "01100";
			if (campo == "negate") operador = "01111";

			instrucao >> campo; //Lê o próximo campo
			reg1 = num_reg(campo); //Binário do registrador correspondente

			instrucao >> campo; //Lê o próximo campo
			reg2 = num_reg(campo); //Binário do registrador correspondente

			un = "00000"; //Bits que não são usados

			memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
			memoria[pc+1] = bitset<8>(reg2+un); //Escreve o segundo byte
		}
		else if (tipo == 4){ //jump, call
			
		}
		else if (tipo == 5){ //loadc, addi
			
		}
		else if (tipo == 6){ //clear, push, pop
			
		}
		else if (tipo == 7){ //.data
			
		}

		// if (campo == "exit"){ //00000 |op|un| |5|11| OK!
		// else if (campo == "loadi"){ //00001 |op|reg|addr| |5|3|8| OK!
		// else if (campo == "storei"){ //00010 |op|reg|addr| |5|3|8|
		// else if (campo == "add"){ //00011 |op|reg|reg|un| |5|3|3|5| OK!
		// else if (campo == "subtract"){ //00100 |op|reg|reg|un| |5|3|3|5| OK!
		// else if (campo == "multiply"){ //00101 |op|reg|reg|un| |5|3|3|5| OK?? (Fazer um programa com multiply!!)
		// else if (campo == "divide"){ //00110 |op|reg|reg|un| |5|3|3|5|
		else if (campo == "jump"){ //00111 |op|un|addr| |5|3|8|
		}
		// else if (campo == "jmpz"){ //01000 |op|reg|addr| |5|3|8|
		// else if (campo == "jmpn"){ //01001 |op|reg|addr| |5|3|8|
		else if (campo == "move"){ //01010 |op|reg|reg|un| |5|3|3|5|
		}
		// else if (campo == "load"){ //01011 |op|reg|reg|un| |5|3|3|5|
		// else if (campo == "store"){ //01100 |op|reg|reg|un| |5|3|3|5|
		else if (campo == "loadc"){ //01101 |op|reg|sgn| |5|3|8|
		}
		else if (campo == "clear"){ //01110 |op|reg|un| |5|3|8|
		}
		else if (campo == "negate"){ //01111 |op|reg|reg|un| |5|3|3|5|
		}
		else if (campo == "push"){ //10000 |op|reg|un| |5|3|8|
		}
		else if (campo == "pop"){ //10001 |op|reg|un| |5|3|8|
		}
		else if (campo == "addi"){ //10010 |op|reg|sgn| |5|3|8|
		}
		else if (campo == "call"){ //10011 |op|un|addr| |5|3|8|
		}
		else if(campo == "return"){ //10100 |op|un| |5|11|
		}
		else if(campo == ".data"){ //Reserva um espaço em memória

		}
		pc += 2; //Incrementa o PC (cada instrução ocupa 2 espaços na mem.)
	}

}

void preenche_lista_labels(ifstream *entrada, vector<Label>& lista_labels){
	stringstream instrucao;
	string le_instrucao, label;
	Label label_aux;
	int pc = 0;

	while(getline(*entrada, le_instrucao, '\n')){ //Lê a linha até o enter
		instrucao.str(string("")); //Limpa a string pra ler a proxima
		instrucao.clear(); //Apaga o buffer da string
		instrucao << le_instrucao; //Joga o que foi lido na string manipulavel
		instrucao >> label; //Lê a primeira informação da linha (operador ou label)

		if (label[0] == '_'){ //Testa se é uma label (começa com "_")
			label_aux.nome_label = label;
			label_aux.nome_label.resize(label.size() -1); //Deleta o : da string (_sign: vira só _sign)
			label_aux.endereco_label = pc;

			lista_labels.push_back(label_aux);
		}
		pc += 2;
	}
}

void escreve_cabecalho_mif(ofstream *saida){
	*saida << "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n" << endl;
}

void preenche_tabela_tipos(vector<Tabela_tipos>& lista_tipos){
	/*	
		Preenche a tabela de tipos levando em consideração
		o número de registradores/operandos que cada instrução
		usa, ou seja, o formato de cada uma.
		Instruções com o mesmo formato são escritas da mesma
		forma na memória, com exceção do opcode, então é útil
		usar uma mesma função para escrever todas as funções de
		um mesmo tipo.
	*/

	// |op5|un11|
	lista_tipos[0].nome_operacao = "exit";
	lista_tipos[0].tipo_operacao = 1;
	lista_tipos[1].nome_operacao = "return";
	lista_tipos[1].tipo_operacao = 1;

	// |op5|reg3|addr8|
	lista_tipos[2].nome_operacao = "loadi";
	lista_tipos[2].tipo_operacao = 2;
	lista_tipos[3].nome_operacao = "storei";
	lista_tipos[3].tipo_operacao = 2;
	lista_tipos[4].nome_operacao = "jmpz";
	lista_tipos[4].tipo_operacao = 2;
	lista_tipos[5].nome_operacao = "jmpn";
	lista_tipos[5].tipo_operacao = 2;

	// |op5|reg3|reg3|un5|
	lista_tipos[6].nome_operacao = "add";
	lista_tipos[6].tipo_operacao = 3;
	lista_tipos[7].nome_operacao = "subtract";
	lista_tipos[7].tipo_operacao = 3;
	lista_tipos[8].nome_operacao = "multiply";
	lista_tipos[8].tipo_operacao = 3;
	lista_tipos[9].nome_operacao = "divide";
	lista_tipos[9].tipo_operacao = 3;
	lista_tipos[10].nome_operacao = "move";
	lista_tipos[10].tipo_operacao = 3;
	lista_tipos[11].nome_operacao = "load";
	lista_tipos[11].tipo_operacao = 3;
	lista_tipos[12].nome_operacao = "store";
	lista_tipos[12].tipo_operacao = 3;
	lista_tipos[13].nome_operacao = "negate";
	lista_tipos[13].tipo_operacao = 3;

	// |op5|un3|addr8|
	lista_tipos[14].nome_operacao = "jump";
	lista_tipos[14].tipo_operacao = 4;
	lista_tipos[15].nome_operacao = "call";
	lista_tipos[15].tipo_operacao = 4;

	// |op5|reg3|sgn8|
	lista_tipos[16].nome_operacao = "loadc";
	lista_tipos[16].tipo_operacao = 5;
	lista_tipos[17].nome_operacao = "addi";
	lista_tipos[17].tipo_operacao = 5;

	// |op5|reg3|un8|
	lista_tipos[18].nome_operacao = "clear";
	lista_tipos[18].tipo_operacao = 6;
	lista_tipos[19].nome_operacao = "push";
	lista_tipos[19].tipo_operacao = 6;
	lista_tipos[20].nome_operacao = "pop";
	lista_tipos[20].tipo_operacao = 6;

	// |.data|numBytes|valor|
	lista_tipos[21].nome_operacao = ".data";
	lista_tipos[21].tipo_operacao = 7;
}