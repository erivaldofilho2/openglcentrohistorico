# Compila e executa com o comando make (unix like)
FONTE=main.cpp
APP=centro_historico.app

CC=g++
GLFLAGS=-lglut -lGL -lGLU -lGLEW -lSOIL
CFLAGS=-std=c++11

all: compila executa

compila:
	$(CC) $(FONTE) $(GLFLAGS) $(CFLAGS) -o $(APP)

executa:
	./$(APP)

clear:
	rm -f $(APP)

