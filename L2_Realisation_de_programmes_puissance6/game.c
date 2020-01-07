#include <stdio.h>
#include "display.h"
#include "game.h"


//fonction qui test si une case est libre
int set(char grid[COLUMN_NB][LINE_NB], int column){

    int line;
    int freeLine = -1; // initialisé à case occupée : (-1)
    column -= 1; //on decremente pour obtenir un nombre compris entre 0 et 10 (pour les 11 colonnes)
 
    if (column < 0 || column >= COLUMN_NB) //if out of range
        return 0;

    for (line = LINE_NB-1 ; line >= 0; --line)
        if (grid[column][line] == VOID) // on regarde si pour une colonne donnée, la ligne qui l'a croise est une case vide
            freeLine = line;
 
    if (freeLine == -1) // si la case est occupée
        return 0;

    return 1;
}


void play(int player, char grid[COLUMN_NB][LINE_NB], int column){
    int freeLine = -1;
    int line;
    column -=1; //on decremente column pour obtenir un nombre compris entre 0 et 10 (pour les 11 colonnes)
 

	//ici on parcours la grille pour récupérer de nouveau le numéros de la ligne où la case est vide et on le met dans freeline
    for (line = 0; line < LINE_NB; ++line)
        if (grid[column][line] == VOID)
            freeLine = line;

 	//on se sert mtn de ces coordonnees pour attribuer à la case vide un symbole
    grid[column][freeLine] = (player == 0) ? CIRCLE:CROSS;
    printf("%s a joue grille[%d][%d]\n", (player == 0) ? "CERCLE":"CROIX", column+1, freeLine+1);
}


int testGameOver(char grid[COLUMN_NB][LINE_NB]){

    Case game[COLUMN_NB][LINE_NB];
    int line, column, ls1=-1, cs1=-1, lh1=-1, ch1=-1;
    
	for(line = LINE_NB-1; line >=0; --line)
        for (column = 0; column < COLUMN_NB; ++column){
            game[column][line].horizontal=1;
            game[column][line].vertical=1;
        }

    
	for(line = LINE_NB-1; line >= 0; --line){
        for(column = 0; column < COLUMN_NB; ++column)
			//comparaison de la case courante et de sa voisine de gauche (même symbole)
		
		// pour la verticale et les alignements en L
		if((grid[column][line] == grid[column][line+1]) && (grid[column][line] != VOID)){

                game[column][line].vertical = game[column][line+1].vertical+1;

				if(game[column][line].vertical == 6)
                    return 9;

				if(game[column][line].vertical >= 4){

					// |--
					if(column+2 < COLUMN_NB && ((grid[column][line] == grid[column+1][line]) && (grid[column+1][line] != VOID)) && ((grid[column+1][line] == grid[column+2][line]) && (grid[column+2][line] != VOID)))
						return 1;

					// L
					else if(column+2 < COLUMN_NB && (line+3 < LINE_NB) && ((grid[column][line] == grid[column+1][line+3]) && (grid[column+1][line+3] != VOID)) && ((grid[column+1][line+3] == grid[column+2][line+3]) && (grid[column+2][line+3] != VOID)))					return 2;

					// _|
					else if(column-2 >= 0 && (line+3 < LINE_NB) && ((grid[column][line] == grid[column-1][line+3]) && (grid[column-1][line+3] != VOID)) && ((grid[column-1][line+3] == grid[column-2][line+3]) && (grid[column-2][line+3] != VOID)))
						return 3;

					// --|
					else if(column-2 >= 0 && ((grid[column][line] == grid[column-1][line]) && (grid[column-1][line] != VOID)) && ((grid[column-1][line] == grid[column-2][line]) && (grid[column-2][line] != VOID)))
						return 4;
				}

					// |----
				else if(game[column][line].vertical == 3){
					if(column+3 < COLUMN_NB && ((grid[column][line] == grid[column+1][line]) && (grid[column+1][line] != VOID)) && ((grid[column+1][line] == grid[column+2][line]) && (grid[column+2][line] != VOID)) && ((grid[column+2][line] == grid[column+3][line]) && (grid[column+3][line] != VOID)))
						return 5;

					// ----|
					else if(column-3 >= 0 && ((grid[column][line] == grid[column-1][line]) && (grid[column-1][line] != VOID)) && ((grid[column-1][line] == grid[column-2][line]) && (grid[column-2][line] != VOID)) && ((grid[column-2][line] == grid[column-3][line]) && (grid[column-3][line] != VOID)))
						return 6;

				}

		}



		// pour l'horizontale et les alignements en L
		else if((grid[column][line] == grid[column-1][line]) && (grid[column][line] != VOID)){
                game[column][line].horizontal = game[column-1][line].horizontal+1;

                if (game[column][line].horizontal == 6)
                    return 10;

				if(game[column][line].horizontal >= 4){
					// ____|
					if(line-2 >= 0 && ((grid[column][line] == grid[column][line-1]) && (grid[column][line-1] != VOID)) && ((grid[column][line-1] == grid[column][line-2]) && (grid[column][line-2] != VOID)))
						return 7;

					// |____
					else if(line-2 >= 0 && (column-3 >= 0) && ((grid[column][line] == grid[column-3][line-1]) && (grid[column-3][line-1] != VOID)) && ((grid[column-3][line-1] == grid[column-3][line-2]) && (grid[column-3][line-2] != VOID)))
						return 8;

				}

		}

			
	} 

    return 0;
}

