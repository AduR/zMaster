/*
===== MasterMind SDL =====
fichier     calculs.c
But         algo de base
Date        juin 2013
*/

#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "calculs.h"


int nouveauRond(Master *master, int (*tabEcran)[LARGEUR_FENETRE/50][HAUTEUR_FENETRE/50])
{
    int colorClique = -1;
    int x;

    for (x=0; x<COLOR_LAST; x++)
    {
        if ((*tabEcran)[6][12-x] == 1)
        {
            colorClique = x;
            break;
        }
    }

    if (colorClique != -1)
    {
        /* trouver le premier trou libre et le remplir */
        for (x=0; x<TROU; x++)
        {
            if (master->plateau[x][master->coupJoues] == COULEUR_RIEN)
            {
                master->plateau[x][master->coupJoues] = colorClique;
                return 0;
            }
        }
    }

    return 1;
}


void setSolution(int (*solution)[TROU])
{
    int x;

    for (x=0; x<TROU; x++)
    {
        (*solution)[x] = (rand()%(COLOR_LAST-1))+1;
    }
}


void calculInfo(Master *master)
{
    int x, y;
    int guess[TROU], solutionCpy[TROU];
    master->info[master->coupJoues].rouge = 0;
    master->info[master->coupJoues].blanc = 0;

    for (x=0; x<TROU; x++)
    {
        guess[x] = master->plateau[x][master->coupJoues];
        solutionCpy[x] = master->solution[x];
    }

    /* rouge */
    for (x=0; x<TROU; x++)
    {
        if(guess[x] == solutionCpy[x])
        {
            master->info[master->coupJoues].rouge++;
            guess[x] = -1;
            solutionCpy[x] = -2;
        }
    }
    /* blanc */
    for (x=0; x<TROU; x++)
    {
        for(y=0; y<TROU; y++)
        {
            if(guess[x] == solutionCpy[y])
            {
                master->info[master->coupJoues].blanc++;
                guess[x] = -1;
                solutionCpy[y] = -2;
            }
        }
    }
}

