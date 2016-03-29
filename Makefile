# Compila e executa com o comando make (unix like)
FONTE=main.cpp desenha_predio.cpp desenha_janela.cpp
OBJETO=main.o desenha_predio.o desenha_janela.o
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
	rm -f $(APP)
