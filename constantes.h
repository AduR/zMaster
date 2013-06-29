#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

    #define FPS             50
    #define FPS_DELAY       (1000/FPS)

    #define HAUTEUR_JEU 500

    #define LARGEUR_PLATEAU 200
    #define LARGEUR_INFO    50
    #define LARGEUR_COULEUR 50

    #define LARGEUR_FENETRE (LARGEUR_PLATEAU+LARGEUR_INFO+LARGEUR_COULEUR+100)
    #define HAUTEUR_FENETRE (HAUTEUR_JEU+100)


    #define RANGEE  10
    #define TROU    4
    #define COULEUR 4

    enum {COULEUR_RIEN=0, ROUGE, VERT, BLEU, JAUNE, COLOR_LAST}Couleur; /*, CYAN, MAGENTA, BLANC, NOIR*/
    enum {INFO_RIEN=0, BIEN_PLACE, BONNE_COULEUR}Info;
    enum {NORMAL=0, CLIC};

    typedef struct{
        int rouge;
        int blanc;
    }sInfo;

    typedef struct{
        int coupJoues;
        int plateau[TROU][RANGEE];
        sInfo info[RANGEE];
        int solution[TROU];
    }Master;

#endif /* CONSTANTES_H_INCLUDED */
