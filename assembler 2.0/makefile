tp1: main.cpp funcoes.cpp
	g++ -o mont main.cpp funcoes.cpp

run: main.cpp funcoes.cpp
	g++ -o mont main.cpp funcoes.cpp
	clear
	./mont ../tst/teste_moodle.a ../tst/teste_moodle_saida.mif
	cat ../tst/teste_moodle_saida.mif

val: main.cpp funcoes.cpp
	g++ -g -o mont main.cpp funcoes.cpp
	reset
	valgrind --leak-check=full --track-origins=yes ./mont ../tst/teste_moodle.a ../tst/teste_moodle_saida.mif

clean:
	rm mont