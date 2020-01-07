#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <GL4D/gl4dh.h>
#include "audioHelper.h"

#define NTEXTURES 5

static void         initGL(void);
static void         initData(void);
static void         init(int w, int h);
static void         draw(void);
static void         quit(void);
static void         sphereMove(void);
static float        myRand(float max);

enum {
  FREQ_MOY = 3
};

enum {
  TEX_STAR00, TEX_STAR01, TEX_STAR02, TEX_STAR03, TEX_STAR04, TEX_STAR05, NB_TEX
};

static int _w, _h;
static GLuint _pId = 0;
static GLuint _tId[NTEXTURES] = {0};
static GLuint _screen = 0;

static int _state = 3;

static int _nb_spheres = 0;
static int _nb_white_sph = 0;
static int _nb_color_sph = 0;
static float *_sph_att;
static GLuint _sphere = {0};
static GLuint _mode = 0;
static float _sph_w = 0;
static int _disco = 0;


static float myRand(float max) {
  float rand = gl4dmURand() * max;
  float sgn = gl4dmURand() * 2.0;
  sgn = sgn > 1.0 ? 1.0 : -1.0;
  rand *= sgn;
  return rand;
}

static void initGL(void) {

  _pId  = gl4duCreateProgram("<vs>shaders/diamant.vs", "<fs>shaders/diamant.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
}

static void initData(void) {
  int i;
  SDL_Surface * t;
  static char * files[] = {
    "images/reddiamond.jpg", 
    "images/diamant.jpg",
    "images/bluediamond.jpg",
    "images/diamant.jpg",
    "images/reddiamond.jpg",
    "images/diamant.jpg"
  };

  if(!_tId[0]) {
    glGenTextures(NTEXTURES, _tId);
  }
  for(i = 0; i < NTEXTURES; i++) {
    glBindTexture(GL_TEXTURE_2D, _tId[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if( (t = IMG_Load(files[i])) != NULL ) {
      int mode = t->format->BytesPerPixel == 4 ? GL_BGRA : GL_BGR;
      mode = t->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;     
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0, mode, GL_UNSIGNED_BYTE, t->pixels);
      SDL_FreeSurface(t);
    } else {
      fprintf(stderr, "can't open file %s : %s\n", files[i], SDL_GetError());
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
  }
  _sphere = gl4dgGenSpheref(2, 2);

  _nb_spheres = 150;
  _nb_color_sph = _nb_spheres - 50;
  _nb_white_sph = _nb_spheres - _nb_color_sph;
  _sph_att = malloc(_nb_spheres * 5 * sizeof(*_sph_att));
  assert(_sph_att);
  for(i = 0; i < _nb_spheres; i++) {
    _sph_att[i * 4 + 0] = myRand(7);
    _sph_att[i * 4 + 1] = myRand(3);
    if(i < _nb_color_sph) {
      _sph_att[i * 4 + 2] = (gl4dmURand() * 10) + 1.0;
      _sph_att[i * 4 + 3] = 0.1;
    }
    else {
      _sph_att[i * 4 + 2] = 0;
      _sph_att[i * 4 + 3] = 0.01;
    }
  }
}

static void init(int w, int h) {
  _w = w; _h = h;
  initGL();
  initData();
}

static void sphereMove(void) {
	_mode++;
	_state++;
	_disco = 1;
	return;
}

static void draw(void) {
  int i;
  GLint vp[4];
  GLfloat dt = 0.0;
  static GLfloat gap = 0.0;
  GLboolean gdt = glIsEnabled(GL_DEPTH_TEST);
  glGetIntegerv(GL_VIEWPORT, vp);
  dt = SDL_GetTicks();

  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * vp[3] / vp[2], 0.5 * vp[3] / vp[2], 1.0, 1000.0);
  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();

  switch(_mode) {
    case 0:
      gl4duTranslatef(0, 0, -3.5);
      break;
    case 1:
      gl4duTranslatef(0, 0, -5);
      break;
    case 2:
      gl4duTranslatef(0, 0, -7.5);
      break;
    default:
      gl4duTranslatef(0, 0, -10);
      break;
  }

  glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gl4duGetMatrixData();
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
  glUseProgram(_pId);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, (_state > 3 ? _tId[0] : 0));
  glUniform1i(glGetUniformLocation(_pId, "tex0"), 0);
  glUniform1i(glGetUniformLocation(_pId, "tex1"), 1);
  glUniform1i(glGetUniformLocation(_pId, "temps"), dt);
  glUniform1i(glGetUniformLocation(_pId, "disco"), _disco);
  glUniform1f(glGetUniformLocation(_pId, "gap"), gap);

  gl4duPushMatrix(); {
    gl4duRotatef(0, 0, 1, 0);
      gl4duTranslatef(0, 0, _sph_w);  
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4dgDraw(_sphere);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);

  for(i = 0; i < _nb_spheres; i++) {
    int id = (gl4dmURand() * 4.0) + 1.0;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, (_state > 3 ? _tId[id] : 0));
    gl4duPushMatrix(); {
      gl4duTranslatef(_sph_att[i * 4 + 0], _sph_att[i * 4 + 1], _sph_w  * _sph_att[i * 4 + 2]);  
      gl4duScalef(_sph_att[i * 4 + 3], _sph_att[i * 4 + 3] , _sph_att[i * 4 + 3]);
      gl4duSendMatrices();
    } gl4duPopMatrix();
    glUniform1i(glGetUniformLocation(_pId, "disco"), 0);
    gl4dgDraw(_sphere);
  }
  
  _sph_w += (_sph_w < 8.0 ? (_state >= 6 ? 0.01 : 0) : 0);
  sphereMove();
  gap += 0.01;
  
  if(!gdt)
    glDisable(GL_DEPTH_TEST);
}


static void quit(void) {
  if(_tId[0]) {
    glDeleteTextures(NTEXTURES, _tId);
    _tId[0] = 0;
  }

  if(_screen) {
    gl4dpSetScreen(_screen);
    gl4dpDeleteScreen();
    _screen = 0;
  }
}

void diamant(int state) {
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
    return;
  default:
    draw();
    return;
  }
}
