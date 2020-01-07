#include "gameplay.h"

int dogHereBis(char grid[COLUMN_NB][LINE_NB], int c, int l, char * dogs){
	int i;
	for(i=0; dogs[i]; ++i)
	if(grid[c][l] == dogs[i])
	return 1;
	return 0;
}


int * dogHERE(char grid[COLUMN_NB][LINE_NB], char * dogs, int * indianNotHereTab, int * dogNotHERETab, buffaloPosition bp){
	//Variables Locales
	int i, k, m, n, c, l, tmpc, tmpl, outsideloop, state, dogNotHERETabReady = 0;

	dogPosition dogCoord;
	for(i=0, bp.column=indianNotHereTab[i]+1; i<COLUMN_NB; ++i, bp.column=indianNotHereTab[i]+1){
		bp.line = searchingBuffaloLine(grid, bp);
		if(grid[bp.column-1][bp.line-2] == BUFFALO){
			c = bp.column-1;
			l = bp.line-1;
			tmpc = c;
			tmpl = l;
			outsideloop = 0;
			state = 1;
			switch(state){
				case 1:
				for(; ((tmpc >= 0) && (tmpl >= 1)); --tmpc, --tmpl)
				if(dogHereBis(grid, tmpc, tmpl, dogs)){
					dogCoord.x = tmpc;
					dogCoord.y = tmpl;
					for(m = c, n = l; ((m!=dogCoord.x) && (n!=dogCoord.y)); --m, --n)
					if(grid[m][n]==VOID){
						outsideloop = 1;
						break;
					}
					if(outsideloop)
					break;
				}
				if(outsideloop)
				break;
				else{
					tmpc = c; tmpl = l;
					++state;
				}
				case 2:
				for(; (tmpl >= 1); --tmpl)
				if(dogHereBis(grid, tmpc, tmpl, dogs)){
					dogCoord.x = tmpc;
					dogCoord.y = tmpl;
					for(m = c, n = l-1; n!=dogCoord.y; --n)
					if(grid[m][n]==VOID){
						outsideloop = 1;
						break;
					}
					if(outsideloop)
					break;
				}
				if(outsideloop)
				break;
				else{
					tmpc = c; tmpl = l;
					++state;
				}
				case 3:
				for(; ((tmpc < COLUMN_NB) && (tmpl >= 1)); ++tmpc, --tmpl)
				if(dogHereBis(grid, tmpc, tmpl, dogs)){
					dogCoord.x = tmpc;
					dogCoord.y = tmpl;
					for(m = c, n = l; ((m!=dogCoord.x) && (n!=dogCoord.y)); ++m, --n)
					if(grid[m][n]==VOID){
						outsideloop = 1;
						break;
					}
					if(outsideloop)
					break;
				}
				if(outsideloop)
				break;
				else{
					tmpc = c; tmpl = l;
					++state;
				}
				case 4:
				for(; tmpc >= 0; --tmpc)
				if(dogHereBis(grid, tmpc, tmpl, dogs)){
					dogCoord.x = tmpc;
					dogCoord.y = tmpl;
					for(m = c, n = l; m!=dogCoord.x; --m)
					if(grid[m][n]==VOID){
						outsideloop = 1;
						break;
					}
					if(outsideloop)
					break;
				}
				if(outsideloop)
				break;
				else{
					tmpc = c; tmpl = l;
					++state;
				}
				case 5:
				for(; tmpc < COLUMN_NB; ++tmpc)
				if(dogHereBis(grid, tmpc, tmpl, dogs)){
					dogCoord.x = tmpc;
					dogCoord.y = tmpl;
					for(m = c, n = l; m!=dogCoord.x; ++m)
					if(grid[m][n]==VOID){
						outsideloop = 1;
						break;
					}
					if(outsideloop)
					break;
				}
				if(outsideloop)
				break;
				else{
					tmpc = c; tmpl = l;
					++state;
				}
				case 6:
				for(; ((tmpc >= 0) && (tmpl < LINE_NB-1)); --tmpc, ++tmpl)
				if(dogHereBis(grid, tmpc, tmpl, dogs)){
					dogCoord.x = tmpc;
					dogCoord.y = tmpl;
					for(m = c, n = l; ((m!=dogCoord.x) && (n!=dogCoord.y)); --m, ++n)
					if(grid[m][n]==VOID){
						outsideloop = 1;
						break;
					}
					if(outsideloop)
					break;
				}
				if(outsideloop)
				break;
				else{
					tmpc = c; tmpl = l;
					++state;
				}
				case 7:
				for(; tmpl < LINE_NB-1; ++tmpl)
				if(dogHereBis(grid, tmpc, tmpl, dogs)){
					dogCoord.x = tmpc;
					dogCoord.y = tmpl;
					for(m = c, n = l; n!=dogCoord.y; ++n)
					if(grid[m][n]==VOID){
						outsideloop = 1;
						break;
					}
					if(outsideloop)
					break;
				}
				if(outsideloop)
				break;
				else{
					tmpc = c; tmpl = l;
					++state;
				}
				case 8:
				for(; ((tmpc < COLUMN_NB) && (tmpl < LINE_NB-1)); ++tmpc, ++tmpl)
				if(dogHereBis(grid, tmpc, tmpl, dogs)){
					dogCoord.x = tmpc;
					dogCoord.y = tmpl;
					for(m = c, n = l; ((m!=dogCoord.x) && (n!=dogCoord.y)); ++m, ++n)
					if(grid[m][n]==VOID){
						outsideloop = 1;
						break;
					}
					if(outsideloop)
					break;
				}
				if(outsideloop)
				break;
				else{
					tmpc = c; tmpl = l;
					++state;
				}
				default :
				for(k=0; k<COLUMN_NB; ++k)
				if(dogNotHERETab[k]==-1){
					dogNotHERETab[k]=c;
					break;
				}
				dogNotHERETabReady = 1;
			}
		}
	}

	if(dogNotHERETabReady)
	return dogNotHERETab;

	return indianNotHereTab;
}
