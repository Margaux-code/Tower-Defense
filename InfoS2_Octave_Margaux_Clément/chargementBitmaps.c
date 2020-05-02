#include "header.h"


///fourni dans le cours de M. Fercoq ///

//chargement d'une image et blindage
//prototype : BITMAP * load_bitmap_check(char *nomImage);

BITMAP* load_bitmap_check(char *nomImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomImage,NULL);
    if (!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }
    return bmp;
}
