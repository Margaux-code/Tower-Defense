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
    int Vback = makecol(0,255,255);
    int test;

    vitesse = abs(poney.depx) + abs(poney.depy);       // la vitesse de l'unit� est r�cup�r�e abs() donne la valeur absolue

    test = getpixel(TEST, poney.posx+50, poney.posy+50);      // on regarde la couleur de la zone o� l'on est
    if (Rdroite == test)                                // en fonction de la couleur, un d�placement est associ�
    {
        poney.depx = 0;                                     // ses d�placements sont remis � 0
        poney.depy = 0;
        poney.depx = vitesse;
    }
    else if (Vhaut == test)
    {
        poney.depx = 0;                                     // ses d�placements sont remis � 0
        poney.depy = 0;
        poney.depy = -1*vitesse;
    }
    else if (Bbas == test)
    {
        poney.depx = 0;                                     // ses d�placements sont remis � 0
        poney.depy = 0;
        poney.depy = vitesse;
    }
    if (Vback == test)                                // en fonction de la couleur, un d�placement est associ�
    {
        poney.depx = 0;                                     // ses d�placements sont remis � 0
        poney.depy = 0;
        poney.depx = -1*vitesse;
    }
    poney.posx = poney.posx + poney.depx;             //On d�place l'unit�e
    poney.posy = poney.posy + poney.depy;
return poney;
}
