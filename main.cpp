#include <iostream>
#include "struct.h"
#include "jeu.h"
#include "affichage.h"
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;





int main(int argc, char *argv[]){
    Plateau plateau;
    int tourDeJeu=0;
    initPlateau(&plateau);
    
    //Toutes les variables necessaire a la gestion de l'affichage
    SDL_Window *window;
    SDL_Surface *windowSurface = NULL;
    SDL_Surface *imageSurface = NULL;
    SDL_Surface *message = NULL;
    SDL_Surface *message2= NULL;
    SDL_Event windowEvent;
    SDL_Color color;
    TTF_Font *font;
    SDL_PixelFormat *fmt;

    SDL_Rect txt1_rect;
    txt1_rect.x = 650;
    txt1_rect.y = 250;
    txt1_rect.w = 100;
    txt1_rect.h = 50;

    SDL_Rect txt2_rect;
    txt2_rect.x = 650;
    txt2_rect.y = 275;
    txt2_rect.w = 100;
    txt2_rect.h = 50;
    
    SDL_Rect img_rect;
    img_rect.x=0;
    img_rect.y=0;
    img_rect.h=600;
    img_rect.w=600;

    createWindow(&window, &windowSurface); //On creer une fenetre
    initPng(&imageSurface,"plateau.png");//On initialise le png
    if(TTF_Init()<0){ //On initialise le TTF
        cout<<"SDL coul not load TTF! TTF Error :"<< TTF_GetError()<<endl;
      //  return 2;
    };

    modifyTTF(font, &color, &message, plateau.joueur1.nom+" "+to_string(plateau.joueur1.nbPion)); //Affiche le nom et pk pas le score des joueurs
    modifyTTF(font, &color, &message2, plateau.joueur2.nom+" "+to_string(plateau.joueur2.nbPion));
    fmt=imageSurface->format;

    while(true){
        if(SDL_PollEvent(&windowEvent)){
            if( windowEvent.type == SDL_QUIT){ //Ce qu'il se passe lorsqu'on ferme la fenetre
                break;
            }
            
            casesJouables(plateau.pion,tourDeJeu);
            if(windowEvent.type == SDL_MOUSEBUTTONDOWN){ //Action qui se déroule quand on clic
                int caseSelec=retourneCase(windowEvent.button.x, windowEvent.button.y);
                if(windowEvent.button.x <=600 || windowEvent.button.y<=600){
                    cout << "x : "<< windowEvent.button.x << " y "<< windowEvent.button.y<< endl;;
                    convertCase(caseSelec, plateau.pion, &tourDeJeu);
                }

                plateau.joueur1.nbPion=calculScore(plateau.pion,plateau.joueur1.pion,0);
                plateau.joueur2.nbPion=calculScore(plateau.pion,plateau.joueur2.pion,1);
                modifyTTF(font, &color, &message, plateau.joueur1.nom+" "+to_string(plateau.joueur1.nbPion)); //Affiche le nom et pk pas le score des joueurs
                modifyTTF(font, &color, &message2, plateau.joueur2.nom+" "+to_string(plateau.joueur2.nbPion));
                
            }
        }
        //redessine l'image
        draw(&imageSurface, &windowSurface, &img_rect, &message, &message2, &txt1_rect, &txt2_rect, &window, plateau.pion,fmt,tourDeJeu);
        
    }
    
    quit(&message, &message2, &imageSurface, &windowSurface, &window);
    return EXIT_SUCCESS;

}