#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <string>
using namespace std;

typedef struct Pion{
    int x;
    int y;
    int etat;
}Pion;

typedef struct Element Element;
struct Element{
    Pion pion;
    Element *suivant;
};

typedef struct{
    Element *premier;
}Liste;

typedef struct{
    string nom;
    Liste *pion;
    int nbPion;
}Joueur;

typedef struct{
    Joueur joueur1;
    Joueur joueur2;
    Pion pion[8][8];
}Plateau;

#endif /* STRUCT_H */