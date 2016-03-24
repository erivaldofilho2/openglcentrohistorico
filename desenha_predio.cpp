#include "desenho.h"

unsigned int Desenho::desenha_predio() {
	GLUquadricObj *quadric;

	/* inicia a composicao do predio */
	unsigned int predio = glGenLists(1);
	glNewList(predio, GL_COMPILE);

	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	//parede direita2
	glPushMatrix();
	glColor3f( 0.858824, 0.858824, 0.439216);
	glTranslatef (0, 10, 0);
	glScalef (20, 3.0, 0.1);
	glutSolidCube (5.0);
	glPopMatrix();

	glEndList();
	return predio;
}