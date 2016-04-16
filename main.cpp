/*
 * Modelagem do Antigo Grupo Escolar Ladislau Neto
 */

#include <GL/glut.h>
#include "janela.h"

static Janela janela;

void reajusteJanela (int largura, int altura);
void exibir (void);
void teclasEspeciais (int key, int x, int y);
void teclado (unsigned char key, int x, int y);

void init () {
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable (GL_TEXTURE_2D);
    glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    //glEnable ( GL_CULL_FACE );
    glEnable (GL_DEPTH_TEST); // Compara profundidade
}

int main (int argc,char **argv){
    glutInit (&argc, argv);

    if ( ! glutCreateWindow ("Antigo Grupo Escolar Ladislau Neto, Maceió - AL") ) {
        std::cout << "Erro ao carregar a janela.\n";
        exit(-1);
    }

    init();

    glutKeyboardFunc (teclado);
    glutSpecialFunc (teclasEspeciais);
    glutDisplayFunc (exibir);
    glutReshapeFunc (reajusteJanela);
    glutIdleFunc (exibir);

    glutMainLoop();

    return 0;
}

void reajusteJanela (int largura, int altura) {
    janela.reajusteJanela (largura, altura);
}
void exibir (void) {
    janela.exibir();
}
void teclasEspeciais (int key, int x, int y) {
    janela.teclasEspeciais (key, x, y);
}
void teclado (unsigned char key, int x, int y) {
    janela.teclado (key, x, y);
}
