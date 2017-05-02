#include "func.h"

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
	else /*if (reg == "A7")*/{
		reg_num = "111";
	}

	return reg_num;
}

formato decode(string pega_linha){
	formato formato_inst;
	string operador, operando1, operando2;
	stringstream linha;
	linha << pega_linha;

	linha >> operador; //Lê a primeira informação da linha (operador ou label)

	if (operador == "exit"){
		formato_inst.operador_bin = "00000";
	}
	else if (operador == "loadi"){
		formato_inst.operador_bin = "00001";
	}
	else if (operador == "storei"){
		formato_inst.operador_bin = "00010";
	}
	else if (operador == "add"){
		formato_inst.operador_bin = "00011";
		linha >> operando1;
		formato_inst.reg1_bin = num_reg(operando1);
		linha >> operando2;
		formato_inst.reg2_bin = num_reg(operando2);
		formato_inst.un5 = "00000";
	}
	else if (operador == "subtract"){
		formato_inst.operador_bin = "00100";
	}
	else if (operador == "multiply"){
		formato_inst.operador_bin = "00101";
	}
	else if (operador == "divide"){
		formato_inst.operador_bin = "00110";
	}
	else if (operador == "jump"){
		formato_inst.operador_bin = "00111";
	}
	else if (operador == "jmpz"){
		formato_inst.operador_bin = "01000";
	}
	else if (operador == "jmpn"){
		formato_inst.operador_bin = "01001";
	}
	else if (operador == "move"){
		formato_inst.operador_bin = "01010";
	}
	else if (operador == "load"){
		formato_inst.operador_bin = "01011";
	}
	else if (operador == "store"){
		formato_inst.operador_bin = "01100";
	}
	else if (operador == "loadc"){
		formato_inst.operador_bin = "01101";
	}
	else if (operador == "clear"){
		formato_inst.operador_bin = "01110";
	}
	else if (operador == "negate"){
		formato_inst.operador_bin = "01111";
	}
	else if (operador == "push"){
		formato_inst.operador_bin = "10000";
	}
	else if (operador == "pop"){
		formato_inst.operador_bin = "10001";
	}
	else if (operador == "addi"){
		formato_inst.operador_bin = "10010";
	}
	else if (operador == "call"){
		formato_inst.operador_bin = "10011";
	}
	else /*(operador == "return")*/{
		formato_inst.operador_bin = "10100";
	}

	return formato_inst;
}