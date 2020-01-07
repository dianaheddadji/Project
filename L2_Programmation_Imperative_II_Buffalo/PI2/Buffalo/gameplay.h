#ifndef GAME_H___
#define GAME_H___
#include "display.h"


//Les structures
struct buffaloPosition{
	int column;
	int line;
};
typedef struct buffaloPosition buffaloPosition;

struct IndianDogPositionOld{
	int columnI;
	int lineI;
	int columnA;
	int lineA;
	int columnB;
	int lineB;
	int columnC;
	int lineC;
	int columnD;
	int lineD;
};
typedef struct IndianDogPositionOld IndianDogPositionOld;
typedef struct IndianDogPositionOld * IndianDogPositionOldpointer;

struct IndianDogPositionCurr{
	int choice;
	int column;
	int line;
};
typedef struct IndianDogPositionCurr IndianDogPositionCurr;
typedef struct IndianDogPositionCurr * IndianDogPositionCurrptr;

struct dogPosition{
	int x;
	int y;
	char c;
};
typedef struct dogPosition dogPosition;
typedef struct dogPosition * dogPositionptr;


//Prototypes des fonctions pour l'implémentation du jeu
int set(char [COLUMN_NB][LINE_NB], char * dogs, int * buffles, int player, IndianDogPositionOldpointer idopptr, IndianDogPositionCurr idpc, buffaloPosition bp); 
//Set : Tente de placer la pièce dans une case donnée
int searchingBuffaloLine(char grid[COLUMN_NB][LINE_NB], buffaloPosition bp);
//searchingBuffaloLine : Cherche la ligne correspondante à la colonne dans lequel se trouve le buffle
int searchingBuffaloLineTab(char grid[COLUMN_NB][LINE_NB], int i);
//searchingBuffaloLineTab : Même chose mais version tableau
int indianMove(IndianDogPositionOldpointer idopptr, IndianDogPositionCurr idpc); 
//indianMove : Gestion des déplacements de l'indien
int dogsMove(char grid[COLUMN_NB][LINE_NB], char * dogs, IndianDogPositionOldpointer idopptr, IndianDogPositionCurr idpc);
//dogsMove : Gestion des déplacements des chiens
int indianHere(char grid[COLUMN_NB][LINE_NB], buffaloPosition bp, IndianDogPositionCurrptr idpcptr);
//indianHere : Indique si l'indien est autour d'un buffle donné
int * dogHERE(char grid[COLUMN_NB][LINE_NB], char * dogs, int * indianNotHereTab, int * dogNotHERETab, buffaloPosition bp);
//dogHERE : Renvoie soit un tableau de buffles modifié; (dogNotHERETab) pour lesquelles chaque buffle ne se trouve, ni autour de l'indien, ni dans l'une des trajectoires d'un des chiens
//soit un tableau non modifié; indianNotHereTab dans lequel chaque buffle ne se trouve autour de l'indien mais qui peut se trouver dans l'une des trajectoires d'un des chiens
int dogHereBis(char grid[COLUMN_NB][LINE_NB], int tmpc, int tmpl, char * dogs);
//dogHereBis : Teste si un buffle se trouve dans la trajectoire d'un des chiens
int * disorder(int * tab);
//disorder : Renvoie un tableau dans l'ordre décroissant
int testGameOver(char grid[COLUMN_NB][LINE_NB], int buffles);
//testGameOver : Détermine si le jeu est terminé

int * nearestBuffalo(char grid[COLUMN_NB][LINE_NB], int * tab);
int nearestBuffaloIndian(char grid[COLUMN_NB][LINE_NB], int nearBuffaloColumn, IndianDogPositionOldpointer idopptr, IndianDogPositionCurrptr idpc);
int nearestBuffaloDogs(char grid[COLUMN_NB][LINE_NB], char * dogs, int nearBuffaloColumn, IndianDogPositionOldpointer idopptr, IndianDogPositionCurrptr idpcptr, dogPositionptr dogCoordptr);

#endif
