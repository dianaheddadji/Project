#include <stdio.h>
#include "display.h"
#include "game.h"																										


int main(){
	//on declare un tableau à deux dimensions
	char grid[COLUMN_NB][LINE_NB];

	//déclaration variables locales utiles
	int column;
    int player = 1;
	int counter = 0; //pour la grille complétement remplie
    int gameover = 0;

	//initialisation de la grille + affichage
    initialization(grid);
    display(grid);

	//boucle principale
	while (!gameover){
		do{
    		printf("Au tour du Joueur : %s\nChoisissez une colonne[1:11] : ", player == 0 ? "CERCLE" : "CROIX");
			scanf("%d", &column);
	    }while(set(grid, column) == 0);

		play(player, grid, column);
		display(grid);
		counter++;
	
		if(testGameOver(grid) > 0){
			gameover = 1;
	        printf("Joueur %s a Gagne !\n\n", player == 0 ? "CERCLE" : "CROIX");
		}

		else if(counter == COLUMN_NB * LINE_NB){
			gameover = 1;
	        printf("Match NUL !\n\n");
	    }

    	player = !player; //on change de joueur
    }

	return 0;
}

