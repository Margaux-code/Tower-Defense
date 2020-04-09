#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

typedef struct sequence // structure pour recuperer image poney
{
    int nimg;        // nombre d'images dans la s�quence
    int tx,ty;       // largeur et hauteur des images de la s�quence
    int ncol;        // nbr images cotes � cotes horizontalement dans le fichier image
    BITMAP* img[80];    // tableau de pointeurs pour indiquer les images
} t_sequence;


void initalisation();

/// affichage graphique ///
BITMAP * load_bitmap_check(char *nomImage);  // Charger une bitmap


#endif // HEADER_H_INCLUDED
