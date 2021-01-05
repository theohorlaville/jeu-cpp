#include <iostream>
#include "struct.h"
#include "jeu.h"
using namespace std;


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

int scoreJoueur(Element *lst){
    int score=0;
    while (lst!=NULL){
        score++;
        lst=lst->suivant;
    }
    return score;
}

int calculScore(Pion pion[][8], Liste *lst, int etat){
    return scoreJoueur(remplirListe(pion,lst,etat)->premier);
}




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


//pose un pion sur la case que laquelle on a clique
void convertCase(int caseSelec, Pion pion[][8], int *tourDeJeu){
    int j=caseSelec/8;
    cout << "pion "<< caseSelec-(8*j) << " "<< j<< " cliqué etat : "<< pion[caseSelec-(8*j)][j].etat<< endl;
    if(pion[caseSelec-(8*j)][j].etat==3){
        pion[caseSelec-(8*j)][j].etat=*tourDeJeu;

        if(*tourDeJeu==0){
            *tourDeJeu=1;
        }
        else{
            *tourDeJeu=0;
        }
        videCasesJouables(pion);
    }
}

void videCasesJouables(Pion pion[][8]){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(pion[i][j].etat==3){
                pion[i][j].etat=2;
            }
        }
    }
}


void casesJouables(Pion pion[][8], int tourDeJeu){   
    for (int i=0; i<8;i++){
        for(int j=0;j<8;j++){
            if(pion[i][j].etat==tourDeJeu){
               
                int k=1;
                while(pion[i-k][j].etat==(tourDeJeu+1)%2 && i>0){
                    k++;
                }
                if(k!=1){
                    if(pion[i-k][j].etat==2){
                        pion[i-k][j].etat=3;
                    }
                }
                
                k=1;

                while(pion[i-k][j+k].etat==((tourDeJeu+1)%2) && i>0 && j<8){
                    k++;
                }
                if(k!=1){
                    if(pion[i-k][j+k].etat==2){
                        pion[i-k][j+k].etat=3;
                    }
                }
                k=1;

                while(pion[i][j+k].etat==(tourDeJeu+1)%2 && j<8){
                    k++;
                }
                if(k!=1){
                    if(pion[i][j+k].etat==2){
                        pion[i][j+k].etat=3;
                    }
                }
                
                k=1;

                while(pion[i+k][j+k].etat==(tourDeJeu+1)%2 && i<8 && j<8){
                    k++;
                }
                if(k!=1){
                    if(pion[i+k][j+k].etat==2){
                        pion[i+k][j+k].etat=3;
                    }
                k=1;
                }
                

                while(pion[i+k][j].etat==(tourDeJeu+1)%2 && i<8){
                    k++;
                }
                if(k!=1){
                    if(pion[i+k][j].etat==2){
                        pion[i+k][j].etat=3;
                    }
                }
                
                k=1;

                while(pion[i+k][j-k].etat==(tourDeJeu+1)%2 && i<8 && j>0){
                    k++;
                }
                if(k!=1){
                    if(pion[i+k][j-k].etat==2){
                        pion[i+k][j-k].etat=3;
                    }
                }
                
                k=1;

                while(pion[i][j-k].etat==(tourDeJeu+1)%2 && j>0){
                    k++;
                }
                if(k!=1){
                    if(pion[i][j-k].etat==2){
                        pion[i][j-k].etat=3;
                    }
                }
                
                k=1;

                while(pion[i-k][j-k].etat==(tourDeJeu+1)%2 && i>0 && j>0){
                    k++;
                }
                if(k!=1){
                    if(pion[i-k][j-k].etat==2){
                        pion[i-k][j-k].etat=3;
                    }
                }
                
            }
        }
    }
}

