#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "affichage.h"
#include "struct.h"
using namespace std;

//Creer la fenetre aux bonnes dimension et rempli la windowSurface
void createWindow(SDL_Window **window, SDL_Surface **windowSurface){ 
    if (SDL_Init(SDL_INIT_EVERYTHING)<0){
        cout<< "SDL could not initialize! SDL Error: " << SDL_GetError() <<endl;
       // return EXIT_FAILURE;
    } 
    *window = SDL_CreateWindow("Projet Othello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if(*window == NULL){
        cout << "Coul not create window: " << SDL_GetError() << endl;
        //return EXIT_FAILURE;
    }
    *windowSurface= SDL_GetWindowSurface(*window);
}


//Initialise l'image passee en argument
void initPng(SDL_Surface **imageSurface, string pngName){  

    if( !(IMG_Init(IMG_INIT_PNG))){
        cout << "Could not initialize SDL_image :" << IMG_GetError() << endl;
        //return 1;
    } 
     char *img=new char[pngName.length()+1];
     strcpy(img,pngName.c_str());
    
    *imageSurface= IMG_Load(img);
    delete [] img;
    
    if(*imageSurface == NULL){
        cout<< "SDL could not load Image! SDL Error :"<< SDL_GetError()<<endl;
    }
}

//Modifie le texte dans la SDL_Surface message
void modifyTTF(TTF_Font *font, SDL_Color *color, SDL_Surface **message, string texte){
    
    color->r=255;
    color->g=255;
    color->b=255;
    char *msg= new char[texte.length()+1];
    strcpy(msg,texte.c_str());
    font= TTF_OpenFont("Times.ttc", 20);
    *message= TTF_RenderUTF8_Solid(font, msg, *color);
    delete []msg;
}

//Redessine sur la surface
void draw(SDL_Surface **imageSurface, SDL_Surface **windowSurface, SDL_Rect *img_rect, SDL_Surface **message, SDL_Surface **message2, SDL_Rect *txt1_rect, SDL_Rect *txt2_rect, SDL_Window **window, Pion pion[][8],SDL_PixelFormat *fmt,int tourDeJeu){
    
    
    Uint32 blanc= SDL_MapRGB(fmt,255,255,255);
    Uint32 noir=SDL_MapRGB(fmt,0,0,0);
    Uint32 rouge=SDL_MapRGB(fmt,255,0,0);
    Uint32 couleurFond=SDL_MapRGB(fmt,214, 231, 242);
    
    if(tourDeJeu==0){
        disque(700, 100, 30, blanc, *windowSurface);
    }else if(tourDeJeu ==1){
        disque(700, 100, 30, noir, *windowSurface);
    }
    for (int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(pion[i][j].etat==0){
                disque(pion[i][j].x, pion[i][j].y, 30, blanc, *imageSurface);
            }else if(pion[i][j].etat==1){
                disque(pion[i][j].x, pion[i][j].y, 30, noir, *imageSurface);
                
            }else if(pion[i][j].etat==3){
                disque(pion[i][j].x, pion[i][j].y, 30, rouge, *imageSurface);

            }else if(pion[i][j].etat==2){
                disque(pion[i][j].x, pion[i][j].y, 30, couleurFond, *imageSurface);
            }
        }
    }
    
    SDL_BlitSurface( *imageSurface, NULL, *windowSurface, img_rect); 
    SDL_BlitSurface( *message, NULL, *windowSurface, txt1_rect);
    SDL_BlitSurface( *message2, NULL, *windowSurface, txt2_rect);
    
    SDL_UpdateWindowSurface(*window);
}

//Libere toute les surface et quitte la SDL
void quit(SDL_Surface **message, SDL_Surface **message2, SDL_Surface **imageSurface, SDL_Surface **windowSurface,SDL_Window **window ){
    SDL_FreeSurface(*message);
    SDL_FreeSurface(*message2);
    SDL_FreeSurface(*imageSurface);
    SDL_FreeSurface(*windowSurface);
    SDL_DestroyWindow(*window);
    SDL_Quit( );

}

void ligneHorizontale(int x, int y, int w, Uint32 coul, SDL_Surface *window){
  SDL_Rect r;
 
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;
 
  SDL_FillRect(window, &r, coul);
}


//Dessine les pions, cx,cy sont les coordonnees du centre
void disque(int cx, int cy, int rayon, int coul, SDL_Surface *window)
{
  int d, y, x;
 
  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;
 
  while (y >= x) {
    ligneHorizontale(cx - x, cy - y, 2 * x + 1, coul, window);
    ligneHorizontale(cx - x, cy + y, 2 * x + 1, coul, window);
    ligneHorizontale(cx - y, cy - x, 2 * y + 1, coul, window);
    ligneHorizontale(cx - y, cy + x, 2 * y + 1, coul, window);
 
    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }
 
    x++;
  }
}


int retourneCase(int coordX, int coordY){
    if(coordX >600 || coordY>600){
        return -1;
    }
    for (int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(coordX >=(i*75) && coordX <(i+1)*75){
                if(coordY>=j*75 && coordY<(j+1)*75){
                    return j*8+i;
                }
            }
        }
    }
    return -2;
}
