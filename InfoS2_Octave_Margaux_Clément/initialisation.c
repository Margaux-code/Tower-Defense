#include "header.h"

void initalisation()
{
    allegro_init();
    install_mouse();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void inimagCoeur(BITMAP* tab[8])// credit M.Fercoq
{
    BITMAP *explosion;
    int i;           // indice de l'image dans la séquence
    int ix,iy;       // indices (horizontal et vertical) dans le "tableau" des images
    int sx,sy;       // coordonnées correspondantes (en pixels)

    explosion=load_bitmap("image/explosion.bmp",NULL);
    if (!explosion)
    {
        allegro_message("pas pu trouver l'explosion");
        exit(EXIT_FAILURE);
    }
    ix = 0;
    iy = 0;
    for (i=0;i<8;i++)
    {
        tab[i]=create_bitmap(100,100);
        // récupérer image
        sx=ix*120+15;
        sy=iy*120+10;
        blit(explosion,tab[i],sx,sy,0,0,100,100);

        // préparer indices pour l'image suivante
        ix++;          // colonne suivante
        if (ix >= 4)  // si je suis à droite de la dernière colonne alors...
        {
            ix=0;      // repartir sur la colonne 0
            iy++;      // à la ligne en dessous
        }
    }
    destroy_bitmap(explosion);
}
