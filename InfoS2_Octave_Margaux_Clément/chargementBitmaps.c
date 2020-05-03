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
    histoire = create_bitmap(SCREEN_W,SCREEN_H);
    terrain1 = create_bitmap(SCREEN_W,SCREEN_H);
    page = create_bitmap(SCREEN_W,SCREEN_H);
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    // Chargement des images (l'allocation a lieu en même temps)
    Terr3=load_bitmap("image/terrain/terrainlvl3.bmp",NULL);
    if (!Terr3)
    {
        allegro_message("pas pu trouver terrain 3");
        exit(EXIT_FAILURE);
    }
    Terr2=load_bitmap("image/terrain/terrainlvl2.bmp",NULL);
    if (!Terr2)
    {
        allegro_message("pas pu trouver terrain 2");
        exit(EXIT_FAILURE);
    }
    cinema3=load_bitmap("image/cinematique3.bmp",NULL);
    if (!cinema3)
    {
        allegro_message("pas pu trouver cinematique 3");
        exit(EXIT_FAILURE);
    }
    cinema2=load_bitmap("image/cinematique2.bmp",NULL);
    if (!cinema2)
    {
        allegro_message("pas pu trouver cinematique 2");
        exit(EXIT_FAILURE);
    }
    regles=load_bitmap("image/regles_du_jeu.bmp",NULL);
    if (!regles)
    {
        allegro_message("pas pu trouver regle du jeu");
        exit(EXIT_FAILURE);
    }
    Terr1 = load_bitmap("image/terrain/terrainlvl1.bmp",NULL);
    if (!Terr1)
    {
        allegro_message("pas pu trouver terrain1");
        exit(EXIT_FAILURE);
    }
    TESTterrain1 = load_bitmap("image/terrain/ligneterrainlvl1.bmp",NULL);
    if (!TESTterrain1)
    {
        allegro_message("pas pu trouver donjon.bmp");
        exit(EXIT_FAILURE);
    }
    donjon = load_bitmap("image/Donjon_tour_fin.bmp",NULL);
    if (!donjon)
    {
        allegro_message("pas pu trouver donjon.bmp");
        exit(EXIT_FAILURE);
    }
    image_fin = load_bitmap("image/image_fin_petits_poney.bmp",NULL);
    if (!image_fin)
    {
        allegro_message("pas pu trouver l'image de fin");
        exit(EXIT_FAILURE);
    }
    game_over = load_bitmap("image/poney_triste.bmp",NULL);
    if (!game_over)
    {
        allegro_message("pas pu trouver image game over");
        exit(EXIT_FAILURE);
    }

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
    if (!b_missile)
    {
        allegro_message("pas pu trouver missile.bmp");
        exit(EXIT_FAILURE);
    }
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
    cinema1=load_bitmap("image/cinematique.bmp",NULL);
    if (!histoire)
    {
        allegro_message("pas pu trouver cinematiques.bmp");
        exit(EXIT_FAILURE);
    }
}

void detruire_bitmap()
{
    destroy_bitmap(terrain1);
    destroy_bitmap(TESTterrain1);
    destroy_bitmap(page);
    destroy_bitmap(buffer);
    destroy_bitmap(decor);
    destroy_bitmap(petitsponey);
    destroy_bitmap(b_nuage);
    destroy_bitmap(b_arc_enciel);
    destroy_bitmap(b_bonbon);
    destroy_bitmap(b_distributeur);
    destroy_bitmap(b_missile);
    destroy_bitmap(regles);
    destroy_bitmap(menu);
    destroy_bitmap(histoire);
    destroy_bitmap(niveau);
    destroy_bitmap(donjon);
    destroy_bitmap(image_fin);
    destroy_bitmap(game_over);
    destroy_bitmap(im_choix_niv);
    destroy_bitmap(b_nuage_2);
    destroy_bitmap(b_arc_enciel_2);
}

