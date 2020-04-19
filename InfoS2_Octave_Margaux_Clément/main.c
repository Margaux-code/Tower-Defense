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
    inimagMech1(tab);
    iniMech(pon,tab);

    // Chargement des images (l'allocation a lieu en même temps)
    terrain1 = load_bitmap_check ("image/terrain/terrainlvl1.bmp");
    TESTterrain1 = load_bitmap_check ("image/terrain/ligneterrainlvl1.bmp");

    // Affichage de l'image sur l'écran


    int i=0;

    while (!key[KEY_ESC])
    {
        if (i==32)
        {
            i=0;
        }
        blit(terrain1, page, 0,0,0,0, terrain1->w, terrain1->h);
        draw_sprite(page,pon[0].seq.img[i], pon[0].posx, pon[0].posy);
        draw_sprite(page,pon[1].seq.img[i], pon[1].posx, pon[1].posy);
        draw_sprite(page,pon[2].seq.img[i], pon[2].posx, pon[2].posy);
        blit(page,screen,0,0,0,0,800,600);
        i++;
        rest(100);
        clear_bitmap(page);
        clear_bitmap(screen);
    }

    return 0;


}
END_OF_MAIN();
