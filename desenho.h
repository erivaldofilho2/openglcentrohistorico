#ifndef DESENHISTA_H
#define DESENHISTA_H

#include <GL/glut.h>
#include <cmath>

/*
 * Classe com funções que desenham objetos
 */
class Desenho
{
public:
    Desenho (float _proporcao = 3) {proporcao = _proporcao;}
    unsigned int desenha_predio (float x, float y, float z);
    unsigned int desenha_mesa (float x, float y, float z);
    unsigned int desenha_cadeira (float x, float y, float z);
    // unsigned int desenha_quadro_branco (float x, float y, float z);

private:
    unsigned int desenha_janela (float x, float y, float z);
    float proporcao;
};


 /*
  * Classe para aulixiar uso do OpenGL na implementação da classe Desenho
  */
class Desenha_gl
{
private:
    float x, y, z, proporcao;
    float desloc_x, desloc_y, desloc_z;
    float escala_x, escala_y, escala_z;
    float angulo, vetor_x, vetor_y, vetor_z;
public:
    Desenha_gl (float pos_x, float pos_y, float pos_z, float _proporcao){
        x = pos_x; y = pos_y; z = pos_z; proporcao = _proporcao;
    }
    ~Desenha_gl(){;}
    void define_deslocamento (float _desloc_x, float _desloc_y, float _desloc_z) {
        desloc_x = x + proporcao * _desloc_x;
        desloc_y = y + proporcao * _desloc_y;
        desloc_z = z + proporcao * _desloc_z;
    }
    void define_escala (float _escala_x, float _escala_y, float _escala_z) {
        escala_x = _escala_x;
        escala_y = _escala_y;
        escala_z = _escala_z;
    }
    void define_rotacao (float _angulo, float vx, float vy, float vz) {
        angulo = _angulo;
        vetor_x = vx;
        vetor_y = vy;
        vetor_z = vz;
    }
    void desenha_cubo() {
        glPushMatrix();
        glTranslatef (desloc_x, desloc_y, desloc_z);
        glRotatef (angulo, vetor_x, vetor_y, vetor_z);
        glScalef (escala_x, escala_y, escala_z);
        glutSolidCube (proporcao);
        glPopMatrix();
    }
};

#endif