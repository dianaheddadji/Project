#include "gameplay.h"

int indianHere(char grid[COLUMN_NB][LINE_NB], buffaloPosition bp, IndianDogPositionCurrptr idpcptr){
	if(grid[bp.column-1][bp.line-1] != VOID)
	return 0;

	int tmpc = bp.column-1, tmpl = bp.line-1, state = 1;

	switch(state){
		case 1:
		if(grid[--tmpc][--tmpl] == INDIAN){
			idpcptr->column = bp.column-1;
			idpcptr->line = bp.line-1;
			return 0;
		}
		tmpc = bp.column-1; tmpl = bp.line-1;
		++state;
		case 2:
		if(grid[tmpc][--tmpl] == INDIAN){
			idpcptr->column = bp.column-1;
			idpcptr->line = bp.line-1;
			return 0;
		}
		tmpc = bp.column-1; tmpl = bp.line-1;
		++state;
		case 3:
		if(grid[++tmpc][--tmpl] == INDIAN){
			idpcptr->column = bp.column-1;
			idpcptr->line = bp.line-1;
			return 0;
		}
		tmpc = bp.column-1; tmpl = bp.line-1;
		++state;
		case 4:
		if(grid[--tmpc][tmpl] == INDIAN){
			idpcptr->column = bp.column-1;
			idpcptr->line = bp.line-1;
			return 0;
		}
		tmpc = bp.column-1; tmpl = bp.line-1;
		++state;
		case 5:
		if(grid[++tmpc][tmpl] == INDIAN){
			idpcptr->column = bp.column-1;
			idpcptr->line = bp.line-1;
			return 0;
		}
		tmpc = bp.column-1; tmpl = bp.line-1;
		++state;
		case 6:
		if(grid[--tmpc][++tmpl] == INDIAN){
			idpcptr->column = bp.column-1;
			idpcptr->line = bp.line-1;
			return 0;
		}
		tmpc = bp.column-1; tmpl = bp.line-1;
		++state;
		case 7:
		if(grid[tmpc][++tmpl] == INDIAN){
			idpcptr->column = bp.column-1;
			idpcptr->line = bp.line-1;
			return 0;
		}
		tmpc = bp.column-1; tmpl = bp.line-1;
		++state;
		case 8:
		if(grid[++tmpc][++tmpl] == INDIAN){
			idpcptr->column = bp.column-1;
			idpcptr->line = bp.line-1;
			return 0;
		}
		default : return 1;
	}
}
