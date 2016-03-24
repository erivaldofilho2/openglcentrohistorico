#include "desenho.h"

unsigned int Desenho::desenha_predio() {
	float cor_parede[3] = {0xa3/256.0, 0x90/256.0, 0x7f/256.0};
	float frontal_comprimento = 20.0,
	      frontal_altura = 7.0,
	      parede_largura = 0.1;

	/* inicia a composicao do predio */
	unsigned int predio = glGenLists(1);
	glNewList(predio, GL_COMPILE);

	// Desenha chão
    glColor3f(0.0, 0.2, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(-100.0, 0.0, -100.0);
        glVertex3f(-100.0, 0.0,  100.0);
        glVertex3f( 100.0, 0.0,  100.0);
        glVertex3f( 100.0, 0.0, -100.0);
    glEnd();

	//parede frontal
	glPushMatrix();
	glColor3f( cor_parede[0], cor_parede[1], cor_parede[2] );
	glTranslatef (0, 10, 0);
	glScalef (frontal_comprimento, frontal_altura, parede_largura);
	glutSolidCube (5.0);
	glPopMatrix();

	glEndList();
	return predio;
}