#include "display.h"

//Procedure qui servira à initialiser toutes les cases du tableau à VOID ' '
void initialization(char grid[COLUMN_NB][LINE_NB], char * dogs){
	int column, line, i;
	//Placement des vides
	for(column = 0; column < COLUMN_NB; ++column)
	for(line = 1; line < LINE_NB; ++line)
	grid[column][line]=VOID;

	//Placement des buffles
	for(line = 0; line < 1; ++line)
	for(column = 0; column < COLUMN_NB; ++column)
	grid[column][line]=BUFFALO;

	//Placement du chef Indien
	grid[COLUMN_NB/2][LINE_NB-2]=INDIAN;

	//Placement des chiens
	for(line = LINE_NB-2, column = (COLUMN_NB/2)-1, i = 0; column > (COLUMN_NB/2)-3; --column, ++i)
	grid[column][line]=dogs[i];

	for(line = LINE_NB-2, column = (COLUMN_NB/2)+1, i = 2; column < (COLUMN_NB/2)+3; ++column, ++i)
	grid[column][line]=dogs[i];
}


//Procedure qui servira à afficher la grille du Buffalo
void display(char grid[COLUMN_NB][LINE_NB]){
	int column, line;

	printf("\n\n\t\t\t\tBuffalo");
	printf("\n\n\t\t_");
	for(column = 0; column < COLUMN_NB; ++column)
	printf("____");

	printf("\n\t\t");
	for(line = 0; line < LINE_NB; ++line){
		for(column = 0; column < COLUMN_NB; ++column)
		printf("|_%c_",grid[column][line]);
		printf("|%d\n\t\t",line+1);//pour commencer à 1
	}

	//boucle for pour afficher le numero de la colonne
	for(column = 0; column < COLUMN_NB; ++column)
	printf("%d   ", column+1); //pour commencer à 1
	printf("\n\n\n");
}
