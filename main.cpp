#include <cmath>
#include <GL/glut.h>
#include <iostream>

#define PI 3.1415926535897932

int LARGURA = 1024;
int ALTURA = 800;

// vetor representando direção da câmera
float vetor_x = 0.0, vetor_z = -1.0;

// posição da câmera
float x = 0.0, z = 30.0, y = 10.0;

float deltaMove = 0.0;
float lateralMove = 0.0;
float deltaAngle = 0.0;
int xOrigin = -1;

// Essa função é chamada quando alguma dimensão da janela é alterada
void remodelar (int largura, int altura){
    LARGURA = largura;
    ALTURA = altura;
    glViewport (0, 0, largura, altura);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (80.0, largura / (float)altura, 0.1, 200.0);
    glMatrixMode (GL_MODELVIEW);
}

// calcula x e z para ir: frente e traz
void computePos () {
    x += deltaMove * vetor_x * 0.1;
    z += deltaMove * vetor_z * 0.1;
    deltaMove = 0;
}

// calcula x e z para ir: esquerda e direita
void lateralPos () {
    x += lateralMove * (sin(deltaAngle + PI / 2)) * 0.1;
    z += lateralMove * (-cos(deltaAngle + PI / 2)) * 0.1;
    lateralMove = 0;
}

void fazer_boneco_de_neve() {
    // Desenha chão
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    float bp = 8;
    // Desenha boneco de neve
    glColor3f(1.0f, 1.0f, 1.0f);
    // Draw Body
    glTranslatef(0.0f ,0.75f*bp, 0.0f);
    glutSolidSphere(0.75*bp,20,20);
    // Draw Head
    glTranslatef(0.0f, 1.0f*bp, 0.0f);
    glutSolidSphere(0.25*bp,20,20);
    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f*bp, 0.10f*bp, 0.18f*bp);
    glutSolidSphere(0.05*bp,10,10);
    glTranslatef(-0.1f*bp, 0.0f, 0.0f);
    glutSolidSphere(0.05*bp,10,10);
    glPopMatrix();
    // Draw Nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glRotatef(0.0f,1.0f*bp, 0.0f, 0.0f);
    glutSolidCone(0.08*bp,0.5f*bp,10,2);
}

void exibir(void){
    if (deltaMove)
        computePos(); // mover camera para frente e traz
    if (lateralMove)
        lateralPos(); // mover camera para esquerda e direita

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
    gluLookAt (x, y, z, x+vetor_x, y, z+vetor_z, 0.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);

    fazer_boneco_de_neve();
    
    // desempilha matriz anterior à chamada da função
    glPopMatrix();
    glutSwapBuffers();
}

void especial(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_UP:
        //if (y > 8)
            y -= 0.1;
        break;
    case GLUT_KEY_DOWN:
        //if (y < 12)
            y += 0.1;
        break;
    case GLUT_KEY_LEFT:
        deltaAngle -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        deltaAngle += 0.1;
        break;
    }

    // update camera's direction
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
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void inicializa() {
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_TEXTURE_2D);
}

//TODO corrigir o aspecto do predio assim que o projeto é executado.
//ao movimentar a camera as cores e texturas voltam ao normal
int main (int argc,char **argv){
    glutInitWindowPosition (0,0);
    glutInitWindowSize (LARGURA, ALTURA);
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    if ( ! glutCreateWindow ("Antiga escola das órfãs, Maceió - AL") ) {
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
