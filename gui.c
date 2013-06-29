/*
===== MasterMind SDL =====
fichier     gui.c
But         fonctions d'affichage
Date        juin 2013
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "My_SDL_lib.h"

#include "constantes.h"
#include "gui.h"


void initGui(Gui *gui)
{
    gui->police = my_loadTtfFont("LBRITE.ttf", 25);
    gui->policeTitre = my_loadTtfFont("LBRITE.ttf", 50);
    gui->petit = my_loadSdlSurface("petit.png", (Uint32)NULL);
    gui->color = my_loadSdlSurface("color.png", MY_LOAD_COLORKEY);
}



void blitPlateau(Gui *gui, Master *master)
{
    SDL_Surface *ecran = SDL_GetVideoSurface(), *texte;
    SDL_Color color = {0, 0, 0, (Uint32)NULL}, colorBleu = {0, 0, 192, (Uint32)NULL};
    SDL_Rect sRect, dRect;
    int x, y, y1;
    char chaine[20];

    /* FOND */
    dRect.x = 50;
    dRect.y = 100;
    dRect.w = LARGEUR_PLATEAU+LARGEUR_INFO;
    dRect.h = HAUTEUR_JEU;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_FillRect(ecran, &dRect, SDL_MapRGB(ecran->format, 0, 0, 0));

    /* NUMEROS */
    for (y=0; y<RANGEE; y++)
    {
        sprintf(chaine, "%d", y+1);
        texte = TTF_RenderText_Blended(gui->police, chaine, color);
        my_blitSurface(texte, 25-texte->w/2, y*50+100+25-texte->h/2);
        SDL_FreeSurface(texte);
    }

    /* TEXTES */
    texte = TTF_RenderText_Blended(gui->policeTitre, "zMaster", colorBleu);
    my_blitSurface(texte, LARGEUR_FENETRE/2-texte->w/2, 100/2-texte->h/2);
    SDL_FreeSurface(texte);
    texte = TTF_RenderText_Blended(gui->police, "verifier", color);
    my_blitSurface(texte, 350-texte->w/2, 200+50/2-texte->h/2);
    SDL_FreeSurface(texte);
    texte = TTF_RenderText_Blended(gui->police, "effacer", color);
    my_blitSurface(texte, 350-texte->w/2, 250+50/2-texte->h/2);
    SDL_FreeSurface(texte);

    /* PLATEAU GROS RONDS */
    sRect.y = 0;
    sRect.h = 50;
    sRect.w = 50;
    for (x=0; x<TROU; x++)
    {
        for (y=0; y<RANGEE; y++)
        {
            sRect.x = master->plateau[x][y]*50;

            dRect.x = x*50+50;
            dRect.y = y*50+100;

            SDL_BlitSurface(gui->color, &sRect, ecran, &dRect);
        }
    }

    /* PLATEAU PETITS RONDS */
    sRect.y = 0;
    sRect.h = 25;
    sRect.w = 25;
    for (y=0; y<RANGEE; y++)
    {
        int rouge = master->info[y].rouge;
        int blanc = master->info[y].blanc;

        for (y1=0; y1<2; y1++)
        {
            for (x=0; x<2; x++)
            {
                if (y < master->coupJoues)
                {
                    if (rouge-- > 0) sRect.x = 25; /* rouge */
                    else if (blanc-- > 0) sRect.x = 50; /* blanc */
                    else sRect.x = 0; /* noir */
                }
                else
                {
                    sRect.x = 0;
                }

                dRect.x = x*25+200+50;
                dRect.y = y*50+y1*25+100;

                SDL_BlitSurface(gui->petit, &sRect, ecran, &dRect);
            }
        }
    }

    sRect.y = 0;
    sRect.h = 50;
    sRect.w = 50;
    dRect.x = 300;

    /* RONDS DE COULEURS */
    for (y=0; y<COLOR_LAST; y++)
    {
        sRect.x = y*50;
        dRect.y = HAUTEUR_FENETRE-y*50;
        SDL_BlitSurface(gui->color, &sRect, ecran, &dRect);
    }
}




void blitGagne(Gui *gui)
{
    SDL_Color color = {192, 0, 0, (Uint32)NULL};
    SDL_Surface *texte = TTF_RenderText_Blended(gui->policeTitre, "Gagné !", color);
    SDL_Rect dRect;

    dRect.x = 0;
    dRect.y = 0;
    dRect.w = LARGEUR_FENETRE;
    dRect.h = 100;
    SDL_FillRect(SDL_GetVideoSurface(), &dRect, SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 255, 255));

    my_blitSurface(texte, LARGEUR_FENETRE/2-texte->w/2, 100/2-texte->h/2);

    SDL_Flip(SDL_GetVideoSurface());

    SDL_FreeSurface(texte);
}
