#include "header.h"

/// Prototype           | t_poney Deplacement(t_poney poney, BITMAP* TEST);
/// exemple 1 unit�e    | Pinkie = Deplacement(Pinkie, TESTterrain1);
/// pour un tableau faire une boucle for
///           for (i=0; i<X; i++)
///           {
///               tabPoney[i] = Deplacement(tabPoney[i], TESTterrain1);
///           }

t_poney Deplacement(t_poney poney, BITMAP* TEST)
{
    int vitesse;         // les couleurs sont assosi� � une direction
    int Rdroite = makecol(255,0,0);
    int Vhaut = makecol(0,255,0);
    int Bbas = makecol(0,0,255);
    int test;

    vitesse = abs(poney.depx) + abs(poney.depy) ;       // la vitesse de l'unit� est r�cup�r�e abs() donne la valeur absolue
    poney.depx = 0;                                     // ses d�placements sont remis � 0
    poney.depy = 0;

    test = getpixel(TEST, poney.posx, poney.posy);      // on regarde la couleur de la zone o� l'on est
    if (Rdroite == test)                                // en fonction de la couleur, un d�placement est associ�
    {
        poney.depx = vitesse;
    }
    else if (Vhaut == test)
    {
        poney.depy = -1*vitesse;
    }
    else if (Bbas == test)
    {
        poney.depy = vitesse;
    }

    poney.posx = poney.posx + poney.depx;              //On d�place l'unit�e
    poney.posy = poney.posy + poney.depy;

    if ((poney.depx == 0) && (poney.depy ==0))        // il est arriv� qu'un pixel ne soit pas exactement de la bonne couleur, dans ce cas on change de pixel
    {
        poney.posx = poney.posx + 1;
        poney.depx = vitesse;
    }


return poney;
}
