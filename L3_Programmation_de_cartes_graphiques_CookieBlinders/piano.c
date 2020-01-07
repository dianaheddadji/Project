#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL_mixer.h>
#include <fftw3.h>
#include <GL4D/gl4dh.h>
#include "audioHelper.h"

static void init(int w, int h);
static void audio(void);
static void draw(void);
static void drawPixelWithThickness(int x, int y, int t);
static void quit(void);

#define ECHANTILLONS 300

static Sint16 _hauteurs[ECHANTILLONS];
static GLuint _screen = 0;
static int _w, _h;

static fftw_complex * _in4fftw = NULL, * _out4fftw = NULL;
static fftw_plan _plan4fftw = NULL;

static int _color[6][3] = {
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
};

static void init(int w, int h) {
  _w = w; _h = h;
  /* préparation des conteneurs de données pour la lib FFTW */
  _in4fftw   = fftw_malloc(ECHANTILLONS *  sizeof *_in4fftw);
  memset(_in4fftw, 0, ECHANTILLONS *  sizeof *_in4fftw);
  assert(_in4fftw);
  _out4fftw  = fftw_malloc(ECHANTILLONS * sizeof *_out4fftw);
  assert(_out4fftw);
  _plan4fftw = fftw_plan_dft_1d(ECHANTILLONS, _in4fftw, _out4fftw, FFTW_FORWARD, FFTW_ESTIMATE);
  assert(_plan4fftw);
}

static void drawPixelWithThickness(int x, int y, int t) {
  int i;
  for(i = 0; i < t; i++) {
    gl4dpPutPixel(x+i, y+i);
    gl4dpPutPixel(x, y);
    gl4dpPutPixel(x-i, y-i);
  }
}

static void draw(void) {
  int i;
  int nc = 1;
  static int cur_color = 0;
  gl4dpSetScreen(_screen);
  gl4dpClearScreenWith(RGB(0, 0, 0));
  for(i = 0; i < ECHANTILLONS; ++i) {
    int x0, y0;
    gl4dpSetColor(RGB(_color[cur_color][0], _color[cur_color][1], _color[cur_color][2]));
    x0 = (i * (_w - 1)) / (ECHANTILLONS - 1);
    y0 = _hauteurs[i];
    drawPixelWithThickness(x0 + _w/2.7, y0 + _h/2.7, 30);
    cur_color = (cur_color + 1) % nc;
  }
  gl4dpUpdateScreen(NULL);
}

static void audio(void) {
  if(_plan4fftw) {
    int i, j, l = MIN(ahGetAudioStreamLength() >> 1, ECHANTILLONS);
    Sint16 *d = (Sint16 *)ahGetAudioStream();
    for(i = 0; i < l; i++)
      _in4fftw[i][0] = d[i] / ((1 << 15) - 1.0);
    fftw_execute(_plan4fftw);
    for(i = 0; i < l >> 2; i++) {
      _hauteurs[4 * i] = (int)(sqrt(_out4fftw[i][0] * _out4fftw[i][0] + _out4fftw[i][1] * _out4fftw[i][1]) * exp(2.0 * i / (double)(l / 4.0)));
      for(j = 1; j < 4; j++)
	_hauteurs[4 * i + j] = MIN(_hauteurs[4 * i], 255);
    }
  }
}

static void quit(void) {
  if(_screen) {
    gl4dpSetScreen(_screen);
    gl4dpDeleteScreen();
    _screen = 0;
  }
}

void piano(int state) {
  switch(state) {
  case GL4DH_INIT:
    _screen = gl4dpInitScreen();
    init(gl4dpGetWidth(), gl4dpGetWidth());
    return;
  case GL4DH_FREE:
    quit();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    audio();
    return;
  default:
    draw();
    return;
  }
}
