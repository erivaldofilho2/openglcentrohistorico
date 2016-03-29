#ifndef DESENHISTA_H
#define DESENHISTA_H

#include <GL/glut.h>

class Desenho {
public:
    unsigned int desenha_predio (float, float, float);
    unsigned int desenha_janela (float, float, float);
};

#endif