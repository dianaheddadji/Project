#include "gameplay.h"

int * nearestBuffalo(char grid[COLUMN_NB][LINE_NB], int * tab){
	int i, c, l, k;

	for(i=0;i<COLUMN_NB;i++)
	tab[i]=-1;

	for(l=LINE_NB-2; l>=0; --l)
	for(c=0; c<COLUMN_NB; ++c)
	if(grid[c][l]==BUFFALO){
		for(k=0;k<11;++k)
		if(tab[k]==-1){
			tab[k]=c;
			break;
		}
	}
	return tab;
}

int searchingBuffaloLineTab(char grid[COLUMN_NB][LINE_NB], int column){
	int l, line;
	for(l=0; l<LINE_NB; ++l)
	if(grid[column][l] == BUFFALO){
		return line = l;
	}
	return -1;
}

int nearestBuffaloIndian(char grid[COLUMN_NB][LINE_NB], int nearBuffaloColumn, IndianDogPositionOldpointer idopptr, IndianDogPositionCurrptr idpcptr){
	int c = idopptr->columnI, l = idopptr->lineI, nearBuffleLine = 0, state = 1;
	int tmpc = c, tmpl = l; // On créer des variables temporaires (pour éviter de modifier les anciennes coordonnées) afin de comparer les anciennes coordonnées avec les nouvelles

	nearBuffleLine = searchingBuffaloLineTab(grid, nearBuffaloColumn);
	if((grid[nearBuffaloColumn][nearBuffleLine]!=BUFFALO) || nearBuffleLine==0)
	return 0;

	switch(state){
		case 1: // Si on déplace bien l'indien d'une seule case en diagonale haut gauche
		if((--tmpc == nearBuffaloColumn) && (--tmpl == nearBuffleLine)){
			idpcptr->column = nearBuffaloColumn+1;
			idpcptr->line = nearBuffleLine+1;
			return 1;// On sort du switch
		}
		tmpc = c; tmpl = l; // On remet les anciennes coordonnées à jour pour tester le cas suivant
		++state; // On passe à l'état suivant
		case 2: // Si on déplace bien l'indien d'une seule case vers le haut
		if((tmpc == nearBuffaloColumn) && (--tmpl == nearBuffleLine)){
			idpcptr->column = nearBuffaloColumn+1;
			idpcptr->line = nearBuffleLine+1;
			return 1;// On sort du switch
		}
		tmpc = c; tmpl = l;
		++state;
		case 3: // Si on déplace bien l'indien d'une seule case en diagonale haut droite
		if((++tmpc == nearBuffaloColumn) && (--tmpl == nearBuffleLine)){
			idpcptr->column = nearBuffaloColumn+1;
			idpcptr->line = nearBuffleLine+1;
			return 1;// On sort du switch
		}
		tmpc = c; tmpl = l;
		++state;
		case 4: // Si on déplace bien l'indien d'une seule case vers la gauche
		if((--tmpc == nearBuffaloColumn) && (tmpl == nearBuffleLine)){
			idpcptr->column = nearBuffaloColumn+1;
			idpcptr->line = nearBuffleLine+1;
			return 1;// On sort du switch
		}
		tmpc = c; tmpl = l;
		++state;
		case 5: // Si on déplace bien l'indien d'une seule case vers la droite
		if((++tmpc == nearBuffaloColumn) && (tmpl == nearBuffleLine)){
			idpcptr->column = nearBuffaloColumn+1;
			idpcptr->line = nearBuffleLine+1;
			return 1;// On sort du switch
		}
		tmpc = c; tmpl = l;
		++state;
		case 6: // Si on déplace bien l'indien d'une seule case en diagonale bas gauche
		if((--tmpc == nearBuffaloColumn) && (++tmpl == nearBuffleLine)){
			idpcptr->column = nearBuffaloColumn+1;
			idpcptr->line = nearBuffleLine+1;
			return 1;// On sort du switch
		}
		tmpc = c; tmpl = l;
		++state;
		case 7: // Si on déplace bien l'indien d'une seule case vers le bas
		if((tmpc == nearBuffaloColumn) && (++tmpl == nearBuffleLine)){
			idpcptr->column = nearBuffaloColumn+1;
			idpcptr->line = nearBuffleLine+1;
			return 1;// On sort du switch
		}
		tmpc = c; tmpl = l;
		++state;
		case 8: // Si on déplace bien l'indien d'une seule case en diagonale bas droite
		if((++tmpc == nearBuffaloColumn) && (++tmpl == nearBuffleLine)){
			idpcptr->column = nearBuffaloColumn+1;
			idpcptr->line = nearBuffleLine+1;
			return 1;// On sort du switch
		}
		default : return 0; // Si aucun des cas n'est valide on retourne 0
	}
}
