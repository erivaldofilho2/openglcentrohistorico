# Compila e executa com o comando 'make' (construtor automático)
FONTE=main.cpp\
      desenha_predio.cpp\
      desenha_janela.cpp\
      desenha_mesa.cpp\
      desenha_cadeira.cpp\
      desenha_quadro.cpp\
      desenha_computador.cpp\
      desenha_bancada.cpp\
      modelagem.cpp\
      janela.cpp
OBJETO=main.o\
       desenha_predio.o\
       desenha_janela.o\
       desenha_mesa.o\
       desenha_cadeira.o\
       desenha_quadro.o\
       desenha_computador.o\
       desenha_bancada.o\
       modelagem.o\
       janela.o
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
