#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

typedef struct sequence // structure pour recuperer image poney
{
    int nimg;        // nombre d'images dans la séquence
    int tx,ty;       // largeur et hauteur des images de la séquence
    int ncol;        // nbr images cotes à cotes horizontalement dans le fichier image
    BITMAP* img[80];    // tableau de pointeurs pour indiquer les images
} t_sequence;


void initalisation();

/// affichage graphique ///
BITMAP * load_bitmap_check(char *nomImage);  // Charger une bitmap


#endif // HEADER_H_INCLUDED
