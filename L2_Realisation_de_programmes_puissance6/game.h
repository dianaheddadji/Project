#ifndef GAME_H___
#define GAME_H___


//structure case qui gerera les différents alignements
typedef struct{
    int horizontal;
    int vertical;
}Case;


//prototypes des fonctions et procédure pour l'implémentation du jeu
int set(char grid[COLUMN_NB][LINE_NB], int column); //determine si on a le droit de placer ici (1 oui 0 non)
int testGameOver(char grid[COLUMN_NB][LINE_NB]); //teste la présence d'un alignement (1 oui 0 non)
void play(int player, char grid[COLUMN_NB][LINE_NB], int column); //place le symbole correspondant au numéro du joueur


#endif
