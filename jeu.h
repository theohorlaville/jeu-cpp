#ifndef JEU_H
#define JEU_H
#include "struct.h"

void initPlateau(Plateau *plateau);
int score(int etat, Pion pion[][8]);
int convertCase(int caseSelec, Pion pion[][8], int *tourDeJeu);
void videCasesJouables(Pion pion[][8]);
int casesJouables(Pion pion[][8], int tourDeJeu);
int calculScore(Pion pion[][8], Liste *lst, int etat);
Liste* remplirListe(Pion pion[][8], Liste *lst, int etat);
void ajoutePion(Liste *lst, Pion *pion);
Liste* initialisationListe();
int scoreJoueur(Element *lst);
void recupJeton(Pion pion[][8],int i, int j, int tourDeJeu);

#endif /* JEU_H */ 