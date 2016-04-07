#include "desenho.h"

unsigned int Desenho::desenha_predio (float pos_x, float pos_y, float pos_z, float aberturaPorta = 0) {
    Desenha_gl gl (pos_x, pos_y, pos_z, proporcao);

    // variáveis auxiliares de posição
    float x, y, z;

    float cor_parede[3] = {0xa3/256.0, 0x90/256.0, 0x7f/256.0};
    float cor_portao[3] = {0x23/256.0, 0x36/256.0, 0x4f/256.0};
    float cor_telhado[3] = {0x61/256.0, 0x2c/256.0, 0x1c/256.0};
    
    float parede_largura = 0.1;
    float frontal_comprimento = 15.0, frontal_altura = 6.5;
    float lateral_comprimento = 7.0, lateral_altura = 5.0;
    float entrada_garagem_altura = 2.7;
    float entrada_garagem_largura = 4;
    float portao_garagem_altura = 2.2;
    float portao_garagem_lagura = 1;
    float portao_garagem_espessura = 0.05;

    /* inicia a composicao do predio */
    unsigned int predio = glGenLists (1);
    glNewList (predio, GL_COMPILE);

    // Desenha chão
    glColor3f (0.0, 0.29, 0.0);
    glBegin (GL_QUADS);
        glVertex3f (-10000, 0, -10000);
        glVertex3f (-10000, 0,  10000);
        glVertex3f ( 10000, 0,  10000);
        glVertex3f ( 10000, 0, -10000);
    glEnd();
    // Desenha chão no interior do prédio
    glColor3f (0.2, 0.2, 0.2);
    glBegin (GL_QUADS);
        glVertex3f (-proporcao * frontal_comprimento/2, 0.1, -0);
        glVertex3f (-proporcao * frontal_comprimento/2, 0.1, -proporcao * lateral_comprimento);
        glVertex3f ( proporcao * frontal_comprimento/2, 0.1, -proporcao * lateral_comprimento);
        glVertex3f ( proporcao * frontal_comprimento/2, 0., -0);
    glEnd();
    
    // parede frontal
    glColor3f ( cor_parede[0], cor_parede[1], cor_parede[2] );
    gl.define_deslocamento (0, frontal_altura / 2, 0);
    gl.define_escala (frontal_comprimento + parede_largura, frontal_altura, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    // desenha janelas
    desenha_janela (0, proporcao * 1.5, 0);
    desenha_janela (-proporcao * (1.4), proporcao * 1.5, 0);
    desenha_janela ( proporcao * (1.4), proporcao * 1.5, 0);
    desenha_janela (-proporcao * (frontal_comprimento/4 - 0.5), proporcao * 1.5, 0);
    desenha_janela ( proporcao * (frontal_comprimento/4 - 0.5), proporcao * 1.5, 0);
    desenha_janela (-proporcao * (frontal_comprimento/2.6), proporcao * 1.5, 0);
    desenha_janela ( proporcao * (frontal_comprimento/2.6), proporcao * 1.5, 0);
    glColor3f ( cor_parede[0], cor_parede[1], cor_parede[2] );

    // parede de fundo
    gl.define_deslocamento (0, lateral_altura / 2, -lateral_comprimento);
    gl.define_escala (frontal_comprimento, lateral_altura, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    
    // parede lateral esquerda
    gl.define_deslocamento (-frontal_comprimento / 2, lateral_altura / 2, -lateral_comprimento / 2);
    gl.define_escala (lateral_comprimento, lateral_altura, parede_largura);
    gl.define_rotacao (90, 0, 1, 0);
    gl.desenha_cubo();

    // parede lateral direita
    gl.define_deslocamento (frontal_comprimento / 2, lateral_altura / 2, -lateral_comprimento / 2);
    gl.define_escala (lateral_comprimento, lateral_altura, parede_largura);
    gl.define_rotacao (90, 0, 1, 0);
    gl.desenha_cubo();

    // parede lateral da garagem
    x = frontal_comprimento / 2 + entrada_garagem_largura;
    gl.define_deslocamento (x, entrada_garagem_altura / 2, -lateral_comprimento / 2);
    gl.define_escala (lateral_comprimento, entrada_garagem_altura, parede_largura);
    gl.define_rotacao (90, 0, 1, 0);
    gl.desenha_cubo();
    // contorno sobre o muro
    glColor3f ( cor_parede[0]-0.1, cor_parede[1]-0.1, cor_parede[2]-0.1 );
    //x = frontal_comprimento / 2 + entrada_garagem_largura; // x já calculado
    gl.define_deslocamento (x, entrada_garagem_altura + parede_largura / 4, -lateral_comprimento / 2);
    gl.define_escala (lateral_comprimento, parede_largura / 2, parede_largura);
    gl.define_rotacao (90, 0, 1, 0);
    gl.desenha_cubo();
    glColor3f ( cor_parede[0], cor_parede[1], cor_parede[2] );

    // parede do fundo da garagem
    x = frontal_comprimento / 2 + entrada_garagem_largura / 2;
    gl.define_deslocamento (x, entrada_garagem_altura / 2, -lateral_comprimento);
    gl.define_escala (entrada_garagem_largura, entrada_garagem_altura, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    // contorno sobre o muro
    glColor3f ( cor_parede[0]-0.1, cor_parede[1]-0.1, cor_parede[2]-0.1 );
    //x = frontal_comprimento / 2 + entrada_garagem_largura / 2; // x já calculado
    gl.define_deslocamento (x, entrada_garagem_altura + parede_largura / 4, -lateral_comprimento);
    gl.define_escala (entrada_garagem_largura, parede_largura / 2, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    glColor3f ( cor_parede[0], cor_parede[1], cor_parede[2] );
    
    // entrada da garagem
    /// lado esquerdo
    x = (frontal_comprimento + entrada_garagem_largura / 2 + 0.4 - portao_garagem_lagura) / 2;
    gl.define_deslocamento (x, entrada_garagem_altura / 2, 0);
    x = entrada_garagem_largura / 2 + 0.4 - portao_garagem_lagura;
    gl.define_escala (x, entrada_garagem_altura, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    ///lado direito
    x = (frontal_comprimento + 3 * entrada_garagem_largura / 2 + 0.4 + portao_garagem_lagura) / 2;
    gl.define_deslocamento (x, entrada_garagem_altura / 2, 0);
    x = entrada_garagem_largura / 2 - 0.4 - portao_garagem_lagura;
    gl.define_escala (x, entrada_garagem_altura, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    /// lado superior
    x = (frontal_comprimento + entrada_garagem_largura) / 2 + 0.4;
    gl.define_deslocamento (x, (entrada_garagem_altura + portao_garagem_altura) / 2, 0);
    y = entrada_garagem_altura - portao_garagem_altura;
    gl.define_escala (portao_garagem_lagura * 2, y, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    // contorno sobre o muro
    glColor3f ( cor_parede[0]-0.1, cor_parede[1]-0.1, cor_parede[2]-0.1 );
    x = (frontal_comprimento + entrada_garagem_largura) / 2;
    gl.define_deslocamento (x, entrada_garagem_altura + parede_largura / 4, 0);
    gl.define_escala (entrada_garagem_largura, parede_largura / 2, parede_largura);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    glColor3f ( cor_parede[0], cor_parede[1], cor_parede[2] );

    // portão da garagem
    /// portão 1
    glColor3f ( cor_portao[0], cor_portao[1], cor_portao[2] );
    x = frontal_comprimento / 2 + entrada_garagem_largura / 2 + 0.4;
    x += -1 + portao_garagem_lagura * cos (aberturaPorta * PI / 180) / 2;
    gl.define_deslocamento ( x, portao_garagem_altura / 2, -sin (aberturaPorta * PI / 180) / 2 );
    gl.define_escala (portao_garagem_lagura, portao_garagem_altura, portao_garagem_espessura);
    gl.define_rotacao ( aberturaPorta, 0, 1, 0);
    gl.desenha_cubo();
    /// portão 2
    x = frontal_comprimento / 2 + entrada_garagem_largura / 2 + 0.4;
    x += 1 - portao_garagem_lagura * cos (aberturaPorta * PI / 180) / 2;
    gl.define_deslocamento ( x, portao_garagem_altura / 2, -sin (aberturaPorta * PI / 180) / 2 );
    gl.define_escala (portao_garagem_lagura, portao_garagem_altura, portao_garagem_espessura);
    gl.define_rotacao (-aberturaPorta, 0, 1, 0);
    gl.desenha_cubo();

    //// pilares frontais
    // pilar lateral esquerda
    glColor3f ( cor_parede[0]+0.1, cor_parede[1]+0.1, cor_parede[2]+0.1 );
    gl.define_deslocamento (-frontal_comprimento / 2 + 0.15, frontal_altura / 2, 0.05);
    gl.define_escala (0.3, frontal_altura, 0.05);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // pilar lateral direita
    gl.define_deslocamento (frontal_comprimento / 2 - 0.15, frontal_altura / 2, 0.05);
    gl.define_escala (0.3, frontal_altura, 0.05);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // segundo pilar lateral esquerdo
    gl.define_deslocamento (-frontal_comprimento / 3.5 + 0.15, frontal_altura / 2, 0.05);
    gl.define_escala (0.3, frontal_altura, 0.05);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // segundo pilar lateral direita
    gl.define_deslocamento (frontal_comprimento / 3.5 - 0.15, frontal_altura / 2, 0.05);
    gl.define_escala (0.3, frontal_altura, 0.05);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // pilar do meio lateral esquerdo
    gl.define_deslocamento (-frontal_comprimento / 6 + 0.15, frontal_altura / 2 -0.25, 0.05);
    gl.define_escala (0.3, frontal_altura-2.5, 0.05);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // pilar do meio lateral direita
    gl.define_deslocamento (frontal_comprimento / 6 - 0.15, frontal_altura / 2 -0.25, 0.05);
    gl.define_escala (0.3, frontal_altura-2.5, 0.05);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // viga inferior
    gl.define_deslocamento (0, 1, 0.05);
    gl.define_escala (frontal_comprimento, 0.3, 0.05);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // viga superior (esta é detalhada)
    glColor3f ( cor_parede[0]+0.16, cor_parede[1]+0.16, cor_parede[2]+0.16 );
    gl.define_deslocamento (0, frontal_altura - 1.3, 0.12);
    gl.define_escala (frontal_comprimento, 0.1, 0.09);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    glColor3f ( cor_parede[0]+0.13, cor_parede[1]+0.13, cor_parede[2]+0.13 );
    gl.define_deslocamento (0, frontal_altura - 1.4, 0.09);
    gl.define_escala (frontal_comprimento, 0.1, 0.07);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();
    glColor3f ( cor_parede[0]+0.1, cor_parede[1]+0.1, cor_parede[2]+0.1 );
    gl.define_deslocamento (0, frontal_altura - 1.5, 0.06);
    gl.define_escala (frontal_comprimento, 0.1, 0.06);
    gl.define_rotacao (0, 0, 0, 0);
    gl.desenha_cubo();

    // telhado
    glColor3f ( cor_telhado[0], cor_telhado[1], cor_telhado[2] );
    gl.define_deslocamento (0, lateral_altura -0.3 + sin(-60)*lateral_comprimento/4, -lateral_comprimento/4);
    gl.define_escala (frontal_comprimento, 0.05+lateral_comprimento/(2*cos(-60)), 0.05);
    gl.define_rotacao (-80, 1, 0, 0);
    gl.desenha_cubo();
    gl.define_deslocamento (0, lateral_altura -0.3 + sin(-60)*lateral_comprimento/4, -lateral_comprimento*3/4);
    gl.define_escala (frontal_comprimento, 0.05+lateral_comprimento/(2*cos(-60)), 0.05);
    gl.define_rotacao (80, 1, 0, 0);
    gl.desenha_cubo();

    // Detalhe sobre os muros laterais 
    // muro esquerdo
    glBegin (GL_POLYGON);
        glColor3f ( cor_parede[0], cor_parede[1], cor_parede[2] );
        x = -proporcao * frontal_comprimento / 2 - proporcao * parede_largura / 2;
        y = proporcao * lateral_altura;
        z = -proporcao * parede_largura / 2;
        glVertex3f (x, y, z);
        y = proporcao * frontal_altura;
        glVertex3f (x, y, z);
        z -= proporcao * 0.5;
        y -= proporcao * 0.8;
        glVertex3f (x, y, z);
        z -= proporcao * 0.4;
        y -= proporcao * 0.1;
        glVertex3f (x, y, z);
        y = proporcao * lateral_altura;
        glVertex3f (x, y, z);
    glEnd();
    glBegin (GL_POLYGON);
        //z -= proporcao * 0.75;
        glVertex3f (x, y, z);
        y = proporcao * (frontal_altura - 0.9);
        glVertex3f (x, y, z);
        z -= proporcao * 0.3;
        glVertex3f (x, y, z);
        y = proporcao * lateral_altura;
        glVertex3f (x, y, z);
    glEnd();
    glBegin (GL_POLYGON);
        glVertex3f (x, y, z);
        y = proporcao * (frontal_altura - 0.9);
        glVertex3f (x, y, z);
        z -= proporcao * 2;
        y += proporcao * 0.7;
        glVertex3f (x, y, z);
        y = proporcao * lateral_altura;
        glVertex3f (x, y, z);
    glEnd();
    glBegin (GL_POLYGON);
        glVertex3f (x, y, z);
        y = proporcao * (frontal_altura - 0.2);
        glVertex3f (x, y, z);
        z = -proporcao * lateral_comprimento;
        y = proporcao * lateral_altura;
        glVertex3f (x, y, z);
    glEnd();
    // Detalhe sobre os muros laterais 
    // muro direito
    glBegin (GL_POLYGON);
        glColor3f ( cor_parede[0], cor_parede[1], cor_parede[2] );
        x = proporcao * frontal_comprimento / 2 + proporcao * parede_largura / 2;
        y = proporcao * lateral_altura;
        z = -proporcao * parede_largura / 2;
        glVertex3f (x, y, z);
        y = proporcao * frontal_altura;
        glVertex3f (x, y, z);
        z -= proporcao * 0.5;
        y -= proporcao * 0.8;
        glVertex3f (x, y, z);
        z -= proporcao * 0.4;
        y -= proporcao * 0.1;
        glVertex3f (x, y, z);
        y = proporcao * lateral_altura;
        glVertex3f (x, y, z);
    glEnd();
    glBegin (GL_POLYGON);
        //z -= proporcao * 0.75;
        glVertex3f (x, y, z);
        y = proporcao * (frontal_altura - 0.9);
        glVertex3f (x, y, z);
        z -= proporcao * 0.3;
        glVertex3f (x, y, z);
        y = proporcao * lateral_altura;
        glVertex3f (x, y, z);
    glEnd();
    glBegin (GL_POLYGON);
        glVertex3f (x, y, z);
        y = proporcao * (frontal_altura - 0.9);
        glVertex3f (x, y, z);
        z -= proporcao * 2;
        y += proporcao * 0.7;
        glVertex3f (x, y, z);
        y = proporcao * lateral_altura;
        glVertex3f (x, y, z);
    glEnd();
    glBegin (GL_POLYGON);
        glVertex3f (x, y, z);
        y = proporcao * (frontal_altura - 0.2);
        glVertex3f (x, y, z);
        z = -proporcao * lateral_comprimento;
        y = proporcao * lateral_altura;
        glVertex3f (x, y, z);
    glEnd();

    glEndList();
    return predio;
}