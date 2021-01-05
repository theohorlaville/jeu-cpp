#ifndef JEU_H
#define JEU_H

void initPlateau(Plateau *plateau);
int score(int etat, Pion pion[][8]);
void convertCase(int caseSelec, Pion pion[][8], int *tourDeJeu);
void videCasesJouables(Pion pion[][8]);
void casesJouables(Pion pion[][8], int tourDeJeu);
int calculScore(Pion pion[][8], Liste *lst, int etat);
Liste* remplirListe(Pion pion[][8], Liste *lst, int etat);
void ajoutePion(Liste *lst, Pion *pion);
Liste* initialisationListe();
int scoreJoueur(Element *lst);

#endif /* JEU_H */ 