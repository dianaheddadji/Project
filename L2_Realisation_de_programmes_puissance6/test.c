#include <stdio.h>
#include "display.h"
#include "game.h"
#include <time.h>
#include <stdlib.h>																					


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

	srand(time(NULL));
	//boucle principale
	while (!gameover){
		do{
    		printf("Au tour du Joueur : %s\nChoisissez une colonne[1:11] : ", player == 0 ? "CERCLE" : "CROIX");
			column = rand()%11+1;
	    }while(set(grid, column) == 0);

		play(player, grid, column);
		display(grid);
		counter++;
		
		int etat = testGameOver(grid);

		if(counter == COLUMN_NB * LINE_NB){
			gameover = 1;
	        printf("Match NUL !\n\n");
	    }

		switch(etat){
			case 1:
					printf("Joueur %s a Gagne avec |-- !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 2:
					printf("Joueur %s a Gagne avec L !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 3:
					printf("Joueur %s a Gagne avec _| !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 4:
					printf("Joueur %s a Gagne avec --| !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 5:
					printf("Joueur %s a Gagne avec |---- !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 6:
					printf("Joueur %s a Gagne avec ----| !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 7:
					printf("Joueur %s a Gagne avec ____| !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 8:
					printf("Joueur %s a Gagne avec |____ !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 9:
					printf("Joueur %s a Gagne avec | !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			case 10:
					printf("Joueur %s a Gagne avec ------ !\nColonne : %d\n", player == 0 ? "CERCLE" : "CROIX", column);
					gameover = 1;
					break;

			default:
					break;

		}


    	player = !player; //on change de joueur
    }

	return 0;
}
