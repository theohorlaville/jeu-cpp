#include <iostream>
#include "struct.h"
#include "jeu.h"
using namespace std;


//On initialise la liste de jeton appartenant a un joueur
Liste* initialisationListe(){
    Liste* liste=(Liste*)malloc(sizeof(*liste));
    Element* elem=(Element*)malloc(sizeof(*elem));
    if(liste==NULL || elem==NULL){
        exit(EXIT_FAILURE);
    }
    elem->pion.x=-1;
    elem->pion.y=-1;
    elem->pion.etat=-1;
    elem->suivant=NULL;
    liste->premier=elem;
    return liste;
}

//On ajoute le pion a la liste 
void ajoutePion(Liste *lst, Pion *pion){
    Element *newElem=(Element*)malloc(sizeof(*newElem));
    if(lst==NULL || newElem==NULL){
        exit(EXIT_FAILURE);
    }
    newElem->pion.x=pion->x;
    newElem->pion.y=pion->y;
    newElem->pion.etat=pion->etat;
    newElem->suivant=lst->premier;
    lst->premier=newElem;
    
}

//On parcour le tableau de pion et on ajoute chaque pion du joueur à la liste 
Liste* remplirListe(Pion pion[][8], Liste *lst, int etat){
    lst->premier=NULL;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(pion[i][j].etat==etat){
                ajoutePion(lst, &pion[i][j]);
            }
        }
    }
    return lst;
}

//On parcour chaque element de la liste pour connaitre le score du joueur 
int scoreJoueur(Element *lst){
    int score=0;
    Element *liste;
    while (lst!=NULL){
        score++;
        liste=lst->suivant;
        free(lst);
        lst=liste;
    }
    return score;
}

int calculScore(Pion pion[][8], Liste *lst, int etat){
    return scoreJoueur(remplirListe(pion,lst,etat)->premier);
}


//initialise le plateau de jeu en début de partie 
void initPlateau(Plateau *plateau){
    //Saisie des noms par l'utilisateur
    cout <<"Entrez le nom d'un joueur : ";
    cin >>plateau->joueur1.nom;
    cout <<"Entrez le nom du deuxieme joueur : ";
    cin >> plateau->joueur2.nom;
    //On associe a chaque pion les coordonées du centre de la case
    int dist_x=37;
    for(int i=0; i<8; i++){
        int dist_y=37;
        for(int j=0;j<8; j++){
            plateau->pion[i][j].x=dist_x;
            plateau->pion[i][j].y=dist_y;
            dist_y=dist_y+75;
            if((i==3  && j==3) || (i==4 && j==4)){//etat 0=blanc, 1=noir, 2=transparent, 3=rouge
                plateau->pion[i][j].etat=0;
            }else if((i==3 && j==4) || (i==4 && j==3)){
                plateau->pion[i][j].etat=1;
            }else{
                plateau->pion[i][j].etat=2;
            }
        }
        dist_x+=75;
    }
    //On calcule le nombre de pion par joueur
    plateau->joueur1.pion=initialisationListe();
    plateau->joueur2.pion=initialisationListe();
    plateau->joueur1.nbPion=calculScore(plateau->pion, plateau->joueur1.pion,0);
    plateau->joueur2.nbPion=calculScore(plateau->pion, plateau->joueur2.pion,1);
}


//pose un pion sur la case que laquelle on a clique, on change de joueur et on vide les cases jouables
int convertCase(int caseSelec, Pion pion[][8], int *tourDeJeu){
    int j=caseSelec/8;
    int i=caseSelec-(8*j);
    if(pion[i][j].etat==3){
        pion[i][j].etat=*tourDeJeu;
        recupJeton(pion, i, j, *tourDeJeu);
        *tourDeJeu=(*tourDeJeu+1)%2;
        
        videCasesJouables(pion);
        return 1;
    }
    return 0;
}

//Parcours le tableau afin de vider les cases précédemment jouables
void videCasesJouables(Pion pion[][8]){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(pion[i][j].etat==3){
                pion[i][j].etat=2;
            }
        }
    }
}

//Parcours les environs de chaque pions de la couleur du joueur pour connaitre les coups jouables
int casesJouables(Pion pion[][8], int tourDeJeu){   
    int retour=1;
    for (int i=0; i<8;i++){
        for(int j=0;j<8;j++){
            if(pion[i][j].etat==tourDeJeu){
               
                int k=1;
                while(pion[i-k][j].etat==(tourDeJeu+1)%2 && i-k>=0){
                    k++;
                }
                if(k!=1 && i-k>=0){
                    if(pion[i-k][j].etat==2){
                        pion[i-k][j].etat=3;
                        retour=0;
                    }
                }
                
                k=1;

                while(pion[i-k][j+k].etat==((tourDeJeu+1)%2) && i-k>=0 && j+k<8){
                    k++;
                }
                if(k!=1 && i-k>=0 && j+k<8){
                    if(pion[i-k][j+k].etat==2){
                        pion[i-k][j+k].etat=3;
                        retour=0;
                    }
                }
                k=1;

                while(pion[i][j+k].etat==(tourDeJeu+1)%2 && j+k<8){
                    k++;
                }
                if(k!=1 && j+k<8){
                    if(pion[i][j+k].etat==2){
                        pion[i][j+k].etat=3;
                        retour=0;
                    }
                }
                
                k=1;

                while(pion[i+k][j+k].etat==(tourDeJeu+1)%2 && i+k<8 && j+k<8){
                    k++;
                }
                if(k!=1 && i+k<8 && j+k<8){
                    if(pion[i+k][j+k].etat==2){
                        pion[i+k][j+k].etat=3;
                        retour=0;
                    }
                k=1;
                }
                

                while(pion[i+k][j].etat==(tourDeJeu+1)%2 && i+k<8){
                    k++;
                }
                if(k!=1 && i+k<8){
                    if(pion[i+k][j].etat==2){
                        pion[i+k][j].etat=3;
                        retour=0;
                    }
                }
                
                k=1;

                while(pion[i+k][j-k].etat==(tourDeJeu+1)%2 && i+k<8 && j-k>=0){
                    k++;
                }
                if(k!=1 && i+k<8 && j-k>=0){
                    if(pion[i+k][j-k].etat==2){
                        pion[i+k][j-k].etat=3;
                        retour=0;
                    }
                }
                
                k=1;

                while(pion[i][j-k].etat==(tourDeJeu+1)%2 && j-k>=0){
                    k++;
                }
                if(k!=1 && j-k>=0){
                    if(pion[i][j-k].etat==2){
                        pion[i][j-k].etat=3;
                        retour=0;
                    }
                }
                
                k=1;

                while(pion[i-k][j-k].etat==(tourDeJeu+1)%2 && i-k>=0 && j-k>=0){
                    k++;
                }
                if(k!=1 && i-k>=0 && j-k>=0){
                    if(pion[i-k][j-k].etat==2){
                        pion[i-k][j-k].etat=3;
                        retour=0;
                    }
                }
                
            }
        }
    }
    return retour;
}

//Parcour les cases autour du pion qui vient d'être posé afin de récuperer ceux qui sont entre ce pion et ceux précédement posés
void recupJeton(Pion pion[][8], int i, int j, int tourDeJeu){
    

    int k=1;
                while(pion[i-k][j].etat==(tourDeJeu+1)%2 && i-k>=0){
                    k++;
                }
                
                if(k!=1 && i-k>=0 && pion[i-k][j].etat==tourDeJeu){
                    for(k; k>=1; k--){
                        pion[i-k][j].etat=tourDeJeu;
                    }
                }
                
                k=1;

                while(pion[i-k][j+k].etat==((tourDeJeu+1)%2) && i-k>=0 && j+k<8){
                    k++;
                }
                if(k!=1 && i-k>=0 && j+k<8 && pion[i-k][j+k].etat==tourDeJeu){
                    for(k; k>=1; k--){
                        pion[i-k][j+k].etat=tourDeJeu;
                    }
                }
                k=1;

                while(pion[i][j+k].etat==(tourDeJeu+1)%2 && j+k<8){
                    k++;
                }
                if(k!=1 && j+k<8 && pion[i][j+k].etat==tourDeJeu){
                    for(k; k>=1; k--){
                         pion[i][j+k].etat=tourDeJeu;
                    }
                }
                       
                
                
                k=1;

                while(pion[i+k][j+k].etat==(tourDeJeu+1)%2 && i+k<8 && j+k<8){
                    k++;
                }
                if(k!=1 && i+k<8 && j+k<8 && pion[i+k][j+k].etat==tourDeJeu){
                    for(k; k>=1; k--){
                         pion[i+k][j+k].etat=tourDeJeu;
                    }
                k=1;
                }
                

                while(pion[i+k][j].etat==(tourDeJeu+1)%2 && i+k<8){
                    k++;
                }
                if(k!=1 && i+k<8 && pion[i+k][j].etat==tourDeJeu){
                    for(k; k>=1; k--){
                        pion[i+k][j].etat=tourDeJeu;
                    }
                }
                
                k=1;

                while(pion[i+k][j-k].etat==(tourDeJeu+1)%2 && i+k<8 && j-k>=0){
                    k++;
                }
                if(k!=1 && i+k<8 && j-k>=0 && pion[i+k][j-k].etat==tourDeJeu){
                    for(k; k>=1; k--){
                        pion[i+k][j-k].etat=tourDeJeu;
                    }
                }
                
                k=1;

                while(pion[i][j-k].etat==(tourDeJeu+1)%2 && j-k>=0){
                    k++;
                }
                if(k!=1 && j-k>=0 && pion[i][j-k].etat==tourDeJeu){
                    for(k; k>=1; k--){
                        pion[i][j-k].etat=tourDeJeu;
                    }
                }
                
                k=1;

                while(pion[i-k][j-k].etat==(tourDeJeu+1)%2 && i-k>=0 && j-k>=0){
                    k++;
                }
                if(k!=1 && i-k>=0 && j-k>=0 && pion[i-k][j-k].etat==tourDeJeu){
                    for(k; k>=1; k--){
                        pion[i-k][j-k].etat=tourDeJeu;
                    }
                        

                }
}