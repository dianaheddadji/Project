/*!\file window.c
 *
 * \brief Utilisation de GL4Dummies pour réaliser une démo.
 *
 * Ici est géré l'ouverture de la fenêtre ainsi que l'ordonnancement
 * des animations. Apriori les seuls éléments à modifier ici lors de
 * votre intégration sont le tableau static \ref _animations et le nom
 * du fichier audio à lire.
 *
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date May 05, 2014 - February 26, 2016
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
	{ 5150, animation_earth, NULL, transition_fondu },
 	{ 15, animation_earth2, 	NULL, transition_fondu },
  { 9200, animation_anim2, animation_anim2, NULL },
  { 10000, animation_anim4, NULL, transition_fondu },
  { 7300, animation_, animation_base, transition_fondu },
  { 1200, animation_flash, NULL, NULL },
  { 10050, animation_vide, animation_anim5, transition_fondu },
  { 10000, animation_lum, animation_anim6, transition_fondu },
  { 3000, animation_lum, animation_lum, transition_fondu },
  { 8750, animation_earth2, animation_earth2, transition_fondu },
  { 6400, diamant, diamant, NULL },
  { 5000, piano, piano, transition_fondu },
  { 5150, diamant, animation_vide, NULL },
 	{ 6000, cookie, NULL, NULL },
  { 5000, piano, NULL, NULL },
  { 5050, animation_earth, credits, transition_fondu },
  { 5000, credits, NULL, NULL },
  {    0, NULL, NULL, NULL } /* Toujours laisser à la fin */
};


/*!\brief dimensions initiales de la fenêtre */
static GLfloat _dim[] = {800, 700};

/*!\brief fonction principale : initialise la fenêtre, OpenGL, audio
 * et lance la boucle principale (infinie).
 */
int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "Cookie Blinders", 
			 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			 _dim[0], _dim[1],
			 SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwResizeFunc(resize);
  gl4duwKeyDownFunc(keydown);
  gl4duwDisplayFunc(gl4dhDraw);

  ahInitAudio("UmbrellaAcademyTheme.mp3");
  gl4duwMainLoop();
  return 0;
}

/*!\brief Cette fonction initialise les paramètres et éléments OpenGL
 * ainsi que les divers données et fonctionnalités liées à la gestion
 * des animations.
 */

static void init(void) {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	 /* une dernière texture vide pour y faire des calculs d'effets */
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
