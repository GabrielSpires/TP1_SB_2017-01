#include "funcoes.h"

int busca_label(string nome_campo, vector<Label> lista_labels){

	// cout << "Pesquisando campo:" + nome_campo << "..." << endl;
	for(int i=0; i<lista_labels.size(); i++){
		if(lista_labels[i].nome_label == nome_campo){
			return lista_labels[i].endereco_label;
		}
	}
	return 0;
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

void traduz_programa_fonte(ifstream *entrada, vector< bitset<8> > &memoria, vector<Label> lista_labels){
	stringstream instrucao; //String manipulável que guarda a instrução
	string le_instrucao, //Usada no getline() pra ler o arquivo
		   campo, //Recebe um a um os campos da instrução
		   operador, reg1, reg2, addr, un; //Operandos possiveis
	int pc = 0, addr_int; //addr_int é a variável que converte o endereço de string p/ int

	while(getline(*entrada, le_instrucao, '\n')){
		instrucao.str(string("")); //Limpa a string pra ler a proxima
		instrucao.clear(); //Apaga o buffer da string
		instrucao << le_instrucao; //Joga a string de le_instrucao na variavel instrucao
		instrucao >> campo; //Lê a primeira informação da instrucao (operador ou label)
		
		if(campo[0] == '_') instrucao >> campo; //Se leu uma label, leia o prox. campo

		if (campo == "exit"){ //00000 |op|un| |5|11| OK!
			memoria[pc] = bitset<8>(string("00000000")); //Escreve 8 zeros na memoria
			memoria[pc+1] = bitset<8>(string("00000000")); //Escreve 8 zeros na memoria
		}
		else if (campo == "loadi"){ //00001 |op|reg|addr| |5|3|8| OK!
			operador = "00001"; //Binário do operador loadi
			
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
		else if (campo == "storei"){ //00010 |op|reg|addr| |5|3|8|
		}
		else if (campo == "add"){ //00011 |op|reg|reg|un| |5|3|3|5| OK!
			operador = "00011";

			instrucao >> campo; //Lê o próximo campo
			reg1 = num_reg(campo); //Binário do registrador correspondente

			instrucao >> campo; //Lê o próximo campo
			reg2 = num_reg(campo); //Binário do registrador correspondente

			un = "00000"; //Bits que não são usados

			memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
			memoria[pc+1] = bitset<8>(reg2+un); //Escreve o segundo byte
		}
		else if (campo == "subtract"){ //00100 |op|reg|reg|un| |5|3|3|5| OK!
			operador = "00100";

			instrucao >> campo; //Lê o próximo campo
			reg1 = num_reg(campo); //Binário do registrador correspondente

			instrucao >> campo; //Lê o próximo campo
			reg2 = num_reg(campo); //Binário do registrador correspondente

			un = "00000"; //Bits que não são usados

			memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
			memoria[pc+1] = bitset<8>(reg2+un); //Escreve o segundo byte
		}
		else if (campo == "multiply"){ //00101 |op|reg|reg|un| |5|3|3|5| OK?? (Fazer um programa com multiply!!)
			operador = "00101";

			instrucao >> campo; //Lê o próximo campo
			reg1 = num_reg(campo); //Binário do registrador correspondente

			instrucao >> campo; //Lê o próximo campo
			reg2 = num_reg(campo); //Binário do registrador correspondente

			un = "00000"; //Bits que não são usados

			memoria[pc] = bitset<8>(operador+reg1); //Escreve o primeiro byte
			memoria[pc+1] = bitset<8>(reg2+un); //Escreve o segundo byte
		}

		//			 !!CÓDIGO FICANDO MUITO REPETITIVO!!
		// !!FAZER TABELA DE TIPOS (CODIGO VAI FICAR MAIS COMPACTO)!!
		// 			COM ISSO FEITO O TP TA 90%~100% PRONTO

		else if (campo == "divide"){ //00110 |op|reg|reg|un| |5|3|3|5|
		}
		else if (campo == "jump"){ //00111 |op|un|addr| |5|3|8|
		}
		else if (campo == "jmpz"){ //01000 |op|reg|addr| |5|3|8|
		}
		else if (campo == "jmpn"){ //01001 |op|reg|addr| |5|3|8|
		}
		else if (campo == "move"){ //01010 |op|reg|reg|un| |5|3|3|5|
		}
		else if (campo == "load"){ //01011 |op|reg|reg|un| |5|3|3|5|
		}
		else if (campo == "store"){ //01100 |op|reg|reg|un| |5|3|3|5|
		}
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

void preenche_lista_labels(ifstream *entrada, vector<Label>* lista_labels){
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

			lista_labels->push_back(label_aux);
		}
		pc += 2;
	}
}

void escreve_cabecalho_mif(ofstream *saida){
	*saida << "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n" << endl;
}