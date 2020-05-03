#include "header.h"

int main()

{

    // Lancer allegro et le mode graphique

    initalisation();

    // Pour pouvoir utiliser des chiffres aleatoire
    srand(time(NULL));

    chargement_bitmap();
    show_mouse(screen);
    jeu_presentation();
    detruire_bitmap();
    return 0;

}
END_OF_MAIN();
