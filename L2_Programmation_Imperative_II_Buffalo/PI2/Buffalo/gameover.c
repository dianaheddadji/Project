#include "gameplay.h"

int testGameOver(char grid[COLUMN_NB][LINE_NB], int buffles){
	int column, line, block;

	// On parcourt la dernière ligne pour voir la présence d'un buffle
	for(column = 0, line = LINE_NB - 1; grid[column][line]; ++column)
	if(grid[column][line] == BUFFALO)
	return 1; // Joueur Buffle gagne

	// Cas particuliers : si l'avance des 5 derniers buffles est bloquée
	if(buffles <= 5){
		block = 0;
		for(column = 0; column < COLUMN_NB; ++column)
		for(line = 0; line < LINE_NB; ++line)
		if(grid[column][line] == BUFFALO) // On cherche les coordonées des 5 buffles
		if(grid[column][line+1] != VOID) // On teste s'il ya un chien ou l'Indien devant eux
		++block; // Il y a un blocage
		if(block == buffles) // Si les 5 buffles sont bloquées alors fin de la partie
		return 2; // l'Indien gagne
	}

	// On parcourt la grille pour voir la présence d'un buffle dans ce cas le jeu continue
	if(buffles)
	return 0; // Le jeu continue, personne ne gagne

	return 2; // Joueur Indien gagne
}
