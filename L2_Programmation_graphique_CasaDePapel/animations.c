/*!\file animations.c
 */

#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <GL4D/gl4dg.h>
#include <SDL_image.h>

/*!\brief identifiant de la géométrie QUAD GL4Dummies */
static GLuint _quadId = 0;
static void loadTexture(GLuint id, const char * filename);


static void loadTexture(GLuint id, const char * filename) {
  SDL_Surface * t;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  if( (t = IMG_Load(filename)) != NULL ) {
#ifdef __APPLE__
    int mode = t->format->BytesPerPixel == 4 ? GL_BGRA : GL_BGR;
#else
    int mode = t->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
#endif       
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0, mode, GL_UNSIGNED_BYTE, t->pixels);
    SDL_FreeSurface(t);
  } else {
    fprintf(stderr, "can't open file %s : %s\n", filename, SDL_GetError());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  }
}


void cheddarfondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[3], pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(3, tex);
    for(i = 0; i < 3; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    loadTexture(tex[2], "picture/fondui.jpg");
    pId = gl4duCreateProgram("<vs>shaders/basici.vs", "<fs>shaders/mixi.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if(tex[0]) {
      glDeleteTextures(3, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, tex[2]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    glUniform1i(glGetUniformLocation(pId, "tex2"), 2);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}


void transition_01(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}


void animation_01(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45.0, 45.0, 0, 0}, r2[] = {40, 40, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/chose.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r2[3] += 0.001;
    r2[2] += 0.001;
    r2[0] -= 0.01;
    r2[1] -= 0.01;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_02(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {0.0, 0.0, 0.8, 0.3}, r2[] = {0, 0, 1, 1}, r = 9.0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/4.png");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    //r1[0] += 0.01;
    r1[1] -= 0.01;
   //r -= 0.02;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_03(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {60.0, 60.0, 0, 0}, r2[] = {47, 47, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/arc.png");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] -= 0.1;
    r1[1] -= 0.1;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_04(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {50.0, 50.0, 0, 0}, r2[] = {50, 50, 0, 0}, r = 0;
  
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/3.png");
    s1 = gl4dpInitScreen();
    //gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] += 0.1;
    r1[1] += 0.1;
   //r *= 0.02;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_05(int state) {
  /* INITIALISEZ VOS VARIABLES */
  static GLuint tId = 0, pId;
  static const GLubyte t[16] = {0,  0,  0, 0, /* noir */
				 -1, -1,  -1, 1, /* blanc  */
				 -1,  -1, -1, 1, /* blanc  */
				0, 0,  0, 0  /* noir */ };
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    glGenTextures(1, &tId);
    glBindTexture(GL_TEXTURE_2D, tId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, t);
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/basic.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if(tId) {
      glDeleteTextures(1, &tId);
      tId = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tId);
    glUniform1i(glGetUniformLocation(pId, "myTexture"), 0);
    gl4dgDraw(_quadId);
    return;
  }
}


void animation_06(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {65.0, 65.0, 0, 0.5}, r2[] = {60, 60, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/redqueen.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpUpdateScreen(NULL);
   // r2[3] += 0.001;
    //r2[2] += 0.001;
    r1[3] -= 0.001;
    //r1[3] -= 0.01;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_07(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {10, 10, 0, 0}, r2[] = {10, 10, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/redchess.jpeg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
   r1[0] += 0.01;
    r1[1] += 0.01;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_08(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {80.0, 80.0, 0, 0}, r2[] = {60, 60, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/darklake.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] += 0.1;
    r2[1] -= 0.1;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_09(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45.0, 45.0, 0, 0}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/chess2.png");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpUpdateScreen(NULL);
    r2[0] -= 0.1;
    r2[1] -= 0.1;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}

void animation_10(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45.0, 45.0, 0, 0}, r2[] = {0, 0, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/chess2.png");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpUpdateScreen(NULL);
    r2[0] -= 0.1;
    r2[1] -= 0.1;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
} 


void animation_11(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45.0, 45.0, 0, 0}, r2[] = {-14.899909, -14.899909 , 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/chess2.png");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpUpdateScreen(NULL);
    r2[0] -= 0.1;
    r2[1] -= 0.1;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_12(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {40.0, 40.0, 0, 0}, r2[] = {30, 30, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/violin.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] += 0.01;
    r1[1] += 0.01;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_13(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {40.0, 40.0, 0, 0}, r2[] = {30, 30, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/violin1.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_14(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {40.0, 40.0, 0, 0}, r2[] = {30, 30, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/violin2.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
   /* r1[0] += 0.01;
    r1[1] += 0.01;*/
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_15(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {40.0, 40.0, 0, 0}, r2[] = {20.0, 20.0, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/piano1.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] -= 0.01;
    r1[1] -= 0.01;
    r2[0] += 0.01;
    r2[1] += 0.01;

    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_15bis(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {37.580406 , 37.580406, 0, 0}, r2[] = {22.420055, 22.420055, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/piano2.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] -= 0.01;
    r1[1] -= 0.01;
    r2[0] += 0.01;
    r2[1] += 0.01;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_16(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {30.0, 30.0, 0, 0}, r2[] = {30.0, 30.0, 0.0, 0.0}, r = 0;

  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/architecture.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    //r2[3] += 0.1;
    r2[2] += 0.01;
   /* r2[0] -= 0.1;
    r2[1] -= 0.1;*/
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_17(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {30.0, 30.0, 0, 0}, r2[] = {30.0, 30.0, 0.0, 0.0}, r = 0;

  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/architecture.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r2[3] += 0.01;
   // r2[2] += 0.01;
   /* r2[0] -= 0.1;
    r2[1] -= 0.1;*/
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_18(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45.0, 45.0, 0, 0}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/architecture.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r2[3] += 0.001;
    r2[2] += 0.001;
    r2[0] -= 0.1;
    r2[1] -= 0.1;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_19(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45.0, 45.0, 0, 0}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/archi3.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r2[3] += 0.001;
    r2[2] += 0.001;
    r2[0] -= 0.1;
    r2[1] -= 0.1;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_20(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45.0, 45.0, 0, 0}, r2[] = {32.700188, 32.700188, 0.123000, 0.123000}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/archi1.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
   r1[0] -= 0.1;
   r2[2] -= 0.001;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_21(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {32.800186, 45.0, 0, 0}, r2[] = {32.700188, 32.700188, 0.001000, 0.123000}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/archi1.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] += 0.1;
   r2[2] += 0.001;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_22(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {60.0, 60.0, 0, 0.0}, r2[] = {45, 45, 0.0, 0.0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/pion.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
	r2[2] += 0.001;
	r2[3] += 0.001;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_23(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {50.0, 50.0, 0, 0.05}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/poker.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[3] -= 0.001;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_24(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {78.299492, 45.0, 0, 0.05}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/architec.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] -= 0.1;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_25(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {40.0, 40.0, 0, 0}, r2[] = {20.0, 20.0, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/lacasa1.PNG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] -= 0.01;
    r1[1] -= 0.01;
    r2[0] += 0.01;
    r2[1] += 0.01;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_26(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {32.781212, 32.781212, 0, 0}, r2[] = {27.230165, 27.230165, 0, 0}, r = 0;

  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/lacasa2.PNG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] -= 0.01;
    r1[1] -= 0.01;
    r2[0] += 0.01;
    r2[1] += 0.01;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_27(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45, 45, 0, 0.0}, r2[] = {35, 35, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/chessB.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r2[2] += 0.001;
    r2[3] += 0.001;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_28(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45, 45.0, 0, 0.0}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/redrose.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_29(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45, 45.0, 0, 0.0}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/roze.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}


void animation_30(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {60, 60.0, 0, 0.0}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/time.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpMap(s1, s2, r1, r2, r);
	r2[2] += 0.0001;
	r2[3] += 0.0001;
    return;
  }
}


void animation_31(int state) {
  /* INITIALISEZ VOS VARIABLES */
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {45, 45.0, 0, 0.0}, r2[] = {45, 45, 0, 0}, r = 0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    sprite = IMG_Load("picture/pen.JPG");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0x0);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    gl4dpMap(s1, s2, r1, r2, r);
	r2[2] += 0.001;
	r2[3] += 0.001;
	r2[0] -= 0.1;
	r2[1] -= 0.1;
    return;
  }
}


void animationsInit(void) {
  if(!_quadId)
    _quadId = gl4dgGenQuadf();
}
