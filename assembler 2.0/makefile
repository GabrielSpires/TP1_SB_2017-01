tp1: main.cpp funcoes.cpp
	g++ -o tp1 main.cpp funcoes.cpp

run: main.cpp funcoes.cpp
	g++ -o tp1 main.cpp funcoes.cpp
	clear
	./tp1 ../tst/teste.a

val: main.cpp funcoes.cpp
	g++ -g -o tp1 main.cpp funcoes.cpp
	reset
	valgrind --leak-check=full --track-origins=yes ./tp1 ../tst/teste.a

clean:
	rm tp1