tp1: main.cpp funcoes.cpp
	g++ -o mont main.cpp funcoes.cpp
	@echo ""
	@echo "Programa compilado!"
	@echo "Um executável chamado 'mont' foi criado."
	@echo "Para executar use o comando ./mont entrada.a saida.mif"
	@echo ""

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