#include <stdio.h>
#include "display.h"


//procedure qui servira à initialiser toutes les cases du tableau à void
void initialization(char grid[COLUMN_NB][LINE_NB]){
    int column, line;
    for(column = 0; column < COLUMN_NB; ++column)
        for(line = 0; line < LINE_NB; ++line)
            grid[column][line]=VOID;
}


//procedure qui servira à afficher la grille du puissance 6
void display(char grid[COLUMN_NB][LINE_NB]){
    int column, line;
    
	printf("\n\n		");

	//boucle for pour afficher le numero de la colonne
    for(column = 0; column < COLUMN_NB; ++column)
        printf(" %d ", column+1); //pour commencer à 1
    printf("\n		|");


    for(column = 0; column < COLUMN_NB; ++column)
        printf("___");
    printf("|\n");

    for(line = 0; line < LINE_NB; ++line){
        printf("		|");
        for(column = 0; column < COLUMN_NB; ++column)
            printf(" %c ", grid[column][line]);
        printf("|\n");
    }
	printf("		|");

    for(column = 0; column < COLUMN_NB; ++column)
        printf("___");
    printf("|\n\n\n");
}
