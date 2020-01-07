#include "gameplay.h"


int indianMove(IndianDogPositionOldpointer idopptr, IndianDogPositionCurr idpc){
	int c = idopptr->columnI, l = idopptr->lineI, state = 1; //On récupère les coordonnées actuelles de l'Indien avant de le déplacer
	int tmpc = c, tmpl = l; // On créer des variables temporaires (pour éviter de modifier l et c) afin de comparer les anciennes coordonnées avec les nouvelles
	switch(state){
		case 1: // Si on déplace bien l'indien d'une seule case en diagonale haut gauche
		if((--tmpc == idpc.column) && (--tmpl == idpc.line))
		break; // On sort du switch
		tmpc = c; tmpl = l; // On remet les anciennes coordonnées à jour pour tester le cas suivant
		++state; // On passe à l'état suivant
		case 2: // Si on déplace bien l'indien d'une seule case vers le haut
		if((tmpc == idpc.column) && (--tmpl == idpc.line))
		break;
		tmpc = c; tmpl = l;
		++state;
		case 3: // Si on déplace bien l'indien d'une seule case en diagonale haut droite
		if((++tmpc == idpc.column) && (--tmpl == idpc.line))
		break;
		tmpc = c; tmpl = l;
		++state;
		case 4: // Si on déplace bien l'indien d'une seule case vers la gauche
		if((--tmpc == idpc.column) && (tmpl == idpc.line))
		break;
		tmpc = c; tmpl = l;
		++state;
		case 5: // Si on déplace bien l'indien d'une seule case vers la droite
		if((++tmpc == idpc.column) && (tmpl == idpc.line))
		break;
		tmpc = c; tmpl = l;
		++state;
		case 6: // Si on déplace bien l'indien d'une seule case en diagonale bas gauche
		if((--tmpc == idpc.column) && (++tmpl == idpc.line))
		break;
		tmpc = c; tmpl = l;
		++state;
		case 7: // Si on déplace bien l'indien d'une seule case vers le bas
		if((tmpc == idpc.column) && (++tmpl == idpc.line))
		break;
		tmpc = c; tmpl = l;
		++state;
		case 8: // Si on déplace bien l'indien d'une seule case en diagonale bas droite
		if((++tmpc == idpc.column) && (++tmpl == idpc.line))
		break;
		default : return 0; // Si aucun des cas n'est valide on retourne 0
	}
	return 1; // sinon 1
}
