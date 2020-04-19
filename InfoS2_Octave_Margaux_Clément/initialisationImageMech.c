#include "header.h"

void iniseqMech(t_sequence tab[3])
{
    tab[0].nomimage="image/petitponey/pp1.bmp";
    tab[1].nomimage="image/petitponey/pp2.bmp";
    tab[2].nomimage="image/petitponey/pp3.bmp";
    int j;
    for(j=0;j<3;j++)
    {
        tab[j].nimg = 32;
        tab[j].ncol = 4;
        tab[j].tx = 64;
        tab[j].ty = 64;
    }
    tab[0].inix = 0;
    tab[1].inix = 192;
    tab[2].inix = 0;
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
        sx=ix*tab[j].tx+tab[j].inix;
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

void iniMech(t_poney tab[3],t_sequence t[3])
{
    tab[0].depx =3;
    tab[0].depy =0;
    tab[0].tx =64;
    tab[0].ty =64;
    tab[0].posx =0;
    tab[0].posy =200;
    tab[0].ptsdebonheur =500;
    tab[0].val = 1;
    tab[0].seq = t[0];

    tab[1].depx =5;
    tab[1].depy =0;
    tab[1].tx =64;
    tab[1].ty =64;
    tab[1].posx =200;
    tab[1].posy =200;
    tab[1].ptsdebonheur =300;
    tab[1].val = 2;
    tab[1].seq = t[1];

    tab[2].depx =10;
    tab[2].depy =0;
    tab[2].tx =64;
    tab[2].ty =64;
    tab[2].posx =100;
    tab[2].posy =200;
    tab[2].ptsdebonheur =100;
    tab[2].val = 3;
    tab[2].seq = t[2];
}







