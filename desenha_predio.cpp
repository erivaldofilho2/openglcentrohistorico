#include "desenho.h"

unsigned int Desenho::desenha_predio(float pos_x, float pos_y, float pos_z) {
    float cor_parede[3] = {0xa3/256.0, 0x90/256.0, 0x7f/256.0};
    float parede_largura = 0.1;
    float frontal_comprimento = 20.0, frontal_altura = 5.0;
    float lateral_comprimento = 7.0, lateral_altura = 3.0;
    float desloc_x, desloc_y, desloc_z;
    float proporcao = 2;

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
    glPushMatrix();
    desloc_x = pos_x + 0;
    desloc_y = pos_y + proporcao * frontal_altura / 2.0;
    desloc_z = pos_z + 0;
    glTranslatef (desloc_x, desloc_y, desloc_z);
    glScalef (frontal_comprimento, frontal_altura, parede_largura);
    glutSolidCube (proporcao);
    glPopMatrix();

    // parede de fundo
    glPushMatrix();
    desloc_x = pos_x + 0;
    desloc_y = pos_y + proporcao * lateral_altura / 2.0;
    desloc_z = pos_z - proporcao * lateral_comprimento;
    glTranslatef (desloc_x, desloc_y, desloc_z);
    glScalef (frontal_comprimento, lateral_altura, parede_largura);
    glutSolidCube (proporcao);
    glPopMatrix();
    
    // parede lateral esquerda
    glPushMatrix();
    desloc_x = pos_x - proporcao * frontal_comprimento / 2.0;
    desloc_y = pos_y + proporcao * lateral_altura / 2.0;
    desloc_z = pos_z - proporcao * lateral_comprimento / 2.0;
    glTranslatef (desloc_x, desloc_y, desloc_z);
    glRotatef (90, 0, 1, 0);
    glScalef (lateral_comprimento, lateral_altura, parede_largura);
    glutSolidCube (proporcao);
    glPopMatrix();

    // parede lateral direita
    glPushMatrix();
    desloc_x = pos_x + proporcao * frontal_comprimento / 2.0;
    desloc_y = pos_y + proporcao * lateral_altura / 2.0;
    desloc_z = pos_z - proporcao * lateral_comprimento / 2.0;
    glTranslatef (desloc_x, desloc_y, desloc_z);
    glRotatef (90, 0, 1, 0);
    glScalef (lateral_comprimento, lateral_altura, parede_largura);
    glutSolidCube (proporcao);
    glPopMatrix();

    glEndList();
    return predio;
}