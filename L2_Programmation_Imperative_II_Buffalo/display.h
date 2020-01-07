#ifndef DISPLAY_H___
#define DISPLAY_H___

#include <stdio.h>

//Les constantes
#define COLUMN_NB 11 //nombre de colonnes
#define LINE_NB 8 //nombre de lignes

//Symboles
#define VOID '_'
#define BUFFALO 'O'
#define INDIAN 'I'

//prototypes des procédures d'initialisation et d'affichage
void initialization(char grid[COLUMN_NB][LINE_NB], char * dogs); //initialisation à void
void display(char grid[COLUMN_NB][LINE_NB]); //affichage de l'état du jeu

#endif
