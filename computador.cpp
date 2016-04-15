#include "desenho.h"

unsigned int Desenho::desenha_computador (float pos_x, float pos_y, float pos_z) {
    float cor_computador[3] = {0, 0, 0.1};
    float cor_monitor[3] = {0.6, 0.6, 0.6};
    float base_largura = 0.1;
    float base_altura = 0.01;
    float base_profundidade = 0.2;


    Desenha_gl gl (pos_x, pos_y, pos_z, proporcao);

    /* inicia a composicao do predio */
    // unsigned int computador = glGenLists (1);
    // glNewList (computador, GL_COMPILE);

    // computador
    glColor3f ( cor_computador[0], cor_computador[1], cor_computador[2] );
    //base
    gl.define_deslocamento (base_profundidade, base_altura, base_largura);
    gl.define_escala (base_profundidade, base_altura, base_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    //suporte
    gl.define_deslocamento (base_profundidade, base_altura+0.04, base_largura);
    gl.define_escala (0.02, 0.1, 0.02);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    //Monitor
    glColor3f ( cor_monitor[0], cor_monitor[1], cor_monitor[2] );
    gl.define_deslocamento (base_profundidade, base_altura+0.16, base_largura);
    gl.define_escala (0.2, 0.15, 0.02);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();


    // glEndList();
    return 0;
}