#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"

void err(void *element,char *word,const char *fun_err)
{
  if(!element)
    {
      fprintf(stderr,word,fun_err);
      exit(EXIT_FAILURE);
    }
}

void err_fun(int output,char *word,const char *fun_err)
{
  if(output)
    fprintf(stderr,word,fun_err);
}

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
  SDL_Surface *tmp = NULL;
  SDL_Texture *texture = NULL;
  
  tmp = SDL_LoadBMP(path);
  SDL_SetColorKey(tmp,SDL_TRUE,SDL_MapRGB(tmp->format,0,255,0));
  err(tmp,"Erreur SDL_LoadBMP : %s",SDL_GetError());
  texture = SDL_CreateTextureFromSurface(renderer, tmp);
  err(texture,"Erreur SDL_CreateTextureFromSurface: %s\n",SDL_GetError());
  SDL_FreeSurface(tmp);
  
  return texture;
}

void setColor(SDL_Renderer *renderer, SDL_Color color)
{
  static int bool=1;
  
  err_fun(SDL_SetRenderDrawColor(renderer, color.r, color.g,color.b, color.a),"Erreur SDL_SetRenderDrawColor(): %s\n",SDL_GetError());
  if(bool)
    {
      err_fun(SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND),"Erreur SDL_SetRenderBlendMode: %s\n",SDL_GetError());
      bool=0;
    }
}

void init_cards(SDL_Renderer *rendu)
{
  cards tmp;
  int max=98,val=0;
  int caract=0,i=0,j=0;
  FILE *file=NULL;
  char path[TAILLE]="";

  file=fopen("files/cards_init.dat","r");
  err(file,"Erreur lors de l'ouverture du fichier: %s\n",SDL_GetError());
  caract=fgetc(file);
  for(j=0;caract!=EOF;j++)
    {
      for(i=0;caract!='\n';i++)
	{
	  path[i]=caract;
	  caract=fgetc(file);
	  if(caract=='\n')
	    path[i+1]='\0';
	}
      if(j==0)
	{
	  cartes[j].nbr=-1;
	  cartes[j].carte=loadImage(path,rendu);
	}
      else
	{
	  cartes[j].nbr=j-1;
	  cartes[j].carte=loadImage(path,rendu);
	}
      caract=fgetc(file);
    }
  for(i=3,j=0;i<101;i++,j++)
    tmp_cartes[j]=cartes[i];
  for(i=0;i<8;max--,i++)
    {
      val=rand()%max;
      hand_set[i]=tmp_cartes[val];
      if(val>=0&&val<max-1)
	{
	  tmp=tmp_cartes[val];
	  tmp_cartes[val]=tmp_cartes[max-1];
	  tmp_cartes[max-1]=tmp;
	}
    }
    for(i=0;i<90;max--,i++)
    {
      val=rand()%max;
      pile[i]=tmp_cartes[val];
      if(val>=0&&val<max-1)
	{
	  tmp=tmp_cartes[val];
	  tmp_cartes[val]=tmp_cartes[max-1];
	  tmp_cartes[max-1]=tmp;
	}
    }
  
  fclose(file);
}

void loadHelp(SDL_Renderer *rendu,char *path1,char *path2,SDL_Texture **T_text1,SDL_Texture **T_text2)
{

  *T_text1=loadImage(path1,rendu);
  *T_text2=loadImage(path2,rendu);
  
}

SDL_Texture *loadtext(SDL_Renderer *rendu,const char path[],char *mot,int taille,SDL_Color color)
{
  TTF_Font *police;
  SDL_Texture *textu;
  SDL_Surface *text;

  TTF_Init();
  
  police=TTF_OpenFont(path,taille);
  err(police,"Erreur TTF_OpenFont: %s\n",TTF_GetError());
  
  text=TTF_RenderText_Blended(police,mot,color);
  err(text,"Erreur SDL_RenderText_Blended: %s\n",SDL_GetError());
  
  textu=SDL_CreateTextureFromSurface(rendu,text);
  err(textu,"Erreur SDL_CreateTextureFromSurface: %s\n",SDL_GetError());

  SDL_FreeSurface(text);
  TTF_CloseFont(police);
  TTF_Quit();
  return textu;
}

void start_image(SDL_Renderer *rendu,const int window_w,const int window_h)
{
  TTF_Font *police=NULL;
  SDL_Surface *text=NULL;
  SDL_Rect position={0};
  SDL_Color red={123,0,27,255},black={0,0,0,255},game_theme={117,117,117,255};
  SDL_Texture *T_text=NULL;
  
  err_fun(TTF_Init(),"Error TTF_Init(): %s\n",TTF_GetError());
  
  police=TTF_OpenFont("files/SHOWG.TTF",164);
  err(police,"Erreur TTF_OpenFont(showg.ttf): %s\n",TTF_GetError());
  
  text=TTF_RenderText_Blended(police,"The Game",black);
  err(text,"Erreur SDL_RenderText_Blended(text): %s\n",SDL_GetError());
  
  T_text=SDL_CreateTextureFromSurface(rendu,text);
  err(T_text,"Erreur SDL_CreateTextureFromSurface(T_text): %s\n",SDL_GetError());
  
  SDL_FreeSurface(text);
  SDL_QueryTexture(T_text,NULL,NULL,&position.w,&position.h);
  position.x=window_w/2-position.w/2;
  position.y=window_h/2-position.h/2;
  err_fun(SDL_SetRenderDrawColor(rendu,red.r,red.g,red.b,red.a),"Erreur SDL_SetRenderDrawColor(): %s\n",SDL_GetError());
  err_fun(SDL_RenderClear(rendu),"Erreur SDL_RenderClear(): %s\n",SDL_GetError());
  err_fun(SDL_RenderCopy(rendu,T_text,NULL,&position),"Erreur SDL_RenderCopy(): %s\n",SDL_GetError());
  SDL_RenderPresent(rendu);
  SDL_Delay(3000);
  err_fun(SDL_SetRenderDrawColor(rendu,game_theme.r,game_theme.g,game_theme.b,game_theme.a),"Erreur SDL_SetRenderDrawColor(game_theme): %s\n",SDL_GetError());
  TTF_CloseFont(police);
  
  police=TTF_OpenFont("files/SHOWG.TTF",36);
  err(police,"Erreur TTF_OpenFont(showg.ttf): %s\n",TTF_GetError());

  text=TTF_RenderText_Blended(police,"Appuyer sur une touche pour continuer",black);
  err(text,"Erreur SDL_RenderText_Blended(text): %s\n",SDL_GetError());
  
  T_text=SDL_CreateTextureFromSurface(rendu,text);
  err(T_text,"Erreur SDL_CreateTextureFromSurface(T_text): %s\n",SDL_GetError());
  
  SDL_FreeSurface(text);
  SDL_QueryTexture(T_text,NULL,NULL,&position.w,&position.h);
  position.x=window_w/2-position.w/2;
  position.y=window_h/2-position.h/2;
  err_fun(SDL_RenderClear(rendu),"Erreur SDL_RenderClear(): %s\n",SDL_GetError());
  err_fun(SDL_RenderCopy(rendu,T_text,NULL,&position),"Erreur SDL_RenderCopy(): %s\n",SDL_GetError());
  SDL_RenderPresent(rendu);
  
  SDL_DestroyTexture(T_text);
  TTF_CloseFont(police);
  TTF_Quit();
}

void game_menu(SDL_Renderer *rendu,SDL_Rect menu,SDL_Rect field,SDL_Event *event,int *bool)
{
  int i=0;
  SDL_Rect rect_tab[5]={{0}},rect_curs[5]={{0}},rect_help1={0},rect_help2={0};
  SDL_Texture *help1=NULL,*help2=NULL;
  SDL_Color orange={255,140,0,255},red={123,0,27,255};
  
  refresh_menu(rendu,menu,rect_tab,field);
  SDL_Delay(1);
  refresh_curs(rendu,rect_tab[i],rect_curs[i]);
  clear_field(rendu,field);
  
  while(*bool)
    {
      SDL_WaitEvent(event);
      if(event->key.type==SDL_KEYUP)
	{
	  switch(event->key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      init_0cards();
	      *bool=0;
	      break;
	    case SDLK_UP:
	      clear_field(rendu,field);
	      if(i==0)
		i=4;
	      else
		i--;
	      refresh_menu(rendu,menu,rect_tab,field);
	      SDL_Delay(125);
	      refresh_curs(rendu,rect_tab[i],rect_curs[i]);
	      SDL_Delay(125);
	      break;
	    case SDLK_DOWN:
	      clear_field(rendu,field);
	      if(i==4)
		i=0;
	      else
		i++;
	      refresh_menu(rendu,menu,rect_tab,field);
	      SDL_Delay(125);
	      refresh_curs(rendu,rect_tab[i],rect_curs[i]);
	      SDL_Delay(125);
	      break;
	    case SDLK_RETURN:
	      switch(i)
		{
		case 0:
		  clear_field(rendu,field);
		  
		  setColor(rendu,red);
		  err_fun(SDL_RenderFillRect(rendu,&menu),"Erreur SDL_RenderFillRect: %s\n",SDL_GetError());

		  game_field(rendu,field);

		  refresh_menu(rendu,menu,rect_tab,field);
		  SDL_Delay(125);
		  refresh_curs(rendu,rect_tab[i],rect_curs[i]);
		  SDL_Delay(125);
		  break;
		case 1:
		  clear_field(rendu,field);
		  break;
		case 2:
		  clear_field(rendu,field);
		  break;
		case 3:
		  clear_field(rendu,field);
		  loadHelp(rendu,"files/help1.bmp","files/help2.bmp",&help1,&help2);
		  err_fun(SDL_QueryTexture(help1,NULL,NULL,&rect_help1.w,&rect_help1.h),"Erreur SDL_QuerryTexture: %s\n",SDL_GetError());
		  err_fun(SDL_QueryTexture(help2,NULL,NULL,&rect_help2.w,&rect_help2.h),"Erreur SDL_QuerryTexture: %s\n",SDL_GetError());
		  // positionnement rect_help
		  rect_help1.x=(field.w-rect_help1.w-rect_help2.w)/2+field.x;
		  rect_help2.x=rect_help1.x+rect_help1.w+1;
		  // fin positionnement
		  setColor(rendu,orange);
		  err_fun(SDL_RenderFillRect(rendu,&rect_help1),"Erreur SDL_RenderFillRect: %s\n",SDL_GetError());
		  err_fun(SDL_RenderFillRect(rendu,&rect_help2),"Erreur SDL_RenderFillRect: %s\n",SDL_GetError());
		  err_fun(SDL_RenderCopy(rendu,help1,NULL,&rect_help1),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
		  err_fun(SDL_RenderCopy(rendu,help2,NULL,&rect_help2),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
		  SDL_RenderPresent(rendu);
		  
		  SDL_DestroyTexture(help1);
		  SDL_DestroyTexture(help2);
		  break;
		case 4:
		  clear_field(rendu,field);
		  init_0cards();
		  *bool=0;
		  break;
		}
	      break;
	    }
	}
    }
}

void refresh_menu(SDL_Renderer *rendu,SDL_Rect menu,SDL_Rect *rect_tab,SDL_Rect field)
{
  int i;
  SDL_Color black={0,0,0,255},orange={255,140,0,255},red={123,0,27,255};
  SDL_Texture *tab[5]={NULL};
  char *name[5]={"Play Solo","Play Online","score","help","exit"};

  setColor(rendu,red);
  err_fun(SDL_RenderFillRect(rendu,&menu),"Erreur SDL_RenderFillRect: %s\n",SDL_GetError());
  for(i=0;i<5;i++)
    {
      tab[i]=loadtext(rendu,"files/SHOWG.TTF",name[i],22,black);
      err(tab[i],"Erreur SDL_CreateTextureFromSurface: %s\n",SDL_GetError());
    }
  setColor(rendu,orange);
  for(i=0;i<5;i++)
    {
      err_fun(SDL_QueryTexture(tab[i],NULL,NULL,&rect_tab[i].w,&rect_tab[i].h),"Erreur SDL_QueryTexture: %s\n",SDL_GetError());
      rect_tab[i].x=menu.w/2-rect_tab[i].w/2;
      if(i==0)
	rect_tab[i].y=field.h-menu.h+60; // field.h-menu.h=skull.h
      else
	rect_tab[i].y=rect_tab[i-1].y+rect_tab[i-1].h+8;
      err_fun(SDL_RenderFillRect(rendu,&rect_tab[i]),"Erreur SDL_RenderDrawRect: %s",SDL_GetError());
      err_fun(SDL_RenderCopy(rendu,tab[i],NULL,&rect_tab[i]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
    }
  SDL_RenderPresent(rendu);

  for(i=0;i<5;i++)
    SDL_DestroyTexture(tab[i]);
}

void refresh_curs(SDL_Renderer *rendu,SDL_Rect rect_tab,SDL_Rect rect_curs)
{
  SDL_Texture *curs=NULL;

  curs=loadImage("files/curseur.bmp",rendu);
  err_fun(SDL_QueryTexture(curs,NULL,NULL,&rect_curs.w,&rect_curs.h),"Erreur SDL_QueryTexture: %s\n",SDL_GetError());
  rect_curs.x=rect_tab.x-rect_curs.w;
  rect_curs.y=rect_tab.y+rect_tab.h/2-rect_curs.h/2;
  err_fun(SDL_RenderCopy(rendu,curs,NULL,&rect_curs),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
  SDL_RenderPresent(rendu);

  SDL_DestroyTexture(curs);
}

void refresh_hand(SDL_Renderer *rendu,SDL_Rect *hand_rect,SDL_Rect zone,int indice)
{
  int i;
  SDL_Color orange={255,140,0,100},black={0,0,0,255};

  for(i=0;i<8;i++)
    {
      setColor(rendu,black);
      err_fun(SDL_RenderDrawRect(rendu,&hand_rect[i]),"Erreur SDL_RenderDrawRect: %s\n",SDL_GetError());
      err_fun(SDL_RenderCopy(rendu,hand_set[i].carte,NULL,&hand_rect[i]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
    }
  setColor(rendu,orange);
  err_fun(SDL_RenderFillRect(rendu,&hand_rect[indice]),"Erreur SDL_RenderDrawRect: %s\n",SDL_GetError());
  err_fun(SDL_RenderCopy(rendu,hand_set[indice].carte,NULL,&zone),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
  setColor(rendu,black);
  err_fun(SDL_RenderDrawRect(rendu,&zone),"SDL_RenderDrawRect: %s\n",SDL_GetError());

  SDL_RenderPresent(rendu);
}

int replace_hand(int indice)
{
  static int i=0;
  
  if(i<90)
    {
      hand_set[indice]=pile[i];
      i++;
      return 0;
    }
  fprintf(stdout,"La pile est vide\n");
  
  return 1;
}

void clear_hand(SDL_Renderer *rendu,cards hand)
{
  SDL_Color dark_white={117,117,117,255};

  setColor(rendu,dark_white);
  err_fun(SDL_SetRenderTarget(rendu,hand.carte),"Erreur SDL_SetRenderTarget: %s\n",SDL_GetError());
  err_fun(SDL_RenderClear(rendu),"Erreur SDL_RenderClear: %s\n",SDL_GetError());
  err_fun(SDL_SetRenderTarget(rendu,NULL),"Erreur SDL_SetRenderTarget: %s\n",SDL_GetError());
  
}

void refresh_pose(SDL_Renderer *rendu,SDL_Rect *base,int indice,int val)
{
  static int bool=0,played=0;
  
  system("clear");
  if(indice%2==0)
    {
      if(hand_set[val].nbr<carte_prec[indice].nbr||hand_set[val].nbr-carte_prec[indice].nbr==10)
	{
	  err_fun(SDL_RenderCopy(rendu,hand_set[val].carte,NULL,&base[indice]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
	  carte_prec[indice].nbr=hand_set[val].nbr;
	  if(replace_hand(val))
	    {
	      if(bool)
		{
		  clear_hand(rendu,hand_set[val]);
		}
	      else
		bool=1;
	    }
	  printf("nombres de cartes jouées:%d\tcartes restantes:%d\n",played,98-played);
	}
    }
  else
    {
      if(hand_set[val].nbr>carte_prec[indice].nbr||carte_prec[indice].nbr-hand_set[val].nbr==10)
	{
	  err_fun(SDL_RenderCopy(rendu,hand_set[val].carte,NULL,&base[indice]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
	  carte_prec[indice].nbr=hand_set[val].nbr;
	  if(replace_hand(val))
	    {
	      if(bool)
		{
		  clear_hand(rendu,hand_set[val]);
		}
	      else
		bool=1;
	    }
	  printf("nombres de cartes jouées:%d\tcartes restantes:%d\n",played,98-played);
	}
    }
  played++;
}

void game_field(SDL_Renderer *rendu,SDL_Rect field)
{
  int i,j,bool=1,boolean=1,boucle=1,val;
  SDL_Color white={255,255,255,255};
  SDL_Rect tab_main[8]={{0,0,125,190},{0,0,125,190},{0,0,125,190},{0,0,125,190},{0,0,125,190},{0,0,125,190},{0,0,125,190},{0,0,125,190}},hand={0,0,1007,190},tab_base[4]={{375,25,125,190},{375,255,125,190},{745,25,125,190},{745,255,125,190}},tab_depot[4]={{520,25,125,190},{520,255,125,190},{890,25,125,190},{890,255,125,190}},pioche={0,0,125,190},actuel={0,0,125,190};
  SDL_Event event;
  SDL_Point point={0,0};

  actuel.x=tab_depot[2].x+tab_depot[2].w+25;
  actuel.y=(tab_depot[3].y+tab_depot[3].h)/2-actuel.h/2+tab_depot[0].y;

  pioche.x=actuel.x+actuel.w+50;
  pioche.y=actuel.y;

  hand.x=field.w/2-hand.w/2+field.x;
  hand.y=tab_depot[3].y+tab_depot[3].h+50;

  refresh_field(rendu,tab_base,tab_depot,field,pioche);
  SDL_Delay(250);
  setColor(rendu,white);
  err_fun(SDL_RenderDrawRect(rendu,&actuel),"Erreur SDL_RenderDrawRect: %s\n",SDL_GetError());
  err_fun(SDL_RenderDrawRect(rendu,&hand),"Erreur SDL_RenderDrawRect: %s\n",SDL_GetError());
  
  for(i=0;i<8;i++)
    {
      tab_main[i].x=hand.x+3+i*tab_main[i].w;
      tab_main[i].y=hand.y;
      err_fun(SDL_RenderDrawRect(rendu,&tab_main[i]),"Erreur SDL_RenderDrawRect: %s\n",SDL_GetError());
      err_fun(SDL_RenderCopy(rendu,hand_set[i].carte,NULL,&tab_main[i]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
    }
  SDL_RenderPresent(rendu);
  
  SDL_Delay(5);
  val=0;
  refresh_hand(rendu,tab_main,actuel,val);
  
  while(boucle)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_QUIT:
	  break;
	case SDL_KEYUP:
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      boucle=0;
	      break;
	    }
	  break;
	case SDL_MOUSEBUTTONUP:
	  point.x=event.button.x;
	  point.y=event.button.y;
	  for(i=0;boolean&&i<8;)
	    {
	      if(SDL_PointInRect(&point,&tab_main[i])==SDL_TRUE)
		{
		  boolean=0;
		}
	      else
		i++;
	  
	      if(i==8)
		{
		  for(j=0;bool&&j<4;)
		    {
		      if(SDL_PointInRect(&point,&tab_depot[j])==SDL_TRUE)
			{
			  bool=0;
			}
		      else
			j++;
		    }
		}
	    }
	  if(boolean)
	    {
	      if(!bool)
		{ 
		  switch(j)
		    {
		    case 0:
		      refresh_pose(rendu,tab_depot,j,val);
		      refresh_hand(rendu,tab_main,actuel,val);
		      boolean=1;
		      bool=1;
		      break;
		    case 1:
		      refresh_pose(rendu,tab_depot,j,val);
		      refresh_hand(rendu,tab_main,actuel,val);
		      boolean=1;
		      bool=1;
		      break;
		    case 2:
		      refresh_pose(rendu,tab_depot,j,val);
		      refresh_hand(rendu,tab_main,actuel,val);
		      boolean=1;
		      bool=1;
		      break;
		    case 3:
		      refresh_pose(rendu,tab_depot,j,val);
		      refresh_hand(rendu,tab_main,actuel,val);
		      boolean=1;
		      bool=1;
		      break;
		    }
		}
	    }
	  else
	    {
	      switch(i)
		{
		case 0:
		  refresh_hand(rendu,tab_main,actuel,i);
		  val=i;
		  boolean=1;
		  bool=1;
		  break;
		case 1:
		  refresh_hand(rendu,tab_main,actuel,i);
		  val=i;
		  boolean=1;
		  bool=1;
		  break;
		case 2:
		  refresh_hand(rendu,tab_main,actuel,i);
		  val=i;
		  boolean=1;
		  bool=1;
		  break;
		case 3:
		  refresh_hand(rendu,tab_main,actuel,i);
		  val=i;
		  boolean=1;
		  bool=1;
		  break;
		case 4:
		  refresh_hand(rendu,tab_main,actuel,i);
		  val=i;
		  boolean=1;
		  bool=1;
		  break;
		case 5:
		  refresh_hand(rendu,tab_main,actuel,i);
		  val=i;
		  boolean=1;
		  bool=1;
		  break;
		case 6:
		  refresh_hand(rendu,tab_main,actuel,i);
		  val=i;
		  boolean=1;
		  bool=1;
		  break;
		case 7:
		  refresh_hand(rendu,tab_main,actuel,i);
		  val=i;
		  boolean=1;
		  bool=1;
		  break;
		}
	    }
	  break;
	}
    }
}

void refresh_field(SDL_Renderer *rendu,SDL_Rect *tab_base,SDL_Rect *tab_depot,SDL_Rect field,SDL_Rect pioche)
{
  int i;
  SDL_Color black={0,0,0,255},white={255,255,255,255};
  SDL_Texture *game_theme=NULL;

  game_theme=loadImage("files/field_theme.bmp",rendu);
  err_fun(SDL_RenderCopy(rendu,game_theme,NULL,&field),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
  SDL_RenderPresent(rendu);
  SDL_Delay(1500);
  clear_field(rendu,field);
  
  for(i=0;i<4;i++)
    {
      setColor(rendu,black);
      err_fun(SDL_RenderDrawRect(rendu,&tab_base[i]),"Erreur SDL_RenderDrawRect: %s\n",SDL_GetError());
      setColor(rendu,white);
      err_fun(SDL_RenderDrawRect(rendu,&tab_depot[i]),"Erreur SDL_RenderDrawRect: %s\n",SDL_GetError());
    }
  setColor(rendu,black);
  err_fun(SDL_RenderDrawRect(rendu,&pioche),"Erreur SDL_RenderDrawRect: %s\n",SDL_GetError());
  err_fun(SDL_RenderCopy(rendu,cartes[1].carte,NULL,&tab_base[0]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
  err_fun(SDL_RenderCopy(rendu,cartes[2].carte,NULL,&tab_base[1]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
  err_fun(SDL_RenderCopy(rendu,cartes[1].carte,NULL,&tab_base[2]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
  err_fun(SDL_RenderCopy(rendu,cartes[2].carte,NULL,&tab_base[3]),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
  err_fun(SDL_RenderCopy(rendu,cartes[0].carte,NULL,&pioche),"Erreur SDL_RenderCopy: %s\n",SDL_GetError());
  
  SDL_RenderPresent(rendu);
}
/*
int select_random()
{
  int nbr=0;

  nbr=rand()%max;
  max=max-1;
  
  return nbr;
}

void init_main()
{
  int indice=0,i;

  for(i=0;i<8;i++)
    {
      indice=select_random();
      hand[i].nbr=tmp_cartes[indice].nbr;
      hand[i].carte=tmp_cartes[indice].carte;
      manage_tab(indice);
    }
}

void manage_tab(int indice)
{
  cards tmp;
  if(indice!=max+1)
    {
      tmp.nbr=tmp_cartes[indice].nbr;
      tmp.carte=tmp_cartes[indice].carte;
      
      tmp_cartes[indice].nbr=tmp_cartes[max+1].nbr;
      tmp_cartes[indice].carte=tmp_cartes[max+1].carte;

      tmp_cartes[max+1].nbr=tmp.nbr;
      tmp_cartes[max+1].carte=tmp.carte;
    }
}
*/
void clear_field(SDL_Renderer *rendu,SDL_Rect field)
{
  SDL_Color dark_white={117,117,117,255},black={0,0,0,255};

  setColor(rendu,dark_white);
  err_fun(SDL_RenderFillRect(rendu,&field),"Erreur SDL_RenderFillRect: %s\n",SDL_GetError());
  setColor(rendu,black);
  err_fun(SDL_RenderDrawRect(rendu,&field),"Erreur SDL_RenderFillRect: %s\n",SDL_GetError());
}

void game_interf(SDL_Renderer *rendu,const int window_w,const int window_h)
{
  SDL_Event event;
  int bool=1,boolean=1;
  SDL_Rect skull={0},menu={0},field={0};
  SDL_Color black={0,0,0,255},game_theme={117,117,117,255};
  SDL_Surface *skull_surf=NULL;
  SDL_Texture *skull_txtur=NULL;
  
  while(bool)
    {
      if(boolean)
	{
	  SDL_WaitEvent(&event);
	  if(event.key.type==SDL_KEYUP)
	    {
	      skull_surf=SDL_LoadBMP("files/skull.bmp");
	      err(skull_surf,"Erreur SDL_LoadBMP: %s\n",SDL_GetError());
	  
	      skull_txtur=SDL_CreateTextureFromSurface(rendu,skull_surf);
	      err(skull_txtur,"Erreur SDL_CreateTextureFromSurface(skull_txtur): %s\n",SDL_GetError());
	  
	      SDL_FreeSurface(skull_surf);
	      err_fun(SDL_QueryTexture(skull_txtur,NULL,NULL,&skull.w,&skull.h),"Erreur SDL_QueryTexture(): %s\n",SDL_GetError());
	      skull.w++;
	      skull.h++;
	      err_fun(SDL_SetRenderDrawColor(rendu,game_theme.r,game_theme.g,game_theme.b,game_theme.a),"Erreur SDL_SetRenderDrawColor(game_theme): %s\n",SDL_GetError());
	      err_fun(SDL_RenderClear(rendu),"Erreur SDL_RenderClear(): %s\n",SDL_GetError());
	      err_fun(SDL_SetRenderDrawColor(rendu,black.r,black.g,black.b,black.a),"Erreur SDL_SetRenderDrawColor(black): %s\n",SDL_GetError());
	      err_fun(SDL_RenderDrawRect(rendu,&skull),"Erreur SDL_RenderDrawRect(skull): %s\n",SDL_GetError());
	      err_fun(SDL_RenderCopy(rendu,skull_txtur,NULL,&skull),"Erreur SDL_RenderCopy(skull_txtur): %s\n",SDL_GetError());
	      menu.w=skull.w;
	      menu.h=window_h-skull.h-1;
	      menu.y=skull.h;
	      err_fun(SDL_RenderDrawRect(rendu,&menu),"Erreur SDL_RenderDrawRect(menu): %s\n",SDL_GetError());
	      field.x=skull.w+1;
	      field.w=window_w-field.x;
	      field.h=window_h;
	      err_fun(SDL_RenderDrawRect(rendu,&field),"Erreur SDL_RenderDrawRect(field): %s\n",SDL_GetError());
	      SDL_RenderPresent(rendu);

	      SDL_DestroyTexture(skull_txtur);
	      boolean=0;
	    }
	}
      else
	{
	  game_menu(rendu,menu,field,&event,&bool);
	}
    }
  
}

void init_0cards()
{
  int i=0;
  
  for(i=0;i<101;i++)
    SDL_DestroyTexture(cartes[i].carte);
}
