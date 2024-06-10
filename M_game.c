#define _VAR_
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "game.h"

int main(int argc,char **argv)
{
  srand(time(NULL));
  
  int window_w=1366,window_h=768;
  SDL_Window *ecran=NULL;
  SDL_Renderer *rendu=NULL;
  
  err_fun(SDL_Init(SDL_INIT_VIDEO&SDL_INIT_TIMER),"Erreur SDL_Init(): %s\n",SDL_GetError());
  err_fun(SDL_CreateWindowAndRenderer(window_w,window_h,SDL_WINDOW_SHOWN,&ecran,&rendu),"Erreur SDL_CreateWindowAndRenderer(): %s\n",SDL_GetError());
  init_cards(rendu);
  start_image(rendu,window_w,window_h);
  game_interf(rendu,window_w,window_h);
  
  SDL_DestroyWindow(ecran);
  SDL_DestroyRenderer(rendu);
  SDL_Quit();
  return EXIT_SUCCESS;
}
