/*!\file animations.h
 *
 * \brief Votre espace de liberté : c'est ici que vous pouvez ajouter
 * vos fonctions de transition et d'animation avant de les faire
 * référencées dans le tableau _animations du fichier \ref window.c
 *
 * Des squelettes d'animations et de transitions sont fournis pour
 * comprendre le fonctionnement de la bibliothèque. En bonus des
 * exemples dont un fondu en GLSL.
 *
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date May 05, 2014
 */
#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

  extern void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void animation_flash(int state);
  extern void animation_vide(int state);
  extern void animation_base(int state);
  extern void animation_earth(int state);
  extern void animation_earth2(int state);
  extern void animation_boule(int state);
  extern void animation_anim2(int state);
  extern void animation_anim4(int state);
  extern void animation_anim5(int state);
  extern void animation_anim6(int state);
  extern void animationsInit(void);

  extern void base_init(void);
  extern void base_draw(void);

  extern void earth_init(void);
  extern void earth_draw(void);
	extern void earth_init2(void);
	extern void audio(void);
	extern void earth_draw2(void);

  extern void base2_init(void);
  extern void base2_draw(void);

  extern void boule_init(void);
  extern void boule_draw(void);

  extern void anim2_init(void);
  extern void anim2_draw(void);

  extern void anim3_init(void);
  extern void anim3_draw(void);

  extern void anim4_init(void);
  extern void anim4_draw(void);

  extern void anim5_init(void);
  extern void anim5_draw(void);

  extern void anim6_init(void);
  extern void anim6_draw(void);
	void animation_lum(int state);
  extern void diamant(int state);
  extern void earth(int state);
  extern void piano(int state);
	extern void animation_(int state);
  extern void cookie(int state);
  extern void credits(int state);




#ifdef __cplusplus
}
#endif

#endif
