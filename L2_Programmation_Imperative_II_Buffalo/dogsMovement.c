#include "gameplay.h"

int dogsMove(char grid[COLUMN_NB][LINE_NB], char * dogs, IndianDogPositionOldpointer idopptr, IndianDogPositionCurr idpc){
	int c, l, x, y, state = 1;

	switch(idpc.choice){
		case 1:
		c = idopptr->columnB;
		l = idopptr->lineB;
		break;
		case 2:
		c = idopptr->columnA;
		l = idopptr->lineA;
		break;
		case 3:
		c = idopptr->columnC;
		l = idopptr->lineC;
		break;
		default:
		c = idopptr->columnD;
		l = idopptr->lineD;
		break;
	}

	int tmpc = c, tmpl = l; // On créer des variables temporaires (pour éviter de modifier c et l) afin de comparer les anciennes coordonnées avec les nouvelles

	switch(state){
		case 1 :
		for(; ((tmpc >= 0) && (tmpl >= 1)); tmpc--, tmpl--)
		if((tmpc == idpc.column) && (tmpl == idpc.line)){
			for(x = c-1, y = l-1; (x != idpc.column) && (y != idpc.line); --x, --y)
			if(grid[x][y]!=VOID)
			return 0; // En cas d'obstacle
			return 1; // Pas d'obstacle
		}
		tmpc = c; tmpl = l;
		++state;
		case 2 :
		for(; tmpl >= 1; --tmpl)
		if((tmpc == idpc.column) && (tmpl == idpc.line)){
			for(x = c, y = l-1; y != idpc.line; --y)
			if(grid[x][y]!=VOID)
			return 0;
			return 1;
		}
		tmpc = c; tmpl = l;
		++state;
		case 3 :
		for(; (tmpc < COLUMN_NB) && (tmpl >= 1); ++tmpc, --tmpl)
		if((tmpc == idpc.column) && (tmpl == idpc.line)){
			for(x = c+1, y = l-1; ((x != idpc.column) && (y != idpc.line)); ++x, --y)
			if(grid[x][y]!=VOID)
			return 0;
			return 1;
		}
		tmpc = c; tmpl = l;
		++state;
		case 4 :
		for(; tmpc >= 0; --tmpc)
		if((tmpc == idpc.column) && (tmpl == idpc.line)){
			for(x = c-1, y = l; x != idpc.column; --x)
			if(grid[x][y]!=VOID)
			return 0;
			return 1;
		}
		tmpc = c; tmpl = l;
		++state;
		case 5 :
		for(; tmpc < COLUMN_NB; ++tmpc)
		if((tmpc == idpc.column) && (tmpl == idpc.line)){
			for(x = c+1, y = l; x != idpc.column; ++x)
			if(grid[x][y]!=VOID)
			return 0;
			return 1;
		}
		tmpc = c; tmpl = l;
		++state;
		case 6 :
		for(; (tmpc >= 0) && (tmpl < LINE_NB-1); --tmpc, ++tmpl)
		if((tmpc == idpc.column) && (tmpl == idpc.line)){
			for(x = c-1, y = l+1; ((x != idpc.column) && (y != idpc.line)); --x, ++y)
			if(grid[x][y]!=VOID)
			return 0;
			return 1;
		}
		tmpc = c; tmpl = l;
		++state;
		case 7 :
		for(; tmpl < LINE_NB-1; ++tmpl)
		if((tmpc == idpc.column) && (tmpl == idpc.line)){
			for(x = c, y = l+1; y != idpc.line; ++y)
			if(grid[x][y]!=VOID)
			return 0;
			return 1;
		}
		tmpc = c; tmpl = l;
		++state;
		case 8 :
		for(; (tmpc < COLUMN_NB) && (tmpl < LINE_NB-1); ++tmpc, ++tmpl)
		if((tmpc == idpc.column) && (tmpl == idpc.line)){
			for(x = c+1, y = l+1; ((x != idpc.column) && (y != idpc.line)); ++x, ++y)
			if(grid[x][y]!=VOID)
			return 0;
			return 1;
		}
		default : return 0;
	}
	return 1;
}
