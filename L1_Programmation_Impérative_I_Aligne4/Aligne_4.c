// Boudjemai Yasmine & Heddadji Diana
// Aligne 4 Projet

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Tableau qui va stocker les piÃšces restantes
int tab2[17];
//Tableau qui rÃ©pertorie toutes les cases
int tab[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

//Tableau qui regroupe toutes les piÃšces
const char* convert[]={"    ","ngar","ngac","ngvr","ngvc","npar","npac","npvr","npvc","bgar","bgac","bgvr","bgvc","bpar","bpac","bpvr","bpvc"};

//Fonction qui vérifie si une case est déjà  prise
int case_occupee(int t[4][4],int l,int c){
	return (t[l][c] != 0);
}

//Fonction qui vÃ©rifie si la grille est entiÃšrement remplie
int grille_remplie(int t[4][4]){
	int i,j;
	for(i=0;i<4;++i)
		for(j=0;j<4;++j)
			if(!case_occupee(t,i,j))
				return 0;
	return 1;
}

//Fonction qui vÃ©rifie si une piÃšce est dÃ©jÃ  choisie
int piece_deja_prise(int t[4][4],int piece){
	int i,j;
	for(i=0;i<4;++i)
		for(j=0;j<4;++j)
			if(t[i][j]==piece)
				return 1;
	return 0;
}

//Fonction qui affiche ce qui reste comme piÃšces aprÃšs chaque coup
void remplit_reste_tab2(int t[4][4]){
	int piece,j;
	for(piece=1,j=0;piece<17;++piece,++j)
		if(!piece_deja_prise(t,piece))
			tab2[j]=piece;
		else
		 	tab2[j]=0;
}

void affiche_reste_tab2(int t[4][4]){
	int i;
	remplit_reste_tab2(t);
	printf("\n  1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16\n");
	printf("_________________________________________________________________________________\n");
	for(i=0;i<16;++i)
		printf("|%s",convert[tab2[i]]);
	printf("|\n---------------------------------------------------------------------------------\n");
}


//Fonction qui remplit la grille
void remplit_grille(int t[4][4],int l,int c,int piece){
	if(!case_occupee(t,l,c) && !piece_deja_prise(t,piece))
		t[l][c]=piece;
}

//ProcÃ©dure qui initialise la grille Ã  zÃ©ro
 void init_grille(int t[4][4]){
     int i,j;
     for(i=0;i<4;++i)
         for(j=0;j<4;++j)
            t[i][j]=0;
}

//ProcÃ©dure qui affiche la grille
 void affiche_grille2(int t[4][4]){
      int i,j;
      printf("\n    0\t  1\t2      3\n");
      for(i=0;i<4;++i){
        printf("  ________________________\n");
        printf("%d",i);
         for(j=0;j<4;++j){
            if(case_occupee(t,i,j))
              printf("|%s ",convert[t[i][j]]);
   	        else
   	          printf("|     ");
   	      }
   	    printf("|\n");
      }
      printf("  ________________________\n");
}


//Fonctions qui dÃ©terminent si l'un des joueurs a gagnÃ©
// en alignant 4 piÃšces ayant une caractÃ©ristique commune

//Fonctions qui vÃ©rifient si un joueur a gagnÃ© (ici avec la caractÃ©ristique la forme: carrÃ© ou ronde)
int grille_horizontale_cr(int t[4][4]){
    int i,j,nbc,nbr;
    nbc=nbr=0;
    for(i=0;i<4;++i){
        for(j=0;j<4;++j){
        	if(t[i][j]==0);
        	else
            	if(t[i][j]%2==0)
               		++nbc;
            	else
               		++nbr;
        }
        if(nbc==4 || nbr==4)
           return 1;
        else
           nbc=nbr=0;
    }
    return 0;
}

int grille_verticale_cr(int t[4][4]){
    int i,j,nbc,nbr;
    for(j=nbc=nbr=0;j<4;++j){
        for(i=0;i<4;++i){
        	if(t[i][j]==0);
        	else
	            if(t[i][j]%2==0)
	               ++nbc;
	            else
	               ++nbr;
        }
        if(nbc==4 || nbr==4)
           return 1;
        else
           nbc=nbr=0;
    }
    return 0;
}

int grille_diagonaled_cr(int t[4][4]){
    int i,j,nbc=0,nbr=0;
    for(i=0,j=3;i<4 && j>=0;++i,--j){
    	if(t[i][j]==0);
        else
	        if(t[i][j]%2==0)
	           ++nbc;
	        else
	           ++nbr;
    }
    if(nbc==4 || nbr==4)
       return 1;
    else
       return 0;
}

int grille_diagonaleg_cr(int t[4][4]){
    int i,nbc=0,nbr=0;
    for(i=0;i<4;++i){
	   	if(t[i][i]==0);
        else
	        if(t[i][i]%2==0)
	           ++nbc;
	        else
	           ++nbr;
    }
    if(nbc==4 || nbr==4)
       return 1;
    else
       return 0;
}

//Fonctions qui vÃ©rifient si un joueur a gagnÃ© (ici avec la caractÃ©ristique couleur: blanche ou noire)
int grille_horizontale_bn(int t[4][4]){
    int i,j,nbb,nbn;
    for(i=nbb=nbn=0;i<4;++i){
        for(j=0;j<4;++j){
        	if(t[i][j]==0);
        	else
	        	if(t[i][j]>0 && t[i][j]<9)
	             ++nbn;
	          else
	             ++nbb;
	      }
        if(nbn==4 || nbb==4)
           return 1;
        else
           nbn=nbb=0;
    }
    return 0;
}

int grille_verticale_bn(int t[4][4]){
    int i,j,nbb,nbn;
    for(j=nbb=nbn=0;j<4;++j){
        for(i=0;i<4;++i){
        	if(t[i][j]==0);
        	else
	            if(t[i][j]>=1 && t[i][j]<=8)
	               ++nbn;
	            else
	               ++nbb;
        }
        if(nbn==4 || nbb==4)
           return 1;
        else
           nbn=nbb=0;
    }
    return 0;
}

int grille_diagonaled_bn(int t[4][4]){
    int i,j,nbb=0,nbn=0;
    for(i=0,j=3;i<4 && j>=0;++i,--j){
    	if(t[i][j]==0);
        else
	        if(t[i][j]>=1 && t[i][j]<=8)
	           ++nbn;
	        else
	           ++nbb;
    }
    if(nbn==4 || nbb==4)
       return 1;
    else
       return 0;
}

int grille_diagonaleg_bn(int t[4][4]){
    int i,nbb=0,nbn=0;
    for(i=0;i<4;++i){
			if(t[i][i]==0);
	        else
		        if(t[i][i]>=1 && t[i][i]<=8)
		           ++nbn;
		        else
		           ++nbb;
    	}
    if(nbn==4 || nbb==4)
   	   return 1;
	else
       return 0;
}

//Fonctions qui vÃ©rifient si un joueur a gagnÃ© (ici avec la caractÃ©ristique taille: grande ou petite)
int grille_horizontale_gp(int t[4][4]){
    int i,j,nbg,nbp;
    for(i=nbg=nbp=0;i<4;++i){
       for(j=0;j<4;++j){
            switch(t[i][j]){
  		        case 0:
                    break;
  	          case 1: 
                   case 2: 
                   case 3: 
                   case 4: 
                   case 9: 
                   case 10: 
                   case 11: 
                   case 12: 
                   		++nbg; 
                   		break;
  	          default: 
                    ++nbp; 
                    break;
    		    }
        }
       if(nbg==4 || nbp==4)
          return 1;
       else
           nbg=nbp=0;
    }
    return 0;
}

int grille_verticale_gp(int t[4][4]){
    int i,j,nbg,nbp;
    for(j=nbg=nbp=0;j<4;++j){
       for(i=0;i<4;++i){
	   	    switch(t[i][j]){
		        case 0:
	    	        break;
	          case 1: 
                case 2: 
                case 3: 
                case 4: 
                case 9: 
                case 10: 
                case 11: 
                case 12: 
	                ++nbg; 
	                break;
	          default:
	                ++nbp; 
	                break;
    		  }
       }
       if(nbg==4 || nbp==4)
          return 1;
       else
           nbg=nbp=0;
    }
    return 0;
}

int grille_diagonaled_gp(int t[4][4]){
    int i,j,nbg=0,nbp=0;
    for(i=0,j=3;i<4 && j>=0;++i,--j){
        switch(t[i][j]){
		        case 0:
	    	        break;
	          case 1: 
                case 2: 
                case 3: 
                case 4: 
                case 9: 
                case 10: 
                case 11: 
                case 12: 
	                ++nbg; 
	                break;
	          default: 
	                ++nbp; 
	                break;
    	  }
    }
    if(nbg==4 || nbp==4)
       return 1;
    else
       return 0;
}

int grille_diagonaleg_gp(int t[4][4]){
    int i,nbg=0,nbp=0;
    for(i=0;i<4;++i){
        switch(t[i][i]){
		        case 0:
	    	        break;
	            case 1: 
                case 2: 
                case 3: 
                case 4: 
                case 9: 
                case 10: 
                case 11: 
                case 12: 
	                ++nbg; 
	                break;
	            default: 
	                ++nbp; 
	                break;
    	  }
    }
    if(nbg==4 || nbp==4)
       return 1;
    else
       return 0;
}

//Fonctions qui vÃ©rifient si un joueur a gagnÃ© (ici avec la caractÃ©ristique type: animal ou vÃ©gÃ©tal)
int grille_horizontale_av(int t[4][4]){
    int i,j,nba,nbv;
    for(i=nba=nbv=0;i<4;++i){
        for(j=0;j<4;++j){
            switch(t[i][j]){
        	      case 0:
	        	        break;
                case 3: 
                    case 4: 
                    case 7: 
                    case 8: 
                    case 11: 
                    case 12: 
                    case 15: 
                    case 16: 
                    ++nbv; 
                    break;
                default: 
                    ++nba; 
                    break;
            }
        }
        if(nbv==4 || nba==4)
            return 1;
        else
            nbv=nba=0;
    }
    return 0;
}

int grille_verticale_av(int t[4][4]){
    int i,j,nba,nbv;
    for(j=nba=nbv=0;j<4;++j){
        for(i=0;i<4;++i){
            switch (t[i][j]){
        		  case 0:
	        	      break;
              case 3: 
                  case 4: 
                  case 7: 
                  case 8: 
                  case 11: 
                  case 12: 
                  case 15: 
                  case 16: 
                  ++nbv; 
                  break;
              default: 
                  ++nba; 
                  break;
            }
         }
         if(nbv==4 || nba==4)
            return 1;
         else
           nbv=nba=0;
    }
    return 0;
}

int grille_diagonaled_av(int t[4][4]){
    int i,j,nba=0,nbv=0;
    for(i=0,j=3;i<4 && j>=0;++i,--j){
        switch (t[i][j]){
        	  case 0:
  	        	  break;
                case 3:
                case 4:
                case 7:
                case 8:
                case 11:
                case 12:
                case 15:
                case 16:
                nbv++;
                break;
            default:
                nba++;
                break;
        }
    }
    if(nba==4 || nbv==4)
       return 1;
    else
       return 0;
}

int grille_diagonaleg_av(int t[4][4]){
    int i,nba=0,nbv=0;
    	for(i=0;i<4;++i){
	        switch (t[i][i]){
	        	  case 0:
		        	   break;
              case 3:
                  case 4:
                  case 7:
                  case 8:
                  case 11:
                  case 12:
                  case 15:
                  case 16:
                  nbv++;
                  break;
              default:
                  nba++;
                  break;
	        }
	    }
	    if(nba==4 || nbv==4)
	       return 1;
	    else
	       return 0;

}

//Fonction qui dÃ©terminent si l'utilisateur a gagnÃ© par l'une des caractÃ©ristques
//Par le type; animal ou vÃ©gÃ©tal
int gagne_av(int t[4][4]){
	int resultat=0;
	resultat+=grille_horizontale_av(t);
	resultat+=grille_verticale_av(t);
	resultat+=grille_diagonaled_av(t);
	resultat+=grille_diagonaleg_av(t);
	if(resultat>=1)
		return 1;
	return 0;
}

//Par la couleur; blanche ou noire
int gagne_bn(int t[4][4]){
	int resultat=0;
	resultat+=grille_horizontale_bn(t);
	resultat+=grille_verticale_bn(t);
	resultat+=grille_diagonaled_bn(t);
	resultat+=grille_diagonaleg_bn(t);
	if(resultat>=1)
		return 1;
	return 0;
}

//Par la forme; carrÃ© ou ronde
int gagne_cr(int t[4][4]){
	int resultat=0;
	resultat+=grille_horizontale_cr(t);
	resultat+=grille_verticale_cr(t);
	resultat+=grille_diagonaled_cr(t);
	resultat+=grille_diagonaleg_cr(t);
	if(resultat>=1)
		return 1;
	return 0;
}

//Par la taille; grande ou petite
int gagne_gp(int t[4][4]){
	int resultat=0;
	resultat+=grille_horizontale_gp(t);
	resultat+=grille_verticale_gp(t);
	resultat+=grille_diagonaled_gp(t);
	resultat+=grille_diagonaleg_gp(t);
	if(resultat>=1)
		return 1;
	return 0;
}

//Fonction qui regroupent les 4 fonctions qui prÃ©cÃšdent
int gameover(int t[4][4]){
	int resultat=0;
	resultat+=gagne_av(t);
	resultat+=gagne_bn(t);
	resultat+=gagne_cr(t);
	resultat+=gagne_gp(t);

	if(resultat>=1)				 //PrÃ©sence d'un alignement
		return 1;
	else
		if(grille_remplie(t)==1) 	 //Match nul
			return 2;
	return 0;				 //La partie n'est pas terminÃ©e
}



//Affichage du contenu de gameover
int affiche_gameover(int t[4][4],int num_joueur){
	switch (gameover(t)){
		case 1: printf("\nLa partie est terminee!\nLe Joueur%d a remporte la partie\n",num_joueur);
				return 1;
				break;

		case 2:	printf("\nMatch nul\n");
				return 1;
				break;

		case 0:	printf("\nC'est au tour du ");
	    	return 0;
			  break;

	  default:
	   		break;
	}
	return 3;
}

void joueur_reel(int t[4][4],int l,int c,int piece,int num_joueur){
	int saisie,car;
    do{
        printf("\nJoueur%d\nSaisir numero de ligne,colonne et numero de piece : \n",num_joueur);
		    saisie=scanf("%d",&l);
		    if(saisie==1){
			    saisie=scanf("%d",&c);
			    if(saisie==1)
				  saisie=scanf("%d",&piece);
		    }while ((car = getchar()) != '\n' && car != EOF); //Vider le buffer
    }while(saisie!=1 || l<0 || l>3 || c<0 || c>3 || case_occupee(t,l,c)==1 || piece<1 || piece>16 || piece_deja_prise(t,piece)==1);
	  remplit_grille(t,l,c,piece);
		affiche_grille2(t);
}

//Fonction pour le joueur automatique
void joueur_automatique(int t[4][4]){
	int l,c,piece;
	srand(time(NULL));
	do{
		l=rand()%4;
		c=rand()%4;
	}while(case_occupee(t,l,c)==1);
	srand(time(NULL));
	do{
		piece=1+ rand()%16;
	}while(piece_deja_prise(t,piece)==1);
	remplit_grille(t,l,c,piece);
	affiche_grille2(t);
}

//Fonctions qui vÃ©rifient si un joueur a gagnÃ© (ici avec la caractÃ©ristique forme: carrÃ© ou ronde)
int horizontale_cr(int t[4][4],int i,int nbp){ //nbp reprÃ©sente le nombre de piÃšces qu'on cherche Ã  aligner
    int j,nbc=0,nbr=0;
    for(j=0;j<4;++j){
    	if(t[i][j]==0);
    	else
        	if(t[i][j]%2==0)
           		++nbc;
        	else
           		++nbr;
    }
    if(nbc==nbp || nbr==nbp)
       return 1;
    else
       return 0;
}

int verticale_cr(int t[4][4],int j,int nbp){
    int i,nbc=0,nbr=0;
    for(i=0;i<4;++i){
    	if(t[i][j]==0);
    	else
          if(t[i][j]%2==0)
              ++nbc;
          else
             ++nbr;
    }
    if(nbc==nbp || nbr==nbp)
       return 1;
    else
       return 0;
}

int diagonaled_cr(int t[4][4],int nbp){
    int i,j,nbc=0,nbr=0;
    for(i=0,j=3;i<4 && j>=0;++i,--j){
    	if(t[i][j]==0);
        else
	        if(t[i][j]%2==0)
	           ++nbc;
	        else
	           ++nbr;
    }
    if(nbc==nbp || nbr==nbp)
       return 1;
    else
       return 0;
}

int diagonaleg_cr(int t[4][4],int nbp){
    int i,nbc=0,nbr=0;
    for(i=0;i<4;++i){
	   	if(t[i][i]==0);
        else
	        if(t[i][i]%2==0)
	           ++nbc;
	        else
	           ++nbr;
    }
    if(nbc==nbp || nbr==nbp)
       return 1;
    else
       return 0;
}

//Fonctions qui vÃ©rifient si un joueur a gagnÃ© (ici avec la caractÃ©ristique couleur: blanche ou noire)
int horizontale_bn(int t[4][4],int i,int nbp){
    int j,nbb=0,nbn=0;
    for(j=0;j<4;++j){
    	if(t[i][j]==0);
    	else
          if(t[i][j]>0 && t[i][j]<=8)
              ++nbn;
          else
              ++nbb;
    }
    if(nbn==nbp || nbb==nbp)
       return 1;
    else
       return 0;
}

int verticale_bn(int t[4][4],int j,int nbp){
    int i,nbb=0,nbn=0;
    for(i=0;i<4;++i){
    	if(t[i][j]==0);
    	else
          if(t[i][j]>=1 && t[i][j]<=8)
              ++nbn;
          else
              ++nbb;
    }
    if(nbn==nbp || nbb==nbp)
       return 1;
    else
       return 0;
}

int diagonaled_bn(int t[4][4],int nbp){
    int i,j,nbb=0,nbn=0;
    for(i=0,j=3;i<4 && j>=0;++i,--j){
    	if(t[i][j]==0);
      else
	        if(t[i][j]>=1 && t[i][j]<=8)
	           ++nbn;
	        else
	           ++nbb;
    }
    if(nbn==nbp || nbb==nbp)
       return 1;
    else
       return 0;
}

int diagonaleg_bn(int t[4][4],int nbp){
    int i,nbb=0,nbn=0;
    for(i=0;i<4;++i){
			if(t[i][i]==0);
	    else
		      if(t[i][i]>=1 && t[i][i]<=8)
		          ++nbn;
		      else
		          ++nbb;
    }
    if(nbn==nbp || nbb==nbp)
   	   return 1;
	  else
       return 0;
}

//Fonctions qui vÃ©rifient si un joueur a gagnÃ© (ici avec la caractÃ©ristique taille: grande ou petite)
int horizontale_gp(int t[4][4],int i,int nbpi){
    int j,nbg=0,nbp=0;
	  for(j=0;j<4;++j)
      switch (t[i][j]){
	      case 0:
    	      break;
        case 1: 
          case 2: 
          case 3: 
          case 4: 
          case 9: 
          case 10: 
          case 11: 
          case 12: 
          ++nbg; 
          break;
        default: 
          ++nbp; 
          break;
		  }
   	if(nbg==nbpi || nbp==nbpi)
      	return 1;
   	else
       	return 0;
}

int verticale_gp(int t[4][4],int j,int nbpi){
    int i,nbg=0,nbp=0;
	  for(i=0;i<4;++i)
   	  switch (t[i][j]){
	      case 0:
    	   	break;
        case 1: 
          case 2: 
          case 3: 
          case 4: 
          case 9: 
          case 10: 
          case 11: 
          case 12: 
          ++nbg; 
          break;
        default: 
          ++nbp; 
          break;
		  }
   	if(nbg==nbpi || nbp==nbpi)
		  return 1;
   	else
      return 0;
}

int diagonaled_gp(int t[4][4],int nbpi){
    int i,j,nbg=0,nbp=0;
    for(i=0,j=3;i<4 && j>=0;++i,--j){
        switch (t[i][j]){
		      case 0:
	    	   	break;
	        case 1: 
            case 2: 
            case 3: 
            case 4: 
            case 9: 
            case 10: 
            case 11: 
            case 12: 
            ++nbg; 
            break;
	        default: 
            ++nbp; 
            break;
    	  }
    }
    if(nbg==nbpi || nbp==nbpi)
      return 1;
    else
      return 0;
}

int diagonaleg_gp(int t[4][4],int nbpi){
    int i,nbg=0,nbp=0;
    for(i=0;i<4;++i){
        switch (t[i][i]){
		      case 0:
	    	    break;
	        case 1: 
            case 2: 
            case 3: 
            case 4: 
            case 9: 
            case 10: 
            case 11: 
            case 12: 
            ++nbg; 
            break;
	        default: 
            ++nbp; 
            break;
    	  }
    }
    if(nbg==nbpi || nbp==nbpi)
       return 1;
    else
       return 0;
}

//Fonctions qui vÃ©rifient si un joueur a gagnÃ© (ici avec la caractÃ©ristique type: animal ou vÃ©gÃ©tal)

int horizontale_av(int t[4][4],int i,int nbp){
    int j,nba=0,nbv=0;
        for(j=0;j<4;++j)
            switch (t[i][j]){
        	      case 0:
	        	      break;
                case 3: 
                  case 4: 
                  case 7: 
                  case 8: 
                  case 11: 
                  case 12: 
                  case 15: 
                  case 16: 
                  ++nbv; 
                  break;
                default: 
                  ++nba; 
                  break;
            }
        if(nbv==nbp || nba==nbp)
            return 1;
        else
            return 0;
}

int verticale_av(int t[4][4],int j,int nbp){
    int i,nba=0,nbv=0;
    for(i=0;i<4;++i)
        switch (t[i][j]){
    		  case 0:
        	   break;
          case 3: 
            case 4: 
            case 7: 
            case 8: 
            case 11: 
            case 12: 
            case 15: 
            case 16: 
            ++nbv; 
            break;
          default: 
            ++nba; 
            break;
        }
    if(nbv==nbp || nba==nbp)
        return 1;
    else
       	return 0;
}

int diagonaled_av(int t[4][4],int nbp){
    int i,j,nba=0,nbv=0;
    for(i=0,j=3;i<4 && j>=0;++i,--j){
        switch (t[i][j]){
        	  case 0:
	        	  break;
            case 3:
              case 4:
              case 7:
              case 8:
              case 11:
              case 12:
              case 15:
              case 16:
              	nbv++;
              	break;
            default:
               	nba++;
               	break;
         }
    }
    if(nba==nbp || nbv==nbp)
      return 1;
    else
      return 0;
}

int diagonaleg_av(int t[4][4],int nbp){
    int i,nba=0,nbv=0;
    	for(i=0;i<4;++i)
	        switch (t[i][i]){
	        	  case 0:
		        	  break;
              case 3: 
                case 4: 
                case 7: 
                case 8: 
                case 11: 
                case 12: 
                case 15: 
                case 16:
                nbv++;
                break;
              default:
                nba++;
                break;
	        }
	    if(nba==nbp || nbv==nbp)
	       return 1;
	    else
	       return 0;
}

int horizontale(int t[4][4],int i,int nbp){
	int resultat=0;
	resultat+=horizontale_av(t,i,nbp);
	resultat+=horizontale_bn(t,i,nbp);
	resultat+=horizontale_cr(t,i,nbp);
	resultat+=horizontale_gp(t,i,nbp);
	if(resultat>=1)
		return 1;
	else
		return 0;
}

int verticale(int t[4][4],int j,int nbp){
	int resultat=0;
	resultat+=verticale_av(t,j,nbp);
	resultat+=verticale_bn(t,j,nbp);
	resultat+=verticale_cr(t,j,nbp);
	resultat+=verticale_gp(t,j,nbp);
	if(resultat>=1)
		return 1;
	else
		return 0;
}

int diagonaled(int t[4][4],int nbp){
	int resultat=0;
	resultat+=diagonaled_av(t,nbp);
	resultat+=diagonaled_bn(t,nbp);
	resultat+=diagonaled_cr(t,nbp);
	resultat+=diagonaled_gp(t,nbp);
	if(resultat>=1)
		return 1;
	else
		return 0;
}

int diagonaleg(int t[4][4],int nbp){
	int resultat=0;
	resultat+=diagonaleg_av(t,nbp);
	resultat+=diagonaleg_bn(t,nbp);
	resultat+=diagonaleg_cr(t,nbp);
	resultat+=diagonaleg_gp(t,nbp);
	if(resultat>=1)
		return 1;
	else
		return 0;
}

int nbre_piece_h(int t[4][4],int i){
  int j,nb=0;
  for(j=0;j<4;++j)
    if(t[i][j]!=0)
      ++nb;
  return nb;
}

int nbre_piece_v(int t[4][4],int j){
  int i,nb=0;
  for(i=0;i<4;++i)
    if(t[i][j]!=0)
      ++nb;
  return nb;
}

int nbre_piece_dd(int t[4][4]){
  int i,j,nb=0;
  for(i=0,j=3;i<4 && j>=0;++i,++j)
    if(t[i][j]!=0)
      ++nb;
  return nb;
}

int nbre_piece_dg(int t[4][4]){
  int i,nb=0;
  for(i=0;i<4;++i)
    if(t[i][i]!=0)
      ++nb;
  return nb;
}

int nbre_piece_pair(int t[4][4]){
    int i,j,nb=0;
    for(i=0;i<4;++i)
    	for(j=0;j<4;++j)
    	    if(t[i][j]>0 && t[i][j]<17)
    	    	++nb;
    if(nb%2==0 && nb!=0)
     	return 1;
    else
    	return 0;
}

void autre_partie_smart(int t[4][4],int num_joueur){
	int i,j,piece,k;
	  for(i=0;i<4;++i){	//PrÃ©sence d'une seule piÃšce sur la rangÃ©e dans toute la grille
	  	for(j=0;j<4;++j){
  		  if(!case_occupee(t,i,j)){
  			  if(nbre_piece_h(t,i)<2 && nbre_piece_v(t,j)<2 && nbre_piece_dd(t)<2 && nbre_piece_dg(t)<2){
  					srand(time(NULL));
  		  		do{
  		  			piece=1+rand()%16;
  					}while(piece_deja_prise(t,piece)==1);
  					remplit_grille(t,i,j,piece);
  					affiche_grille2(t);
  					i=j=4;
  			  }
  		  }
		  }
	  }
	if((num_joueur==1 && nbre_piece_pair(t)) || (num_joueur==2 && !nbre_piece_pair(t))){ //PrÃ©sence de deux piÃšces
	  for(i=0;i<4;++i){
	  	for(j=0;j<4;++j){
  		  if(!case_occupee(t,i,j)){
  			  if(horizontale(t,i,2)==0 && nbre_piece_h(t,i)>=1 && verticale(t,j,2)==0 && nbre_piece_v(t,j)>=1 && diagonaled(t,2)==0 && nbre_piece_dd(t)>=1 && diagonaleg(t,2)==0 && nbre_piece_dg(t)>=1){
  				  srand(time(NULL));
  		  		do{
  		  				piece=1+rand()%16;
  					}while(piece_deja_prise(t,piece)==1);
  					remplit_grille(t,i,j,piece);
  					affiche_grille2(t);
  					i=j=4;
  			  }
  		  }
		  }
    }
  }
	if((num_joueur==1 && nbre_piece_pair(t)) || (num_joueur==2 && !nbre_piece_pair(t))){
	  for(i=0;i<4;++i){
		  for(j=0;j<4;++j){
			  if(!case_occupee(t,i,j)){//Au dessus de 3 piÃšces dont il y a une caractÃ©ristique commune
				  for(k=0;k<16;++k)
				      if(!piece_deja_prise(t,tab2[k])){
  						  t[i][j]=tab2[k];
  						  if(horizontale(t,i,3)==0 && verticale(t,j,3)==0 && diagonaled(t,3)==0 && diagonaleg(t,3)==0){
  						     remplit_grille(t,i,j,t[i][j]);
  						     affiche_grille2(t);
  						     k=16;
  						     i=j=4;
  						  }
  						  else
  						     t[i][j]=0;
					    }
			  }
			}
		}
	}
	if((num_joueur==1 && nbre_piece_pair(t)) || (num_joueur==2 && !nbre_piece_pair(t))){
		joueur_automatique(t);
	}
}

void joueur_smart(int t[4][4],int num_joueur){
     int i=0,j,k;
     remplit_reste_tab2(t); //Tableau qui stock ce qui reste comme piÃšces aprÃšs chaque coup
     while(i<4){		//Le IA commence par vÃ©rifier s'il peut gagner
     	   for(j=0;j<4;++j)
     	       if(case_occupee(t,i,j)==0){  //Case vide
	    	       for(k=0;k<16;++k){
	     	       	   if(piece_deja_prise(t,tab2[k])==0){ //PiÃšce disponible
		     	           t[i][j]=tab2[k];
		     	           if(gameover(t)==1){
		     	              remplit_grille(t,i,j,tab2[k]);
		     	              affiche_grille2(t);
		 		      		      k=16;
		 		                i=j=4;
	 		                }
	 		                else
 		      	            t[i][j]=0;
	 		              }
	 	            }
	            }
 	        ++i;
     } //Si ce n'est pas le cas, il joue autrement
	  if(gameover(t)==0)
	  	autre_partie_smart(t,num_joueur);
}

int main() {
    int t[4][4];
    int i=0,l=0,c=0,piece=0,choix;
    printf("\n\n\t\t\t\t\t\t\tAligne 4\n\n\n");
    printf("Principe du jeu :\n\n");
    printf("Vous avez en votre possession 16 types de pieces.Chacune possede 4 caracteristiques binaires: \nCouleur (noire ou blanche); Taille (grande ou petite); Type (animal ou vegetal); Forme (ronde ou carree).\nLe but est d'aligner 4 pieces ayant une caracteristique commune horizontalement, verticalement ou en diagonale.\nExemple :\n");
    init_grille(t);
    t[0][0]=5;
    t[1][1]=3;
    t[2][2]=1;
    t[3][3]=2;
    t[1][2]=8;
    affiche_grille2(t);
    init_grille(t);
    printf("\nC'est gagne!\nEt ceci par la caracteristique couleur:noire\n\nChoisir un mode de jeu :\n\n1-Utilisateur VS Utilisateur (Multijoueur)\n2-Utilisateur VS Joueur Automatique\n3-Utilisateur VS Ordinateur(IA)\n\n(En mode Spectateur)\n\n4-Joueur Automatique VS Joueur Automatique\n5-Joueur Automatique VS Ordinateur(IA)\n6-Ordinateur VS Ordinateur\nUne autre touche pour quitter le programme\n\n");
    scanf("%d",&choix);
    affiche_grille2(t);
    switch(choix){
    	case 1: //Cas NÂ°1:Joueur rÃ©el VS joueur rÃ©el (Multijoueur)
  	 	  while(i<=16 ){
  		    	affiche_reste_tab2(t);
  			    joueur_reel(t,l,c,piece,1);
  		    	++i;
  		    	if(affiche_gameover(t,1)==0){
      				printf(" Joueur2\n");
      				affiche_reste_tab2(t);
      				joueur_reel(t,l,c,piece,2);
      		   		++i;
      				if(affiche_gameover(t,2)!=0)
      					i=17;
      				else
      					printf(" Joueur1\n");
  			    }
  			    else
  				      i=17;
  		  }
  		 break;

	    case 2:	//Cas NÂ°2: Joueur rÃ©el contre joueur automatique
  	 	 while(i<=16 ){
  	    	affiche_reste_tab2(t);
  			  joueur_reel(t,l,c,piece,1);
  		    ++i;
  		    if(affiche_gameover(t,1)==0){
  			    printf(" Joueur2\n");
  				  joueur_automatique(t);
  		   		++i;
  				  if(affiche_gameover(t,2)!=0)
  					  i=17;
  			    else
  					  printf(" Joueur1\n");
  			  }
  			  else
  				  i=17;
  	    }
        break;

      	case 3: //Cas NÂ°3: Joueur rÃ©el VS IA
	     	 while(i<=16 ){
		    	affiche_reste_tab2(t);
			    joueur_reel(t,l,c,piece,1);
		    	++i;
		    	if(affiche_gameover(t,1)==0){
			      printf(" Joueur2\n");
				    joueur_smart(t,2);
		   		  ++i;
				    if(affiche_gameover(t,2)!=0)
					    i=17;
				    else
					    printf(" Joueur1\n");
          }
			    else
			     i=17;
	       }
         break;

	      case 4: //Cas NÂ°4:Joueur automatique VS joueur automatique
	        while(i<=16 ){
            printf("Joueur Automatique Numero 1\n");
    			  joueur_automatique(t);
    	    	++i;
    	    	if(affiche_gameover(t,1)==0){
              printf("Joueur Automatique Numero 2\n");
    			    joueur_automatique(t);
    		   		++i;
    				  if(affiche_gameover(t,2)!=0)
    					  i=17;
    			  }
    			  else
    				  i=17;
    		  }
	  	    break;

        case 5: //Cas NÂ°5: Joueur automatique VS IA
	     	 while(i<=16 ){
			  	printf("Joueur Automatique\n");
				  joueur_automatique(t);
		    	++i;
		    	if(affiche_gameover(t,1)==0){
			      printf("Joueur IA\n");
				    joueur_smart(t,2);
		   		  ++i;
				    if(affiche_gameover(t,2)!=0)
					    i=17;
			    }
			    else
				    i=17;
	       }
         break;

	      case 6: //Cas NÂ°6 :IA VS IA
		      while(i<=16 ){
			     joueur_smart(t,1);
	    	   ++i;
	    	   if(affiche_gameover(t,1)==0){
  		    	 printf("Joueur IA Numero 2\n");
  				   joueur_smart(t,2);
  		   		 ++i;
  				   if(affiche_gameover(t,2)!=0)
  					    i=17;
  				   else
  					    printf("Joueur IA Numero 1\n");
			     }
			     else
				      i=17;
	        }
	        break;

        default: //return;
		      break;
    }
	return 0;
}
