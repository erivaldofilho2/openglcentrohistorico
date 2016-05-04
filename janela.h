#ifndef JANELA_H
#define JANELA_H

#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "desenho.h"
#include "SOIL.h"
//#include "iluminacao.hpp"

#define PI 3.1415926535897932

class Janela {
public:
    Janela();
    void reajusteJanela (int largura, int altura);
    void exibir (void);
    void teclasEspeciais (int key, int x, int y);
    void teclado (unsigned char key, int x, int y);
private:
    unsigned int modelagem; // indentificador de lista de chamada
    float proporcao;
    Desenho desenhista; // coleção de funções que desenha os objetos
    bool fullscreenmode;
    float vetor_x, vetor_y, vetor_z; // vetor direção da câmera
    float x, y, z; // posição da câmera
    float deltaMove;
    float lateralMove;
    float deltaAngle;
    float verticalMove;
    float aberturaPorta;
    float aberturaPortaLateral;
    // iluminação
    void defineLuzESPECULAR (void);
    void defineLuzAMBIENTE (void);
    void defineLuzDIFUSA (void);
    GLfloat ratio;
    static const int AMBIENTE = 0;
    static const int DIFUSA = 1;
    static const int ESPECULAR = 2;
    float ambiente[3];
    int ModoDeIluminacao;
    int LuzAmbEhMax;
};

#endif