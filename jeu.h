#ifndef JEU_H
#define JEU_H

void initPlateau(Plateau *plateau);
int score(int etat, Pion pion[][8]);
void convertCase(int caseSelec, Pion pion[][8], int *tourDeJeu);
void casesJouables(Pion pion[][8], int tourDeJeu);

#endif /* JEU_H */ 