#include "desenho.h"

unsigned int Desenho::desenha_cadeira (float pos_x, float pos_y, float pos_z) {
    Desenha_gl gl (pos_x, pos_y, pos_z, proporcao);
    
    /* inicia a composicao do predio */
    unsigned int cadeira = glGenLists (1);
    glNewList (cadeira, GL_COMPILE);

    glEndList();
    return cadeira;
}