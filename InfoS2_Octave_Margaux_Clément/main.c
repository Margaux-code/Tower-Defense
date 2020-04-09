#include "header.h"


int main()
{
    // Lancer allegro et le mode graphique
    initalisation();

    // Déclaration des pointeurs sur BITMAP devant recevoir des images
    BITMAP *terrain1;
    BITMAP *TESTterrain1;

    // Chargement des images (l'allocation a lieu en même temps)
    terrain1 = load_bitmap_check ("image/terrain/terrainlvl1.bmp");
    TESTterrain1 = load_bitmap_check ("image/terrain/ligneterrainlvl1.bmp");

    // Affichage de l'image sur l'écran
    blit(terrain1, screen, 0,0,0,0, terrain1->w, terrain1->h);


    while (!key[KEY_ESC])
    {

    }

    return 0;

    
}
END_OF_MAIN();
