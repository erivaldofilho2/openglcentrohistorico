/*
 * Modelagem do Antigo Grupo Escolar Ladislau Neto
 */

#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include "desenho.h"

#define PI 3.1415926535897932

Desenho desenhista; // coleção de funções que desenha os objetos
//// Início de indentificadores de lista de chamadas
unsigned int predio;
unsigned int janela;
//// Fim de indentificadores de lista de chamadas

float vetor_x = 0.0, vetor_y = 0.0, vetor_z = -1.0; // vetor direção da câmera
float x = 0.0, y = 2.0, z = 30.0; // posição da câmera
float deltaMove = 0.0;
float lateralMove = 0.0;
float deltaAngle = 0.0;
float verticalMove = 0.0;

// Essa função é chamada quando alguma dimensão da janela é alterada
void remodelar (int largura, int altura){
    glViewport (0, 0, largura, altura);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (80.0, largura / (float)altura, 0.1, 600.0);
    glMatrixMode (GL_MODELVIEW);
}


// Referência: http://www.inf.pucrs.br/~manssour/OpenGL/Iluminacao.html
//iluminacao
void iluminacao_externa(void)
{
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};    // "cor" 
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
    GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
    GLint especMaterial = 60;

    // Especifica que a cor de fundo da janela será preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Define a refletância do material 
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);  
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
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
    if (verticalMove) { // move camera no eixo vertical
        y += verticalMove;
        verticalMove = 0;
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
    gluLookAt (x, y, z, x+vetor_x, y+sin(vetor_y), z+vetor_z, 0.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);

    //// INICIO DESENHO DE OBJETOS
    glCallList(predio);
    glCallList(janela);
    //// FIM DE DESENHO DE OBJETOS
    
    // desempilha matriz anterior à chamada da função
    glPopMatrix();
    glutSwapBuffers();
}

void especial(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_UP:
        if (vetor_y <= 1.6)
            vetor_y += 0.1;
        break;
    case GLUT_KEY_DOWN:
        if (vetor_y >= -1.6)
            vetor_y -= 0.1;
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
        deltaMove = 3;
        break;
    case 's':
        deltaMove = -3;
        break;
    case 'a':
        lateralMove = -3;
        break;
    case 'd':
        lateralMove = 3;
        break;
    case 'r':
        verticalMove = 3;
        break;
    case 'f':
        verticalMove = -3;
        break;
    case 'W':
        deltaMove = 0.1;
        break;
    case 'S':
        deltaMove = -0.1;
        break;
    case 'A':
        lateralMove = -0.1;
        break;
    case 'D':
        lateralMove = 0.1;
        break;
    case 'R':
        verticalMove = 0.1;
        break;
    case 'F':
        verticalMove = -0.1;
        break;
    case '1':
        vetor_y = 0;
        y = 10;
        verticalMove = 0;
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
    /* 
     * @func glEnable (GL_DEPTH_TEST)
     * Antes de cada pixel ser desenhado é feita uma comparação com
     * o valor de profundidade já armazenado
     */
    glEnable (GL_DEPTH_TEST);
    predio = desenhista.desenha_predio (0, 0, 0);
    janela = desenhista.desenha_janela (0, 3, .1);
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
    //iluminacao_externa();

    glutMainLoop();

    return 0;
}
