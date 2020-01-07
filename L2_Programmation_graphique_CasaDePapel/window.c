/*!\file window.c
 */
#include <stdlib.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4duw_SDL2.h>
#include "animations.h"
#include "audioHelper.h"

/* Prototypes des fonctions statiques contenues dans ce fichier C. */
static void init(void);
static void quit(void);
static void resize(int w, int h);
static void keydown(int keycode);

/*!\brief tableau contenant les animations sous la forme de timeline,
 * ce tableau se termine toujours par l'élémént {0, NULL, NULL,
 * NULL} */
static GL4DHanime _animations[] = {
 {2000,  animation_01, NULL, NULL },
 { 2400, animation_02, NULL, NULL },
 { 2000, animation_03, NULL, NULL },
 { 2500, animation_04, animation_05, transition_01 },
 { 3000, animation_06, NULL, NULL },
 { 5000, animation_07, NULL, NULL },
 { 2000, animation_06, NULL, NULL },
 { 10000,animation_08, NULL, NULL },
 { 2000, animation_06, NULL, NULL },
 { 2500, animation_09, NULL, NULL },
 { 1000, animation_06, NULL, NULL },
 { 1000,  animation_10, NULL, NULL },
 { 1000, animation_06, NULL, NULL }, 
 { 4000, animation_11, NULL, NULL },
 { 2200, animation_12, NULL, NULL },
 { 2000, animation_13, animation_14, transition_01 },
 { 3000, animation_14, NULL, NULL },
 { 5000, animation_15, NULL, NULL },
 { 4000, animation_15, animation_15bis, cheddarfondu },
 {1000,  animation_15bis, NULL, NULL },
 {1700,  animation_16, NULL, NULL },
 { 1700, animation_17, NULL, NULL },
 { 1700, animation_16, NULL, NULL },
 { 300, animation_18, NULL, NULL },
 { 300, animation_19, NULL, NULL },
 { 300, animation_18, NULL, NULL },
 { 300, animation_19, NULL, NULL },
 { 300, animation_18, NULL, NULL },
 { 300, animation_19, NULL, NULL },
{ 1000, animation_20, NULL, NULL },
{ 2000, animation_21, NULL, NULL },
 { 2000,animation_22, NULL, NULL  },
 { 2000, animation_23, NULL, NULL  },
 { 3000, animation_24, NULL, NULL  },
{ 12000, animation_25, NULL, NULL },
 { 3000, animation_26, NULL, NULL },
{ 3000, animation_27, NULL, NULL },
{ 1000, animation_27, animation_28, transition_01 },
 { 2000, animation_28, animation_29, transition_01 },
{ 2000, animation_30, NULL, NULL },
{ 7500, animation_30, animation_31, cheddarfondu },
  {    0, NULL, NULL, NULL } /* Toujours laisser à la fin */
};

/*!\brief dimensions initiales de la fenêtre */
static GLfloat _dim[] = {1000, 800};

/*!\brief fonction principale : initialise la fenêtre, OpenGL, audio
 * et lance la boucle principale (infinie).
 */
int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "La Casa de Papel", 
			 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			 _dim[0], _dim[1],
			 SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwResizeFunc(resize);
  gl4duwKeyDownFunc(keydown);
  gl4duwDisplayFunc(gl4dhDraw);

  ahInitAudio("MyLifeIsGoingOn.mod");
  gl4duwMainLoop();
  return 0;
}

/*!\brief Cette fonction initialise les paramètres et éléments OpenGL
 * ainsi que les divers données et fonctionnalités liées à la gestion
 * des animations.
 */
static void init(void) {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  gl4dhInit(_animations, _dim[0], _dim[1], animationsInit);
  resize(_dim[0], _dim[1]);
}

/*!\brief paramétre la vue (viewPort) OpenGL en fonction des
 * dimensions de la fenêtre.
 * \param w largeur de la fenêtre.
 * \param w hauteur de la fenêtre.
 */
static void resize(int w, int h) {
  _dim[0] = w; _dim[1] = h;
  glViewport(0, 0, _dim[0], _dim[1]);
}

/*!\brief permet de gérer les évènements clavier-down.
 * \param keycode code de la touche pressée.
 */
static void keydown(int keycode) {
  switch(keycode) {
  case SDLK_ESCAPE:
  case 'q':
    exit(0);
  default: break;
  }
}

/*!\brief appelée à la sortie du programme (atexit).
 */
static void quit(void) {
  ahClean();
  gl4duClean(GL4DU_ALL);
}
