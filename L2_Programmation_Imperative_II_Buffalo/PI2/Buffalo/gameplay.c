#include "gameplay.h"

int searchingBuffaloLine(char grid[COLUMN_NB][LINE_NB], buffaloPosition bp){
	int i;
	--bp.column;
	for(i=0; i<LINE_NB; ++i)
	if(grid[bp.column][i] == BUFFALO){
		++bp.column;
		return bp.line = i+2;
	}
	return -1;
}

//fonction qui test si une case est libre
int set(char grid[COLUMN_NB][LINE_NB], char * dogs, int * buffles, int player, IndianDogPositionOldpointer idopptr, IndianDogPositionCurr idpc, buffaloPosition bp){
	//Déclaration des variables locales
	int MoveErr;

	bp.column -= 1; //on decremente pour obtenir un nombre compris entre 0 et 10 (pour les 11 colonnes)
	bp.line -= 1; //même chose pour la ligne

	idpc.column -= 1; //on decremente pour obtenir un nombre compris entre 0 et 10 (pour les 11 colonnes)
	idpc.line -= 1; //même chose pour la ligne

	if(player){
		if(bp.column < 0 || bp.column >= COLUMN_NB || bp.line < 0 || bp.line >= LINE_NB) //en cas de débordement
		return 0;
		if((grid[bp.column][bp.line] == VOID)){ //On vérifie si la case suivante est vide
			grid[bp.column][bp.line-1] = VOID;
			grid[bp.column][bp.line] = BUFFALO;
			return 1;
		}
	}

	if(!player){
		if(idpc.column < 0 || idpc.column >= COLUMN_NB || idpc.line < 0 || idpc.line >= LINE_NB)
		return 0;
		if((grid[idpc.column][idpc.line]==VOID) || ((idpc.choice == 5) && (grid[idpc.column][idpc.line]==BUFFALO))){
			if(idpc.line == 7 || idpc.line == 0) // Pour que l'Indien ou les chiens ne se déplacent pas sur la première ou la troisième ligne
			return 0;
			switch(idpc.choice){
				case 1 : // Chien B
				MoveErr = dogsMove(grid, dogs, idopptr, idpc);
				if(!MoveErr)
				return 0;
				grid[idopptr->columnB][idopptr->lineB] = VOID;
				grid[idpc.column][idpc.line] = dogs[0];
				idopptr->columnB = idpc.column;
				idopptr->lineB = idpc.line;
				return 1;
				case 2 : // Chien A
				MoveErr = dogsMove(grid, dogs, idopptr, idpc);
				if(!MoveErr)
				return 0;
				grid[idopptr->columnA][idopptr->lineA] = VOID;
				grid[idpc.column][idpc.line] = dogs[1];
				idopptr->columnA = idpc.column;
				idopptr->lineA = idpc.line;
				return 1;
				case 3 : // Chien C
				MoveErr = dogsMove(grid, dogs, idopptr, idpc);
				if(!MoveErr)
				return 0;
				grid[idopptr->columnC][idopptr->lineC] = VOID;
				grid[idpc.column][idpc.line] = dogs[2];
				idopptr->columnC = idpc.column;
				idopptr->lineC = idpc.line;
				return 1;
				case 4 : // Chien D
				MoveErr = dogsMove(grid, dogs, idopptr, idpc);
				if(!MoveErr)
				return 0;
				grid[idopptr->columnD][idopptr->lineD] = VOID;
				grid[idpc.column][idpc.line] = dogs[3];
				idopptr->columnD = idpc.column;
				idopptr->lineD = idpc.line;
				return 1;
				case 5 : // Indien I
				if(grid[idpc.column][idpc.line]==BUFFALO)
				--*buffles;
				MoveErr = indianMove(idopptr, idpc);
				if(!MoveErr)
				return 0;
				grid[idopptr->columnI][idopptr->lineI] = VOID;
				grid[idpc.column][idpc.line] = INDIAN;
				idopptr->columnI = idpc.column;
				idopptr->lineI = idpc.line;
				return 1;
			}
		}
	}
	return 0; //la case est occupée
}
