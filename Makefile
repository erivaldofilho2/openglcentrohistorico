# Compila e executa com o comando 'make' (construtor automático)
FONTE=main.cpp\
      predio.cpp\
      janela.cpp\
      mesa.cpp\
      cadeira.cpp\
      quadro.cpp\
      computador.cpp
OBJETO=main.o\
       predio.o\
       janela.o\
       mesa.o\
       cadeira.o\
       quadro.o\
       computador.o
APP=centro_historico.app

CC=g++
GLFLAGS=-lglut -lGL -lGLU
CFLAGS=-std=c++11 -Wall

all: compila
	./$(APP) # executa

compila: objeto
	$(CC) -o $(APP) $(OBJETO) $(GLFLAGS)

objeto:
	$(CC) -c $(CFLAGS) $(FONTE)

clear:
	rm -f $(APP) *.o
