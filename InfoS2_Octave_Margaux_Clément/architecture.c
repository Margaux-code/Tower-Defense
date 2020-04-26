#include "header.h"




void boucle_de_jeu()
{
    
    
    
    while(!key[KEY_ESC] )
    {

    }

    menu_jeu();
}

void initialiser_niveau(int a)
{
    decor=load_bitmap("decors/decor%d.bmp",a);
    if (!decor)
    {
        allegro_message("pas pu trouver fond_ecran.bmp");
        exit(EXIT_FAILURE);
    }
    
    
}

void cinematique(int b)
{
     histoire=load_bitmap("cinematique%d.bmp",b);
    if (!histoire)
    {
        allegro_message("pas pu trouver cinematique.bmp");
        exit(EXIT_FAILURE);
    }
    blit(histoire,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    rest(1000);
    boucle_de_jeu();
}


void choix_niveau()
{
    do
    {
        textprintf_ex(page,font,0,0,makecol(250,30,0),-1,"Bienenue sur le Jeu My little Poney");
        textprintf_ex(page,font,30,50,makecol(250,240,0),-1,"Choisissez votre niveau");
        textprintf_ex(page,font,30,100,makecol(250,240,0),-1,"1 2 ou 3");
        blit (page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    while(!key[KEY_1]  &&  !key[KEY_2]  && !key[KEY_3]  && !key[KEY_4]);

int a;
if (key[KEY_1])
{
    key[KEY_1]=0;
    key[KEY_2]=0;
    key[KEY_3]=0;
    key[KEY_4]=0;
    a=1;
    initialiser_niveau(a);
    cinematique(a);
}
if (key[KEY_2])
{
    key[KEY_1]=0;
    key[KEY_2]=0;
    key[KEY_3]=0;
    key[KEY_4]=0;
    a=2;
    initialiser_niveau(a);
    cinematique(a);
}
if (key[KEY_3])
{
    key[KEY_1]=0;
    key[KEY_2]=0;
    key[KEY_3]=0;
    key[KEY_4]=0;
    a=3;
    initialiser_niveau(a);
    cinematique(a);
}


}

void regles_du_jeu()
{
while (!key[KEY_1])
{
    blit(regles,page,0,0,0,0,SCREEN_W,SCREEN_H);
     blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}
key[KEY_1]=0;
menu_jeu();
}


void menu_jeu()
{

    do
    {

        blit(menu,page,0,0,0,0,SCREEN_W,SCREEN_H);
        blit (page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    while(!key[KEY_1]  && !key[KEY_2]  && !key[KEY_3]);

    clear(page);
    if (key[KEY_1])
    {
        key[KEY_1]=0;
        key[KEY_2]=0;
        choix_niveau();
    }
    if(key[KEY_2])
    {
        key[KEY_1]=0;
        key[KEY_2]=0;
        regles_du_jeu();
    }


}

void jeu_presentation()
{
    blit(petitsponey,page,0,0,0,0,SCREEN_W,SCREEN_H);

    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    rest(1000);
    clear(page);
    menu_jeu();

}
