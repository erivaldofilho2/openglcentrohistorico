#include "desenho.h"

unsigned int Desenho::desenha_computador (float pos_x, float pos_y, float pos_z) {
    float cor_computador[3] = {1, 1, 1};
    float computador_espessura = 0;
    float computador_comprimento = 0;
    float computador_altura = 0;
    Desenha_gl gl (pos_x, pos_y, pos_z, proporcao);

    /* inicia a composicao do predio */
    unsigned int computador = glGenLists (1);
    glNewList (computador, GL_COMPILE);

    // computador

    glEndList();
    return computador;
}