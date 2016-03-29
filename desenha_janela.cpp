#include "desenho.h"

unsigned int Desenho::desenha_janela (float pos_x, float pos_y, float pos_z) {
    float cor_janela[3] = {0x23/256.0, 0x36/256.0, 0x4f/256.0};
    float janela_largura = 0.05;
    float janela_comprimento = 1.0;
    float janela_altura = 3.0;
    float desloc_x, desloc_y, desloc_z;
    float proporcao = 2;

    /* inicia a composicao da janela */
    unsigned int janela = glGenLists (1);
    glNewList (janela, GL_COMPILE);

    // parede frontal
    glColor3f ( cor_janela[0], cor_janela[1], cor_janela[2] );
    glPushMatrix();
    desloc_x = pos_x + 0;
    desloc_y = pos_y + proporcao * janela_altura / 2.0;
    desloc_z = pos_z + 0;
    glTranslatef (desloc_x, desloc_y, desloc_z);
    glScalef (janela_comprimento, janela_altura, janela_largura);
    glutSolidCube (proporcao);
    glPopMatrix();

    glEndList();
    return janela;
}