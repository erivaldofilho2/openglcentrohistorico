/*
 * Modelagem do Antigo Grupo Escolar Ladislau Neto
 */

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "desenho.h"
#include "iluminacao.hpp"

#define PI 3.1415926535897932

unsigned int modelagem; // indentificador de lista de chamada

float proporcao = 5;
Desenho desenhista (proporcao); // coleção de funções que desenha os objetos
bool fullscreenmode = false;
float vetor_x = 0.0, vetor_y = 0.0, vetor_z = -1.0; // vetor direção da câmera
float x = 0.0 * proporcao, y = 1.7 * proporcao, z = 10.0 * proporcao; // posição da câmera
float deltaMove = 0.0;
float lateralMove = 0.0;
float deltaAngle = 0.0;
float verticalMove = 0.0;
float aberturaPorta = 0;
float aberturaPortaLateral = 0;

// Essa função é chamada quando alguma dimensão da janela é alterada
void reajusteJanela (int largura, int altura){
    glViewport (0, 0, largura, altura);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (80.0, largura / (float)altura, 0.1, 600.0);
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
    if (verticalMove) { // vira a camera em torno do eixo vertical
        y += verticalMove;
        verticalMove = 0;
    }

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_BLEND);
    glShadeModel (GL_SMOOTH);
    glDepthMask (GL_TRUE);
    glClearColor (0.32,0.57,0.88,0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Reinicia matriz de transformação

    // Escolha da iluminação
    switch(ModoDeIluminacao)
    {
    case ESPECULAR: defineLuzESPECULAR();
            break;
    case DIFUSA: defineLuzDIFUSA();
            break;
    case AMBIENTE: defineLuzAMBIENTE();
            break;
    }

    // empilha matriz atual (anterior à chamada da função)
    glPushMatrix();
    // define câmera
    gluLookAt (x, y, z, x+vetor_x, y+sin(vetor_y), z+vetor_z, 0.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);

    //// INICIO DESENHO DE OBJETOS
    glCallList(modelagem);
    //// FIM DE DESENHO DE OBJETOS
    
    // desempilha matriz anterior à chamada da função
    glPopMatrix();
    glutSwapBuffers();
}

void especial(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_UP: if (vetor_y <= 1.6) vetor_y += 0.1;
        break;
    case GLUT_KEY_DOWN: if (vetor_y >= -1.6) vetor_y -= 0.1;
        break;
    case GLUT_KEY_LEFT: deltaAngle -= 0.1;
        break;
    case GLUT_KEY_RIGHT: deltaAngle += 0.1;
        break;
    }

    // atualiza direção da câmera
    vetor_x = sin (deltaAngle);
    vetor_z = -cos (deltaAngle);
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y){
    switch (key) {
    case 'w': deltaMove = 3;
        break;
    case 's': deltaMove = -3;
        break;
    case 'a': lateralMove = -3;
        break;
    case 'd': lateralMove = 3;
        break;
    case 'r': verticalMove = 3;
        break;
    case 'f': verticalMove = -3;
        break;
    case 'W': deltaMove = 0.1;
        break;
    case 'S': deltaMove = -0.1;
        break;
    case 'A': lateralMove = -0.1;
        break;
    case 'D': lateralMove = 0.1;
        break;
    case 'R': verticalMove = 0.1;
        break;
    case 'F': verticalMove = -0.1;
        break;
    case 'O':
    case 'o': if (aberturaPorta <= 90 - 3) aberturaPorta += 3;
        modelagem = desenhista.geraModelagem (aberturaPorta, aberturaPortaLateral);
        break;
    case 'P':
    case 'p': if (aberturaPorta >= 3) aberturaPorta -= 3;
        modelagem = desenhista.geraModelagem (aberturaPorta, aberturaPortaLateral);
        break;
    case 'K':
    case 'k': if (aberturaPortaLateral <= 90 - 3) aberturaPortaLateral += 3;
        modelagem = desenhista.geraModelagem (aberturaPorta, aberturaPortaLateral);
        break;
    case 'L':
    case 'l': if (aberturaPortaLateral >= 3) aberturaPortaLateral -= 3;
        modelagem = desenhista.geraModelagem (aberturaPorta, aberturaPortaLateral);
        break;
    case '1': vetor_y = 0; y = 10; verticalMove = 0;
        break;
    case 27: // esc
        fullscreenmode = !fullscreenmode;
        if (fullscreenmode) glutFullScreen();
        else glutReshapeWindow (1024, 800);
        break;
    case '7': ModoDeIluminacao = AMBIENTE;
        LuzAmbEhMax = 0;
        break;
    case '8': ModoDeIluminacao = DIFUSA;
        LuzAmbEhMax = 0;
        break;
    case '9': ModoDeIluminacao = ESPECULAR;
        LuzAmbEhMax = 0;
        break;
    case '0': LuzAmbEhMax = !LuzAmbEhMax;
        break;
    case '+':
        if (ambiente[0] < 0.5) {
            ambiente[0] +=0.01;
            ambiente[1] +=0.01;
            ambiente[2] +=0.01;
        }
        break;
    case '-':
        if (ambiente[0] > -0.5) {
            ambiente[0] -=0.01;
            ambiente[1] -=0.01;
            ambiente[2] -=0.01;
        }
        break;
    }
    glutPostRedisplay();
}

void inicializa() {
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable (GL_TEXTURE_2D);
    glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    //glEnable ( GL_CULL_FACE );
    glEnable (GL_DEPTH_TEST); // Compara profundidade
    modelagem = desenhista.geraModelagem (aberturaPorta, aberturaPortaLateral);
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
    glutReshapeFunc (reajusteJanela);
    glutIdleFunc (exibir);

    glutMainLoop();

    return 0;
}
