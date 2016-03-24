#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include "desenho.h"

#define PI 3.1415926535897932

Desenho desenhista; // coleção de funções que desenha os objetos
//// Início de indentificadores de lista de chamadas
unsigned int predio;
unsigned int cadeiras;
//// Fim de indentificadores de lista de chamadas

float vetor_x = 0.0, vetor_y = 10.0, vetor_z = -1.0; // vetor direção da câmera
float x = 0.0, y = 0.0, z = 100.0; // posição da câmera
float deltaMove = 0.0;
float lateralMove = 0.0;
float deltaAngle = 0.0;

// Essa função é chamada quando alguma dimensão da janela é alterada
void remodelar (int largura, int altura){
    glViewport (0, 0, largura, altura);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (80.0, largura / (float)altura, 0.1, 200.0);
    glMatrixMode (GL_MODELVIEW);
}

void exibir(void){
    if (deltaMove) { // mover camera para frente e traz
        x += deltaMove * vetor_x;
        z += deltaMove * vetor_z;
        deltaMove = 0;
    }
    if (lateralMove) { // mover camera para esquerda e direita
        x += lateralMove * (sin(deltaAngle + PI / 2));;
        z += lateralMove * (-cos(deltaAngle + PI / 2));
        lateralMove = 0;
    }

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_BLEND);
    glShadeModel (GL_SMOOTH);
    glDepthMask (GL_TRUE);
    glClearColor (0.5,0.5,0.5,0.5);
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Reinicia matriz de transformação

    // empilha matriz atual (anterior à chamada da função)
    glPushMatrix();
    // define câmera
    gluLookAt (x, 10, z, x+vetor_x, vetor_y, z+vetor_z, 0.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);

    //// INICIO DESENHO DE OBJETOS
    glCallList(predio);
    //// FIM DE DESENHO DE OBJETOS
    
    // desempilha matriz anterior à chamada da função
    glPopMatrix();
    glutSwapBuffers();
}

void especial(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_UP:
        if (vetor_y < 12)
            vetor_y += 0.2;
        break;
    case GLUT_KEY_DOWN:
        if (vetor_y > 8)
            vetor_y -= 0.2;
        break;
    case GLUT_KEY_LEFT:
        deltaAngle -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        deltaAngle += 0.1;
        break;
    }

    // atualiza direção da câmera
    vetor_x = sin (deltaAngle);
    vetor_z = -cos (deltaAngle);
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y){
    switch (key) {
    case 'w':
        deltaMove = 10;
        break;
    case 's':
        deltaMove = -10;
        break;
    case 'a':
        lateralMove = -10;
        break;
    case 'd':
        lateralMove = 10;
        break;
    case '1':
        vetor_y = 10;
        break;
    case 27: // esc
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void inicializa() {
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_TEXTURE_2D);
    predio = desenhista.desenha_predio();
}

int main (int argc,char **argv){
    glutInitWindowPosition (0,0);
    glutInitWindowSize (1024, 800);
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    if ( ! glutCreateWindow ("Antigo Grupo Escolar Ladislau Neto, Maceió - AL") ) {
        std::cout<< "Erro ao carregar a janela.\n";
        exit(-1);
    }

    inicializa();

    glutKeyboardFunc (teclado);
    glutSpecialFunc (especial);
    glutDisplayFunc (exibir);
    glutReshapeFunc (remodelar);
    glutIdleFunc (exibir);

    glutMainLoop();

    return 0;
}
