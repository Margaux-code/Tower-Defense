#include "header.h"



void boucle_de_jeu()
{
    while(!key[KEY_ESC] )
    {

    }

    menu_jeu();
}


void regles_du_jeu()
{

}


void menu_jeu()
{

    do {
textprintf_ex(page,font,0,0,makecol(250,30,0),-1,"Bienenue sur le Jeu My little Poney");
textprintf_ex(page,font,30,50,makecol(250,240,0),-1,"1.Commencer le Jeu");
textprintf_ex(page,font,30,100,makecol(250,240,0),-1,"2.regles du jeu");
blit (page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}while (!key[KEY_1] && !key[KEY_2]);
if (key[KEY_1])
{
    boucle_de_jeu();
}
if(key[KEY_2])
{
    regles_du_jeu();
}


}


void jeu_presentation()
{
blit(petitsponey,page,0,0,0,0,SCREEN_W,SCREEN_H);
draw_sprite(page,decor,0,140);
blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
rest(1000);
clear(page);
menu_jeu();

}


