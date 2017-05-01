#include "func.h"

string operador_binario(string operador){
	string binario;

	if (operador == "exit"){
		binario = "00000";
	}
	else if (operador == "loadi"){
		binario = "00001";
	}
	else if (operador == "storei"){
		binario = "00010";
	}
	else if (operador == "add"){
		binario = "00011";
	}
	else if (operador == "subtract"){
		binario = "00100";
	}
	else if (operador == "multiply"){
		binario = "00101";
	}
	else if (operador == "divide"){
		binario = "00110";
	}
	else if (operador == "jump"){
		binario = "00111";
	}
	else if (operador == "jmpz"){
		binario = "01000";
	}
	else if (operador == "jmpn"){
		binario = "01001";
	}
	else if (operador == "move"){
		binario = "01010";
	}
	else if (operador == "load"){
		binario = "01011";
	}
	else if (operador == "store"){
		binario = "01100";
	}
	else if (operador == "loadc"){
		binario = "01101";
	}
	else if (operador == "clear"){
		binario = "01110";
	}
	else if (operador == "negate"){
		binario = "01111";
	}
	else if (operador == "push"){
		binario = "10000";
	}
	else if (operador == "pop"){
		binario = "10001";
	}
	else if (operador == "addi"){
		binario = "10010";
	}
	else if (operador == "call"){
		binario = "10011";
	}
	else /*(operador == "return")*/{
		binario = "10100";
	}

	return binario;
}