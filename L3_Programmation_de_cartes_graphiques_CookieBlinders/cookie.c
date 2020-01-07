#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <GL4D/gl4dh.h>
#include "audioHelper.h"

static void         init(int w, int h);
static void         draw(void);
static void         quit(void);
static float        myRand(float max);

#define ECHANTILLONS 1024
#define NB_TEXTURES 7

static GLuint _pId = 0;
static GLuint _sphere = 0;
static GLfloat _lumPos0[4] = {-15.1, 20.0, 20.7, 1.0};
static GLfloat _basses = 0, _aigus = 0;

static int _w, _h;
static GLuint _screen = 0;

static int _nb_spheres = 0;
static float *_sph_att;

static const char * _texture_filenames[] = { 
  "images/cookie.png", 
  "images/cookie.png", 
  "images/cookie.png",
  "images/cookie.png",
  "images/cookie.png",
  "images/cookie.png",
  "images/cookie.png",
};

static const char * _sampler_names[] = {
  "eday", 
  "ebump", 
  "egloss" 
};

enum texture_e {
  TE_STAR00 = 0, 
  TE_EBUMP,      
  TE_EGLOSS,    
  TE_END   
};

enum texture_s {
  TE_STAR01,
  TE_STAR02,
  TE_STAR03,
  TE_STAR04,
  NB_STAR
};

static GLuint _tId[NB_TEXTURES] = {0};

static float myRand(float max) {
  float rand = gl4dmURand() * max;
  float sgn = gl4dmURand() * 2.0;
  sgn = sgn > 1.0 ? 1.0 : -1.0;
  rand *= sgn;
  return rand;
}

static void init(int w, int h) {
  _w = w; _h = h;
  int i;
  if(!_tId[0]) {
    glGenTextures(NB_TEXTURES, _tId);
    for(i = 0; i < NB_TEXTURES; i++) {
      SDL_Surface * t;
      glBindTexture(GL_TEXTURE_2D, _tId[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      if( (t = IMG_Load(_texture_filenames[i])) != NULL ) {
  int mode = t->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;    
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0, mode, GL_UNSIGNED_BYTE, t->pixels);
  SDL_FreeSurface(t);
      } else {
  fprintf(stderr, "can't open file %s : %s\n", _texture_filenames[i], SDL_GetError());
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      }
    }
  }

  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
  _pId  = gl4duCreateProgram("<vs>shaders/cookie.vs", "<fs>shaders/cookie.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  _sphere = gl4dgGenSpheref(30, 30);

  _nb_spheres = 200;
  _sph_att = malloc(_nb_spheres * 2 * sizeof(*_sph_att));
  assert(_sph_att);
  for(i = 0; i < _nb_spheres; i++) {
    _sph_att[i * 2 + 0] = myRand(1.5);
    _sph_att[i * 2 + 1] = myRand(1.1);
  }
}

static void draw(void) {
  int i;
  static GLfloat a0 = 0.0;
  static Uint32 t0 = 0;
  GLint vp[4];
  GLfloat dt = 0.0, steps[2] = {1.0f / _w, 1.0f / _h};
  GLfloat lumPos[4], *mat;
  Uint32 t;
  dt = ((t = SDL_GetTicks()) - t0) / 1000.0;
  t0 = t;

  GLboolean gdt = glIsEnabled(GL_DEPTH_TEST);
  glGetIntegerv(GL_VIEWPORT, vp);
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * vp[3] / vp[2], 0.5 * vp[3] / vp[2], 1.0, 1000.0);
  gl4duBindMatrix("modelViewMatrix");
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();
  gl4duTranslatef(0, 0, -3);
  mat = gl4duGetMatrixData();
  MMAT4XVEC4(lumPos, mat, _lumPos0);

  glUseProgram(_pId);
  for(i = 0; i < _nb_spheres; i++) {
    int id = (gl4dmURand() * 4.0) + 3.0;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _tId[id]);
    gl4duPushMatrix(); { 
      gl4duTranslatef(_sph_att[i * 2 + 0], _sph_att[i * 2 + 1], 0);  
      GLfloat sc = gl4dmURand() * 0.030;
      gl4duScalef(sc, sc, sc);
      gl4duSendMatrices();
    } gl4duPopMatrix();
    gl4dgDraw(_sphere);
  }


  for(i = 0; i < TE_END; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, _tId[i]);
    gl4duRotatef(a0, 0, 1, 0);
    gl4duScalef(0.90, 0.90, 0.5);
    glUniform1i(glGetUniformLocation(_pId, _sampler_names[i]), i);
  }
  glUniform1f(glGetUniformLocation(_pId, "basses"), _basses);
  glUniform1f(glGetUniformLocation(_pId, "aigus"), _aigus);
  glUniform2fv(glGetUniformLocation(_pId, "steps"), 1, steps);
  glUniform4fv(glGetUniformLocation(_pId, "lumPos"), 1, lumPos);
  gl4duSendMatrices();
  gl4dgDraw(_sphere);
  

  for(i = 0; i < TE_END; i++) {
    glActiveTexture(GL_TEXTURE0 + TE_END - 1 - i);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  a0 += 360.0 * dt / 24.0;

  if(!gdt)
    glDisable(GL_DEPTH_TEST);

}

static void quit(void) {

  if(_tId[0]) {
    glDeleteTextures(NB_TEXTURES, _tId);
    _tId[0] = 0;
  }

  if(_screen) {
    gl4dpSetScreen(_screen);
    gl4dpDeleteScreen();
    _screen = 0;
  }
}

void cookie(int state) {
  switch(state) {
  case GL4DH_INIT:
    _screen = gl4dpInitScreen();
    init(gl4dpGetWidth(), gl4dpGetHeight());
    return;
  case GL4DH_FREE:
    quit();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    (Sint16 *)ahGetAudioStream();
    _basses = ahGetAudioStreamFreq();
    _aigus = ahGetAudioStreamAigus();
    return;
  default:
    draw();
    return;
  }
}
