#include "gameplay.h"
#include <stdlib.h>
#include <time.h>

char dogs[4] = {'B','A','C','D'};

void bufferEmpty(){
	int c = 0;
	while(c!='\n' && c!=EOF)
	c=getchar();
}

int main(){
	//On declare un tableau à deux dimensions pour le plateau de jeu (18*27)
	char grid[COLUMN_NB][LINE_NB];

	//déclaration variables locales utiles
	int restart = 0, gameover, err, player, state; //si player est vrai, c'est les buffles qui jouent sinon l'indien
	int c, i, ok, res;
	int mode, random, buffles; // Nb total de buffles
	int bestChoice[COLUMN_NB], dogNotHERETab[COLUMN_NB];
	int nearBuffaloTab[COLUMN_NB];
	int * nearBuffaloTabptr = nearBuffaloTab;
	int * bestChoiceptr = bestChoice;
	char crestart;
	buffaloPosition bp;
	IndianDogPositionCurr idpc;
	IndianDogPositionCurrptr idpcptr = &idpc;
	IndianDogPositionCurr idpcbis;
	IndianDogPositionCurrptr idpcptrbis = &idpcbis;
	IndianDogPositionOld idpo;
	IndianDogPositionOldpointer idopptr = &idpo;
	dogPosition dogCoord;
	dogPositionptr dogCoordptr = &dogCoord;

	do{
		do{
			printf("\n\nBienvenue sur le jeu Buffalo (non il ne s'agit pas du restaurant) mais plutôt d'un jeu paisible codé par deux étudiants débiles afin d'obtenir la satisfaction de M. Bourdin.\n\nLes règles du jeu sont les suivantes :\n\nL'objectif des buffles est d’amener au moins l’un des leurs de l'autre côté du plateau. L'objectif du chef indien est de capturer tous les buffles ou de les bloquer avec ses chiens.\n\nBuffle : O, Indien : I, les chiens : A, B, C, et D.\n\nAppuyer sur n'importe quelle autre touche afin de quitter le programme\n\nMultiplayer : [1]\nPlayer (buffle) vs Ordinateur (Indien) : [2]\nOrdinateur (buffle) vs Player (Indien) : [3]\nOrdinateur vs Ordinateur [4]\n\nChoisir le mode de jeu : ");
			err = scanf("%d", &mode);
			if(!err)
			return 0;
		}while(mode < 1 || mode > 4);

		//Initialisation de la grille + affichage
		initialization(grid, dogs);
		display(grid);
		gameover = 0;
		player = 1;
		buffles = COLUMN_NB;
		idpo.columnI = COLUMN_NB/2;
		idpo.lineI = LINE_NB-2;
		idpo.columnA = (COLUMN_NB/2)-2;
		idpo.lineA = LINE_NB-2;
		idpo.columnB = (COLUMN_NB/2)-1;
		idpo.lineB = LINE_NB-2;
		idpo.columnC = (COLUMN_NB/2)+1;
		idpo.lineC = LINE_NB-2;
		idpo.columnD = (COLUMN_NB/2)+2;
		idpo.lineD = LINE_NB-2;

		//boucle principale
		while(!gameover){
			do{
				if((mode==1) || (mode==2 && player==1) || (mode==3 && player==0)){
					printf("\n\nAppuyer sur n'importe quelle autre touche afin de quitter le programme\n\nAu tour du Joueur : %s\n\n", player == 0 ? "Indien" : "Buffles");
					if(!player){
						do{
							printf("[%d buffles à capturer]\n\nChoisir le pion [1-5] :\n", buffles);
							for(i = 0; dogs[i]; ++i)
							printf("Chien %c n°%d\n", dogs[i], i+1);
							printf("Indien %c n°%d\n\nVotre choix : ", INDIAN, i+1);
							err = scanf("%d", &idpc.choice); //On récupère la valeur de scanf afin de quitter le programme si un symbole est entré
							if(!err)
							return 0;
						}while(idpc.choice < 1 || idpc.choice > 5);

						printf("Choisissez une colonne[1:%d] : ", COLUMN_NB);
						err = scanf("%d", &idpc.column);
						if(!err)
						return 0;
						printf("Choisissez une ligne[1:%d] : ", LINE_NB);
						err = scanf("%d", &idpc.line);
						if(!err)
						return 0;
					}
					else{
						printf("Choisissez le buffle à déplacer [1:%d] : ", COLUMN_NB);
						err = scanf("%d", &bp.column);
						if(!err)
						return 0;
						bp.line = searchingBuffaloLine(grid, bp);
					}
				}

				//IA Buffle
				else if((mode==3 && player==1) || (mode==4 && player==1)){
					for(i=0; i<COLUMN_NB; ++i){
						bestChoice[i] = -1;
						dogNotHERETab[i] = -1;
					}

					for(bp.column=1; bp.column<COLUMN_NB+1; ++bp.column){
						bp.line = searchingBuffaloLine(grid, bp);
						if(grid[bp.column-1][bp.line-2]==BUFFALO)
						if(indianHere(grid, bp, idpcptrbis))
						for(i=0; i<COLUMN_NB; ++i)
						if(bestChoice[i]==-1){
							bestChoice[i] = bp.column-1;
							break;
						}
					}

					bestChoiceptr = dogHERE(grid, dogs, bestChoice, dogNotHERETab, bp);

					random = 1;
					for(c=0, bp.column=bestChoiceptr[c]+1; c<COLUMN_NB; ++c, bp.column=bestChoiceptr[c]+1){
						bp.line = searchingBuffaloLine(grid, bp);
						if(grid[bp.column-1][bp.line-2]==BUFFALO)
						if(grid[bp.column-1][bp.line-1]==VOID){
							random = 0;
							break;
						}
					}

					if(random){
						srand(time(NULL));
						bp.column = rand()%COLUMN_NB+1;
					}
				}
				else{ //IA Indian
					ok = 1;
					nearBuffaloTabptr = nearestBuffalo(grid, nearBuffaloTabptr);
					for(i=0; i<COLUMN_NB; ++i)
					if(nearestBuffaloIndian(grid, nearBuffaloTabptr[i], idopptr, idpcptr)){
						ok=0;
						idpcptr->column=idpcptrbis->column;
						idpcptr->line=idpcptrbis->line;
						break;
					}
					res=0;
					if(ok){
						for(i=0; i<COLUMN_NB; ++i){
							res = nearestBuffaloDogs(grid, dogs, nearBuffaloTabptr[i], idopptr, idpcptr, dogCoordptr);
							if(res){
								switch(dogCoordptr->c){
									case 'A' : idpc.choice=2; break;
									case 'B' : idpc.choice=1; break;
									case 'C' : idpc.choice=3; break;
									case 'D' : idpc.choice=4; break;
									default :	idpc.choice=5; break;
								}
								break;
							}
						}
					}
					state=1;
					if(!res){
						srand(time(NULL));
						idpc.choice = rand()%idpc.choice+1;
						srand(time(NULL));
						switch(state){
							case 1 : idpc.column = rand()%(idopptr->columnB+1)+(idopptr->columnB-1); break;
							case 2 : idpc.column = rand()%(idopptr->columnA+1)+(idopptr->columnA-1); break;
							case 3 : idpc.column = rand()%(idopptr->columnC+1)+(idopptr->columnC-1); break;
							case 4 : idpc.column = rand()%(idopptr->columnD+1)+(idopptr->columnD-1); break;
							default :	idpc.column = rand()%(idopptr->columnI+1)+(idopptr->columnI-1); break;
						}
					}
				}
			}while(set(grid, dogs, &buffles, player, idopptr, idpc, bp) == 0);
			display(grid);

			if(testGameOver(grid, buffles) > 0){
				if(testGameOver(grid, buffles) == 1)
				printf("Joueur Buffles a Gagné !\n\n");
				else
				printf("Joueur Indien a Gagné !\n\n");
				err = 1;
				bufferEmpty();
				while(err){
					printf("Rejouer ? [O\\N]\n");
					err = scanf("%c", &crestart);
					if((crestart == 'O') || (crestart == 'o')){
						bufferEmpty();
						err=0;
						gameover = 1;
						restart = 1;
					}
					else if((crestart == 'N') || (crestart == 'n'))
					return 0;
				}
			}
			player = !player; // On change de joueur
		}
	}while(restart);
}
