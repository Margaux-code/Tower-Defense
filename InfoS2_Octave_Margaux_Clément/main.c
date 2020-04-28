#include "header.h"

int main()

{

    // Lancer allegro et le mode graphique

    initalisation();

    // Déclaration des pointeurs sur BITMAP devant recevoir des images

    page = create_bitmap(SCREEN_W,SCREEN_H);
    petitsponey=create_bitmap(SCREEN_W,SCREEN_H);
    regles=create_bitmap(SCREEN_W,SCREEN_H);
    menu=create_bitmap(SCREEN_W,SCREEN_H);

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
    //t_tour * nuage;
    show_mouse(screen);
    jeu_presentation();
    return 0;

}
END_OF_MAIN();
