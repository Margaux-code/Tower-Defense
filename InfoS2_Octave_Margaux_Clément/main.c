#include "header.h"

int main()

{

    // Lancer allegro et le mode graphique

    initalisation();

    // Déclaration des pointeurs sur BITMAP devant recevoir des images

    BITMAP *terrain1;
    BITMAP *TESTterrain1;
    BITMAP *page;
    page = create_bitmap(SCREEN_W,SCREEN_H);
    decor=create_bitmap(SCREEN_W,SCREEN_H);
    
    petitsponey=create_bitmap(SCREEN_W,SCREEN_H);
    regles=create_bitmap(SCREEN_W,SCREEN_H);
    menu=create_bitmap(SCREEN_W,SCREEN_H);

    // Initialisation des poney

    t_sequence tab[3]; // Declaration du tableau avec sequence image poney
    t_poney pon[3]; // Declaration du tableau avec les différentes sorte de poney
    t_poney acteur[100];
    int nbActeur;
    inimagMech1(tab);
    iniMech(pon,tab);
    nbActeur = creaTabActeur(acteur,pon,nbActeur);
    printf("%d",nbActeur);
    // Chargement des images (l'allocation a lieu en même temps)
    terrain1 = load_bitmap_check ("image/terrain/terrainlvl1.bmp");
    TESTterrain1 = load_bitmap_check ("image/terrain/ligneterrainlvl1.bmp");

    int i=0;
    int j;

petitsponey=load_bitmap("Intro.bmp",NULL);
    if (!petitsponey)
    {
        allegro_message("pas pu trouver intro.bmp");
        exit(EXIT_FAILURE);
    }
    menu=load_bitmap("menu.bmp",NULL);
        if (!menu)
    {
        allegro_message("pas pu trouver menu.bmp");
        exit(EXIT_FAILURE);
    }
    t_tour * nuage;
    show_mouse(screen);
    jeu_presentation();
    return 0;

}
END_OF_MAIN();
