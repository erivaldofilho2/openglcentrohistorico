#include "desenho.h"

unsigned int Desenho::geraModelagem (float anguloPortaGaragem, float anguloPortaLateral) {
    unsigned int model = glGenLists (1);
    glNewList (model, GL_COMPILE);

    // inicia organização da modelagem
    desenha_predio (0, 0, 0, anguloPortaGaragem, anguloPortaLateral);
    desenha_mesa (-proporcao*1.5, 0, -proporcao*7+6);
    desenha_mesa (0, 0, -proporcao*7+6);
    desenha_mesa (proporcao*1.5, 0, -proporcao*7+6);
    desenha_mesa (-proporcao*1.5, 0, -proporcao*5.5+6);
    desenha_mesa (0, 0, -proporcao*5.5+6);
    desenha_mesa (proporcao*1.5, 0, -proporcao*5.5+6);
    desenha_mesa (-proporcao*1.5, 0, -proporcao*4+6);
    desenha_mesa (0, 0, -proporcao*4+6);
    desenha_mesa (proporcao*1.5, 0, -proporcao*4+6);
    desenha_cadeira (-proporcao*1.5, 0, -proporcao*7+8);
    desenha_cadeira (0, 0, -proporcao*7+8);
    desenha_cadeira (proporcao*1.5, 0, -proporcao*7+8);
    desenha_cadeira (-proporcao*1.5, 0, -proporcao*5.5+8);
    desenha_cadeira (0, 0, -proporcao*5.5+8);
    desenha_cadeira (proporcao*1.5, 0, -proporcao*5.5+8);
    desenha_cadeira (-proporcao*1.5, 0, -proporcao*4+8);
    desenha_cadeira (0, 0, -proporcao*4+8);
    desenha_cadeira (proporcao*1.5, 0, -proporcao*4+8);
    desenha_quadro (0, 0.5, -proporcao*7.0+proporcao*0.05);
    //desenha_computador ();
    desenha_bancada (-15, 0, -proporcao*7.0+4);
    desenha_bancada (-15, 0, -4);

    glEndList();
    return model;
}