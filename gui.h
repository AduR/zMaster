#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

    typedef struct{
        TTF_Font    *police;
        TTF_Font    *policeTitre;
        SDL_Surface *petit;
        SDL_Surface *color;
    }Gui;

    void initGui(Gui *gui);
    void blitPlateau(Gui *gui,  Master *master);
    void blitGagne(Gui *gui);

#endif /* GUI_H_INCLUDED */
