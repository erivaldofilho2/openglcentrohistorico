#include "desenho.h"

unsigned int Desenho::desenha_mesa (float pos_x, float pos_y, float pos_z) {
    Desenha_gl gl (pos_x, pos_y, pos_z, proporcao);
    
    /* inicia a composicao do predio */
    unsigned int mesa = glGenLists (1);
    glNewList (mesa, GL_COMPILE);

    glEndList();
    return mesa;
}