#ifndef DISPLAY_H___
#define DISPLAY_H___

//constantes de jeu
#define COLUMN_NB 11 //nombre de colonnes
#define LINE_NB 13  //nombre de lignes
#define VOID ' '  //symboles
#define CROSS 'X'
#define CIRCLE 'O'

//prototypes des procédures d'initialisation et d'affichage
void initialization(char grid[COLUMN_NB][LINE_NB]); //initialisation à void
void display(char grid[COLUMN_NB][LINE_NB]); //affichage de l'état du jeu


#endif
