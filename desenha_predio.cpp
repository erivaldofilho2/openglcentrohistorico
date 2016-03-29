#include "desenho.h"

unsigned int Desenho::desenha_predio(float pos_x, float pos_y, float pos_z) {
    float proporcao = 2;
    Desenha_gl gl (pos_x, pos_y, pos_z, proporcao);

    float cor_parede[3] = {0xa3/256.0, 0x90/256.0, 0x7f/256.0};
    
    float parede_largura = 0.1;
    float frontal_comprimento = 15.0, frontal_altura = 6.5;
    float lateral_comprimento = 7.0, lateral_altura = 5.0;
    float entrada_garagem_altura = 2.7;
    float entrada_garagem_largura = 3;
    float portao_garagem_altura = 2.2;
    float portao_garagem_lagura = 2;
    float portao_garagem_espessura = 0.05;

    /* inicia a composicao do predio */
    unsigned int predio = glGenLists (1);
    glNewList (predio, GL_COMPILE);

    // Desenha chão
    glColor3f (0.0, 0.2, 0.0);
    glBegin (GL_QUADS);
        glVertex3f (-100, 0, -100);
        glVertex3f (-100, 0,  100);
        glVertex3f ( 100, 0,  100);
        glVertex3f ( 100, 0, -100);
    glEnd();
    
    // parede frontal
    glColor3f ( cor_parede[0], cor_parede[1], cor_parede[2] );
    gl.define_deslocamento (0, frontal_altura / 2, 0);
    gl.define_escala (frontal_comprimento, frontal_altura, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // parede de fundo
    gl.define_deslocamento (0, lateral_altura / 2, -lateral_comprimento);
    gl.define_escala (frontal_comprimento, lateral_altura, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    
    // parede lateral esquerda
    gl.define_deslocamento (-frontal_comprimento / 2, lateral_altura / 2, -lateral_comprimento / 2);
    gl.define_escala (lateral_comprimento, lateral_altura, parede_largura);
    gl.define_rotacao (90, 0, 1, 0);
    gl.desenha_cubo();

    // parede lateral direita
    gl.define_deslocamento (frontal_comprimento / 2, lateral_altura / 2, -lateral_comprimento/2);
    gl.define_escala (lateral_comprimento, lateral_altura, parede_largura);
    gl.define_rotacao (90, 0, 1, 0);
    gl.desenha_cubo();

    // entrada da garagem
    gl.define_deslocamento (frontal_comprimento / 2 + entrada_garagem_largura / 2, entrada_garagem_altura / 2, 0);
    gl.define_escala (entrada_garagem_largura, entrada_garagem_altura, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    glEndList();
    return predio;
}