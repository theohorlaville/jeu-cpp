#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <string>
using namespace std;

typedef struct{
    int x;
    int y;
    int etat;
}Pion;

typedef struct{
    Pion pion;
    Pion *suivant;
}ListePion;

typedef struct{
    string nom;
    Pion *pion;
    int nbPion;
}Joueur;

typedef struct{
    Joueur joueur1;
    Joueur joueur2;
    Pion pion[8][8];
}Plateau;

#endif /* STRUCT_H */