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

void chargement_bitmap()
{
    page = create_bitmap(SCREEN_W,SCREEN_H);
    petitsponey=create_bitmap(SCREEN_W,SCREEN_H);
    regles=create_bitmap(SCREEN_W,SCREEN_H);
    menu=create_bitmap(SCREEN_W,SCREEN_H);
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    b_distributeur=create_bitmap(SCREEN_W,SCREEN_H);
    b_missile=create_bitmap(SCREEN_W,SCREEN_H);
    //BITMAP *anim;
    decor=create_bitmap(SCREEN_W,SCREEN_H);
    // Chargement des images (l'allocation a lieu en même temps)
    terrain1 = load_bitmap_check ("image/terrain/terrainlvl1.bmp");
    TESTterrain1 = load_bitmap_check ("image/terrain/ligneterrainlvl1.bmp");
    //anim=create_bitmap(SCREEN_W,SCREEN_H);
    donjon = load_bitmap("image/Donjon_tour_fin.bmp",NULL);
    image_fin = load_bitmap("image/image_fin_petits_poney.bmp",NULL);
    game_over = load_bitmap("image/poney_triste.bmp",NULL);

    petitsponey=load_bitmap("image/Intro.bmp",NULL);
    if (!petitsponey)
    {
        allegro_message("pas pu trouver intro.bmp");
        exit(EXIT_FAILURE);
    }
    menu=load_bitmap("image/Menu.bmp",NULL);
    if (!menu)
    {
        allegro_message("pas pu trouver menu.bmp");
        exit(EXIT_FAILURE);
    }
    b_missile=load_bitmap("image/missiles.bmp",NULL);
        b_arc_enciel_2 = load_bitmap("image/arc_en_ciel2.bmp",NULL);
    if (!b_arc_enciel_2)
    {
        allegro_message("pas pu trouver arc_enciel2.bmp");
        exit(EXIT_FAILURE);
    }
    b_nuage_2=load_bitmap("image/nuage2.bmp",NULL);
    if (!b_nuage_2)
    {
        allegro_message("pas pu trouver nuage2.bmp");
        exit(EXIT_FAILURE);
    }
    b_nuage=load_bitmap("image/nuage1.bmp",NULL);
    if (!b_nuage)
    {
        allegro_message("pas pu trouver nuage.bmp");
        exit(EXIT_FAILURE);
    }

    b_bonbon=load_bitmap("image/bonbon1.bmp",NULL);
    if (!b_bonbon)
    {
        allegro_message("pas pu trouver bonbon.bmp");
        exit(EXIT_FAILURE);
    }
    b_arc_enciel=load_bitmap("image/arc_en_ciel1.bmp",NULL);
    if (!b_arc_enciel)
    {
        allegro_message("pas pu trouver arc_en_ciel1.bmp");
        exit(EXIT_FAILURE);
    }
       b_distributeur=load_bitmap("image/distributeur.bmp",NULL);
        if (!b_distributeur)
    {
        allegro_message("pas pu trouver distributeur.bmp");
        exit(EXIT_FAILURE);
    }

}
