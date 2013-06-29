/*
===== MasterMind SDL =====
fichier     main.c
But         Main source code file
Date        juin 2013
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "My_SDL_lib.h"

#include "constantes.h"
#include "gui.h"
#include "calculs.h"


int main(int argc, char *argv[])
{
    /* VARIABLES */
    SDL_Surface *ecran = NULL;

    Input in;
    Temps temps;
    Master master;
    Gui gui;

    int tabEcran[LARGEUR_FENETRE/50][HAUTEUR_FENETRE/50];
    int continuer = 1;
    int x;

    /* INIT */
    (void) argc, (void) argv;
    srand((unsigned int)time(NULL));
    ecran = initSdl(LARGEUR_FENETRE, HAUTEUR_FENETRE, "zMaster", NULL);
    initTtf();
    initGui(&gui);

    memset(&in, 0, sizeof in);
    memset(&temps, 0, sizeof temps);
    memset(&master, 0, sizeof master);

    setSolution(&master.solution);

    /* BOUCLE PRINCIPALE */
    while (!in.quit && continuer)
    {
        updateEvent(&in);

        if (in.mousebutton[SDL_BUTTON_LEFT])
        {
            /* tab pour savoir ou est le clic */
            memset(&tabEcran, 0, sizeof tabEcran);
            tabEcran[in.mousex/50][in.mousey/50] = 1;

            /* nouveau rond */
            in.mousebutton[SDL_BUTTON_LEFT] = nouveauRond(&master, &tabEcran);

            /* verifier */
            if (tabEcran[6][4] || tabEcran[7][4])
            {
                int nbRond = 0;

                for (x=0; x<TROU; x++)
                    if (master.plateau[x][master.coupJoues] != COULEUR_RIEN)
                        nbRond ++;

                if (nbRond == TROU)
                {
                    calculInfo(&master);
                    continuer = (master.info[master.coupJoues].rouge != TROU);
                    master.coupJoues ++;
                }
            }

            /* effecer */
            if (tabEcran[6][5] || tabEcran[7][5])
            {
                for (x=0; x<TROU; x++)
                    master.plateau[x][master.coupJoues] = COULEUR_RIEN;
            }
        }

        blitPlateau(&gui, &master);
        SDL_Flip(ecran);

        gererTemps(&temps, FPS_DELAY);
    }

    blitGagne(&gui);
    while (!in.quit)
    {
        updateEvent(&in);
        SDL_Delay(FPS_DELAY);
    }

    /* FREE */
    TTF_CloseFont(gui.police);
    TTF_CloseFont(gui.policeTitre);
    TTF_Quit();

    SDL_FreeSurface(gui.petit);
    SDL_FreeSurface(gui.color);
    SDL_Quit();

    return 0;
}

