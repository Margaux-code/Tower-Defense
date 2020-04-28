#include "header.h"

void boucle_de_jeu()
{
    // Déclaration des pointeurs sur BITMAP devant recevoir des images
    BITMAP *terrain1;
    BITMAP *TESTterrain1;
    BITMAP *page;
    page = create_bitmap(SCREEN_W,SCREEN_H);
    decor=create_bitmap(SCREEN_W,SCREEN_H);

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
    while(!key[KEY_ESC] )
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
            rectfill(page,j*64+2,j*64-5,j*64+62,j*64,makecol(0,0,0));
            rectfill(page,j*64+4,j*64-4,j*64+i*15,j*64-1,makecol(0,255,0));
            draw_sprite(page,acteur[j].seq.img[acteur[j].numImg[i]], j*64, j*64);
            //allegro_message("yoyo");
        }
        blit(page,screen,0,0,0,0,800,600);
        i++;
        rest(100);
        clear_bitmap(page);
        clear_bitmap(screen);
    }

    menu_jeu();
}

void initialiser_niveau(int a) // LE a représente le niveau
{
    decor=load_bitmap("decors/decor%d.bmp",a);
    if (!decor)
    {
        allegro_message("pas pu trouver fond_ecran.bmp");
        exit(EXIT_FAILURE);
    }


}

void cinematique(int b) // LE b représente le niveau
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
