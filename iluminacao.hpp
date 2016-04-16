
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


GLfloat ratio;

#define AMBIENTE 0
#define DIFUSA 1
#define ESPECULAR 2

float ambiente[3] = {0,0,0};

int ModoDeIluminacao = AMBIENTE;

int LuzAmbEhMax = 0;
// **********************************************************************
//  void DefineLuz(void)
//
//
// **********************************************************************
void defineLuzESPECULAR(void)
{
  // Define cores para um objeto dourado
  GLfloat LuzAmbiente[]   = {0.24725, 0.1995, 0.07} ;
  GLfloat LuzAmbienteMAX[]   = {1,1,1} ;

  GLfloat LuzDifusa[]   = {0.75164, 0.60648, 0.22648f, 0.5 };
  GLfloat LuzEspecular[] = {0.626281, 0.555802, 0.366065, 0.5 };
  //GLfloat LuzEspecular[] = {1,0,0, 1.0f };
  GLfloat PosicaoLuz0[]  = {3.0, 3.0, 0.0, 1.0};
  GLfloat PosicaoLuz1[]  = {-3.0, -3.0, 0.0, 1.0 };
  GLfloat Especularidade[] = {0, 0, 0, 0 };

   // ****************  Fonte de Luz 0

   glEnable ( GL_COLOR_MATERIAL );


   // Habilita o uso de iluminação
  glEnable(GL_LIGHTING);

  // Ativa o uso da luz ambiente
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
  // Define os parametros da Luz número Zero
  if (LuzAmbEhMax)
      glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
  else glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
  glEnable(GL_LIGHT0);

  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentração do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado será o brilho. (Valores válidos: de 0 a 128)
  glMateriali(GL_FRONT,GL_SHININESS,20);

  // ****************  Fonte de Luz 1

  // Ativa o uso da luz ambiente
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
  // Define os parametros da Luz número Zero
  if (LuzAmbEhMax)
      glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
  else glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
  //glEnable(GL_LIGHT1);

  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentração do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado será o brilho. (Valores válidos: de 0 a 128)
  glMateriali(GL_FRONT,GL_SHININESS,11);
//  glMateriali(GL_FRONT,GL_SHININESS,20);

}
// **********************************************************************
//  void DefineLuz(void)
//
//
// **********************************************************************
void defineLuzAMBIENTE(void)
{   
    glDisable(GL_LIGHTING);
    return;
}

// **********************************************************************
//  void DefineLuz(void)
//
//
// **********************************************************************
void defineLuzDIFUSA(void)
{
// Flat shading for speed  
glShadeModel(GL_FLAT);  
// Disable Lighting for performance.  
glDisable(GL_LIGHTING);  
// Não escreve no buffer de cor, apenas no depth  
//glColorMask(0, 0, 0, 0);
// Protege o código anterior a esta função  
glPushAttrib(GL_TEXTURE_BIT |  GL_ENABLE_BIT);  
// Habilita a geração automática de coordenadas de textura do ponto de vista da câmera  
glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);  
glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);  
glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);  
glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);  
// Aplica a transformação destas coordenadas para o espaço da luz  
// glTexGenfv(GL_S, GL_EYE_PLANE, textureTrasnformS);  
// glTexGenfv(GL_T, GL_EYE_PLANE, textureTrasnformT);  
// glTexGenfv(GL_R, GL_EYE_PLANE, textureTrasnformR);  
// glTexGenfv(GL_Q, GL_EYE_PLANE, textureTrasnformQ);  
// Ativa  
glEnable(GL_TEXTURE_GEN_S);  
glEnable(GL_TEXTURE_GEN_T);  
glEnable(GL_TEXTURE_GEN_R);  
glEnable(GL_TEXTURE_GEN_Q);  
  
  //Bind & enable shadow map texture  
  glEnable(GL_TEXTURE_2D); 

  // Define cores para um objeto dourado
  GLfloat LuzAmbiente[]   = {0.24725, 0.1995, 0.07};
  LuzAmbiente[0] += ambiente[0];
  LuzAmbiente[1] += ambiente[1];
  LuzAmbiente[2] += ambiente[2];
  //GLfloat LuzAmbiente[]   = {0,0,0} ;
  GLfloat LuzAmbienteMAX[]   = {1,1,1} ;
  GLfloat LuzDifusa[]   = {0.75164, 0.60648, 0.22648, 1 };
  GLfloat LuzEspecular[] = {0,0,0, 0};
  GLfloat PosicaoLuz0[]  = {3.0, 1003.0, 0.0, 1.0 };
  //GLfloat PosicaoLuz1[]  = {-3.0, 103.0, 0.0, 1.0 };
  //GLfloat Especularidade[] = {0,0,0,1 };

   // ****************  Fonte de Luz 0
  glEnable ( GL_COLOR_MATERIAL );

   // Habilita o uso de iluminação
  glEnable(GL_LIGHTING);

  // Ativa o uso da luz ambiente
  if (LuzAmbEhMax)
      glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
  else glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
  // Define os parametros da Luz número Zero
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
  glEnable(GL_LIGHT0);

  // Ativa o "Color Tracking"
  //glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  //glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentração do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado será o brilho. (Valores válidos: de 0 a 128)
  //glMateriali(GL_FRONT,GL_SHININESS, 30);

/*
  // ****************  Fonte de Luz 1

  // Ativa o uso da luz ambiente
  if (LuzAmbEhMax)
      glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
  else glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
  // Define os parametros da Luz número Zero
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
  //glEnable(GL_LIGHT1);

  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentração do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado será o brilho. (Valores válidos: de 0 a 128)
  //glMateriali(GL_FRONT,GL_SHININESS, 0);
*/
}