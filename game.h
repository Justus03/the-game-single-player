#ifndef _GAME_H
#define _GAME_H

#define TAILLE 20
typedef struct
{
  int nbr;
  SDL_Texture *carte;
}cards;

typedef struct
{
  char name[TAILLE];
  int nbr_joueur;
}team;

typedef struct
{
  char name[TAILLE];
  cards jeu[8];
  team equip;
  int playing_time;
}player;

#ifndef _VAR_
#define _VAR_
#include <time.h>
static cards cartes[101]; // definition des cartes
static cards tmp_cartes[98]; // pile de cartes
static cards carte_prec[4]={{100,NULL},{1,NULL},{100,NULL},{1,NULL}}; // dernières cartes posées
static cards pile[90];
static cards hand_set[8];
#endif

void start_image(SDL_Renderer *rendu,const int window_w,const int window_h);
void game_interf(SDL_Renderer *rendu,const int window_w,const int window_h);
void game_menu(SDL_Renderer *rendu,SDL_Rect menu,SDL_Rect field,SDL_Event *event,int *bool);
void refresh_menu(SDL_Renderer *rendu,SDL_Rect menu,SDL_Rect *rect_tab,SDL_Rect field);
void refresh_curs(SDL_Renderer *rendu,SDL_Rect rect_tab,SDL_Rect rect_curs);

void refresh_hand(SDL_Renderer *rendu,SDL_Rect *hand_rect,SDL_Rect zone,int indice);
int replace_hand(int indice);
void clear_hand(SDL_Renderer *rendu,cards hand);
void refresh_pose(SDL_Renderer *rendu,SDL_Rect *base,int indice,int val);
void game_field(SDL_Renderer *rendu,SDL_Rect field);
void refresh_field(SDL_Renderer *rendu,SDL_Rect *tab_base,SDL_Rect *tab_depot,SDL_Rect field,SDL_Rect pioche);

void clear_field(SDL_Renderer *rendu,SDL_Rect field);
void init_cards(SDL_Renderer *rendu);
void init_0cards();

void loadHelp(SDL_Renderer *rendu,char *path1,char *path2,SDL_Texture **T_text1,SDL_Texture **T_text2);
SDL_Texture *loadtext(SDL_Renderer *rendu,const char path[],char *mot,int taille,SDL_Color color);
void showHelp(SDL_Renderer *rendu,SDL_Texture *T_text1,SDL_Texture *T_text2,SDL_Rect field);
void setColor(SDL_Renderer *renderer, SDL_Color color);
SDL_Texture *loadImage(const char path[],SDL_Renderer *renderer);
void err(void *element,char *word,const char *fun_err);
void err_fun(int output,char *word,const char *fun_err);
/*
int select_random();
void init_main();
void manage_tab(int indice);
*/
#endif
