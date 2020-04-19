#include "header.h"


int main()

{

    // Lancer allegro et le mode graphique

    initalisation();

    // Déclaration des pointeurs sur BITMAP devant recevoir des images

    BITMAP *terrain1;
    BITMAP *TESTterrain1;
    BITMAP *page;
    page = create_bitmap(800,600);

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

    while (!key[KEY_ESC])
    {
        affichageMech(acteur,nbActeur);
        if (i==4)
        {
            i=0;
        }
        blit(terrain1, page, 0,0,0,0, terrain1->w, terrain1->h);
        for(j=0;j<nbActeur;j++)
        {
            //allegro_message("yoyo");
            draw_sprite(page,acteur[j].seq.img[acteur[j].numImg[i]], j*64, j*64);
            //allegro_message("yoyo");
        }
        blit(page,screen,0,0,0,0,800,600);
        i++;
        rest(100);
        clear_bitmap(page);
        clear_bitmap(screen);
    }
    return 0;

}
END_OF_MAIN();
