#include "header.h"

void iniseqMech(t_sequence tab[3])
{
    tab[0].nomimage="pp1.bmp";
    tab[1].nomimage="pp2.bmp";
    tab[2].nomimage="pp3.bmp";
    int j;
    for(j=0;j<3;j++)
    {
        tab[j].nimg = 80;
        tab[j].ncol = 10;
        tab[j].tx = 64;
        tab[j].ty = 64;
    }
}

void inimagMech1(t_sequence tab[3])// credit M.Fercoq
{
    iniseqMech(tab);
    int j;
    for (j=0;j<3;j++)
    {
    BITMAP *source;
    int i;           // indice de l'image dans la séquence
    int ix,iy;       // indices (horizontal et vertical) dans le "tableau" des images
    int sx,sy;       // coordonnées correspondantes (en pixels)

    source=load_bitmap(tab[j].nomimage,NULL);
    if (!source)
    {
        allegro_message("pas pu trouver %s", tab[j].nomimage);
        exit(EXIT_FAILURE);
    }

    ix = 0;
    iy = 0;
    for (i=0;i<tab[j].nimg;i++)
    {
        // allouer image
        tab[j].img[i]=create_bitmap(tab[j].tx,tab[j].ty);

        // récupérer image
        sx=ix*tab[j].tx;
        sy=iy*tab[j].ty;
        blit(source,tab[j].img[i],sx,sy,0,0,tab[j].tx,tab[j].ty);

        // préparer indices pour l'image suivante
        ix++;          // colonne suivante
        if (ix >= tab[j].ncol)  // si je suis à droite de la dernière colonne alors...
        {
            ix=0;      // repartir sur la colonne 0
            iy++;      // à la ligne en dessous
        }
    }
    destroy_bitmap(source);
    }
}
