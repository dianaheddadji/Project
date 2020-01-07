#include "gameplay.h"


int nearestBuffaloDogs(char grid[COLUMN_NB][LINE_NB], char * dogs, int nearBuffaloColumn, IndianDogPositionOldpointer idopptr, IndianDogPositionCurrptr idpcptr, dogPositionptr dogCoordptr){
	//Variables Locales
	int m, n, tmpc, tmpl,c,l, nearBuffleLine = 0, state = 1;

	nearBuffleLine = searchingBuffaloLineTab(grid, nearBuffaloColumn);
	if((grid[nearBuffaloColumn][nearBuffleLine]!=BUFFALO) || nearBuffleLine==0)
	return 0;

	c = nearBuffaloColumn;
	l = nearBuffleLine+1;
	tmpc = c;
	tmpl = l;

	switch(state){
		case 1:
		for(; ((tmpc >= 0) && (tmpl < LINE_NB-1)); --tmpc, ++tmpl)
		if(dogHereBis(grid, tmpc, tmpl, dogs)){
			dogCoordptr->x = tmpc;
			dogCoordptr->y = tmpl;
			dogCoordptr->c = grid[tmpc][tmpl];
			for(m = c, n = l; ((m!=dogCoordptr->x) && (n!=dogCoordptr->y)); --m, ++n)
			if(grid[m][n]==VOID){
				idpcptr->column = nearBuffaloColumn+1;
				idpcptr->line = nearBuffleLine+2;
				return 1;// On sort du switch
			}
		}
		tmpc = c; tmpl = l;
		++state;
		case 2:
		for(; tmpl < LINE_NB-1; ++tmpl)
		if(dogHereBis(grid, tmpc, tmpl, dogs)){
			dogCoordptr->x = tmpc;
			dogCoordptr->y = tmpl;
			dogCoordptr->c = grid[tmpc][tmpl];
			for(m = c, n = l; n!=dogCoordptr->y; ++n)
			if(grid[m][n]==VOID){
				idpcptr->column = nearBuffaloColumn+1;
				idpcptr->line = nearBuffleLine+2;
				return 1;// On sort du switch
			}
		}
		tmpc = c; tmpl = l;
		++state;
		case 3:
		for(; ((tmpc < COLUMN_NB) && (tmpl < LINE_NB-1)); ++tmpc, ++tmpl)
		if(dogHereBis(grid, tmpc, tmpl, dogs)){
			dogCoordptr->x = tmpc;
			dogCoordptr->y = tmpl;
			dogCoordptr->c = grid[tmpc][tmpl];
			for(m = c, n = l; ((m!=dogCoordptr->x) && (n!=dogCoordptr->y)); ++m, ++n)
			if(grid[m][n]==VOID){
				idpcptr->column = nearBuffaloColumn+1;
				idpcptr->line = nearBuffleLine+2;
				return 1;// On sort du switch
			}
		}
		default :
		dogCoordptr->c = 'I';
		return 0;
	}
	return 0;
}
