#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "struct.h"
using namespace std;

const int WIDTH = 800, HEIGHT =600;

void createWindow(SDL_Window **window, SDL_Surface **windowSurface);
void initPng(SDL_Surface **imageSurface, string pngName);
void modifyTTF(TTF_Font *font, SDL_Color *color, SDL_Surface **message, string texte);
void draw(SDL_Surface **imageSurface, SDL_Surface **windowSurface, SDL_Rect *img_rect, SDL_Surface **message, SDL_Surface **message2, SDL_Rect *txt1_rect, SDL_Rect *txt2_rect, SDL_Window **window, Pion pion[][8],SDL_PixelFormat *fmt,int tourDeJeu);
void quit(SDL_Surface **message, SDL_Surface **message2, SDL_Surface **imageSurface, SDL_Surface **windowSurface,SDL_Window **window);
void disque(int cx, int cy, int rayon, int coul, SDL_Surface *window);
void ligneHorizontale(int x, int y, int w, Uint32 coul, SDL_Surface *window);
int retourneCase(int coordX, int coordY);

#endif /* AFFICHAGE_H */