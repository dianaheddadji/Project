/*!\file audioHelper.c
 *
 * \brief éléments audio pouvant être utiles pour la démo.
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date May 5, 2014 - February 26, 2016
 */

#include "audioHelper.h"
#include <fftw3.h>
#include <assert.h>

/*!\brief pointeur vers la musique chargée par SDL_Mixer */
static Mix_Music * _mmusic = NULL;

/*!\brief pointeur vers le flux audio.
 * \see ahGetAudioStream
 * \see ahSetAudioStream
 */
static Uint8 * _audioStream = NULL;
/*!\brief longueur du flux audio.
 * \see ahGetAudioStreamLength
 * \see ahSetAudioStream
 */
static int _audioStreamLength = 0;

#define ECHANTILLONS 1024
/*!\brief amplitude des basses et aigus du signal sonore */
static GLfloat _basses = 0, _aigus = 0;

static fftw_complex * _in4fftw = NULL, * _out4fftw = NULL;
/*!\brief donnée à précalculée utile à la lib fftw */
static fftw_plan _plan4fftw = NULL;

int ahGetAudioStreamFreq(void) {
  return _basses;
}

int ahGetAudioStreamAigus(void) {
  return _aigus;
}

/*!\brief renvoie le pointeur vers le flux audio.
 * \return le pointeur vers le flux audio.
 */
Uint8 * ahGetAudioStream(void) {
  return _audioStream;
}


/*!\brief renvoie la longueur du flux audio.
 * \return la longueur du flux audio.
 */
int ahGetAudioStreamLength(void) {
  return _audioStreamLength;
}

/*!\brief met à jour le pointeur vers le flux audio et sa longueur.
 */
void ahSetAudioStream(Uint8 * audioStream, int audioStreamLength, GLfloat basses, GLfloat aigus) {
  _basses = basses;
  _aigus = aigus;
  _audioStream = audioStream;
  _audioStreamLength = audioStreamLength;
}

/*!\brief Cette fonction est appelée quand l'audio est joué et met 
 * dans \a stream les données audio de longueur \a len.
 * \param udata pour user data, données passées par l'utilisateur, ici NULL.
 * \param stream flux de données audio.
 * \param len longueur de \a stream.
 */

static void mixCallback(void *udata, Uint8 *stream, int len) {
  if(_plan4fftw) {
    int i, l = MIN(len >> 1, ECHANTILLONS);
    Sint16 *d = (Sint16 *)stream;
    for(i = 0; i < l; i++)
      _in4fftw[i][0] = d[i] / ((1 << 15) - 1.0);
    fftw_execute(_plan4fftw);
    for(i = 0, _basses = 0, _aigus = 0; i < l >> 2; i++) {
      if(i < l >> 3)
  _basses += sqrt(_out4fftw[i][0] * _out4fftw[i][0] + _out4fftw[i][1] * _out4fftw[i][1]);
      else
  _aigus  += sqrt(_out4fftw[i][0] * _out4fftw[i][0] + _out4fftw[i][1] * _out4fftw[i][1]);
    }
    _basses /= l >> 3;
    _aigus  /= l >> 3;
    //if(_basses > 5.0) printf("%f\n", _basses);
  }

  ahSetAudioStream(stream, len, _basses, _aigus);
  gl4dhUpdateWithAudio();
  ahSetAudioStream(NULL, 0, 0, 0);
}

/*!\brief Cette fonction initialise les paramètres SDL_Mixer et charge
 *  le fichier audio.
 */
void ahInitAudio(const char * file) {
#if defined(__APPLE__)
  int mult = 1;
#else
  int mult = 2;
#endif
  int mixFlags = MIX_INIT_MP3, res;
  /* préparation des conteneurs de données pour la lib FFTW */
  _in4fftw   = fftw_malloc(ECHANTILLONS *  sizeof *_in4fftw);
  memset(_in4fftw, 0, ECHANTILLONS *  sizeof *_in4fftw);
  assert(_in4fftw);
  _out4fftw  = fftw_malloc(ECHANTILLONS * sizeof *_out4fftw);
  assert(_out4fftw);
  _plan4fftw = fftw_plan_dft_1d(ECHANTILLONS, _in4fftw, _out4fftw, FFTW_FORWARD, FFTW_ESTIMATE);
  assert(_plan4fftw);
  res = Mix_Init(mixFlags);
  if( (res & mixFlags) != mixFlags ) {
    fprintf(stderr, "Mix_Init: Erreur lors de l'initialisation de la bibliotheque SDL_Mixer\n");
    fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
    //exit(3); commenté car ne réagit correctement sur toutes les architectures
  }
  if(Mix_OpenAudio(44100, AUDIO_S16LSB, 1, mult * ECHANTILLONS) < 0)
    exit(4);  
  if(!(_mmusic = Mix_LoadMUS(file))) {
    fprintf(stderr, "Erreur lors du Mix_LoadMUS: %s\n", Mix_GetError());
    exit(5);
  }
  Mix_SetPostMix(mixCallback, NULL);
  if(!Mix_PlayingMusic())
    Mix_PlayMusic(_mmusic, 1);
}

/*!\brief Libère l'audio.
 */
void ahClean(void) {
  if(_mmusic) {
    if(Mix_PlayingMusic())
      Mix_HaltMusic();
    Mix_FreeMusic(_mmusic);
    _mmusic = NULL;
  }
  Mix_CloseAudio();
  Mix_Quit();
  if(_plan4fftw) {
    fftw_destroy_plan(_plan4fftw);
    _plan4fftw = NULL;
  }
  if(_in4fftw) {
    fftw_free(_in4fftw); 
    _in4fftw = NULL;
  }
  if(_out4fftw) {
    fftw_free(_out4fftw); 
    _out4fftw = NULL;
  }
  gl4duClean(GL4DU_ALL);
}
