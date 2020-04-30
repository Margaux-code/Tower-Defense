#include "header.h"

void boucle_de_jeu(int niv)
{
    // Déclaration des pointeurs sur BITMAP devant recevoir des images
    BITMAP *terrain1;
    BITMAP *TESTterrain1;
    BITMAP *anim;
    decor=create_bitmap(SCREEN_W,SCREEN_H);
    anim=create_bitmap(SCREEN_W,SCREEN_H);
    // Initialisation des poney

    t_sequence tab[3]; // Declaration du tableau avec sequence image poney
    t_poney pon[3]; // Declaration du tableau avec les différentes sorte de poney
    t_poney acteur[100];
    t_poney yo;
    int nbActeur; // nombre d'acteur totale depuis le debut du niveau
    int nbActeurAff; //nombre d'acteur afficher depuis le debut du niveau
    int compt=1;
    int nbrParVague;
    inimagMech1(tab);
    iniMech(pon,tab);
    nbActeur = creaTabActeur(acteur,pon,nbActeur,niv);
    printf("%d",nbActeur);
    // Chargement des images (l'allocation a lieu en même temps)
    terrain1 = load_bitmap_check ("image/terrain/terrainlvl1.bmp");
    TESTterrain1 = load_bitmap_check ("image/terrain/ligneterrainlvl1.bmp");

    t_nuages nuage[nb_tourmax];
    t_tour arc_en_ciel[nb_tourmax];
    t_tour bonbons[nb_tourmax];

    int k;
    for (k=0; k<nb_tourmax; k++)
    {
        nuage[k].pos_x=0;
        nuage[k].pos_y=0;
        arc_en_ciel[k].pos_x=150;
        arc_en_ciel [k].pos_y=0;
        bonbons[k].pos_x=300;
        bonbons[k].pos_y=0;
    }
    int n=nb_tourmax-1;// compteur des tours nuages
    int a=nb_tourmax-1; //compteur arc_en_ciel
    int b=nb_tourmax-1;//compteur bonbons
    int nuIm=0; // numero d'image dans la sequence d'animation
    int j;
    nbActeurAff = 2*niv;
    while(!key[KEY_ESC] /*&& (mouse_b&1 &! (mouse_x>=750 && mouse_y<=20))*/)
    {

        affichageMech(acteur,nbActeur);
        if (nuIm==4)
        {
            nuIm=0;
        }
        if (compt %50==0 && nbActeur!=nbActeurAff)
        {
            printf("la bite");
            if(nbActeur-nbActeurAff<(5*niv))
            {
                nbActeurAff = nbActeur;
                printf("finish");
                printf("%d ", nbActeurAff);
            }
            if(nbActeur-nbActeurAff>=3)
            {
                nbrParVague= (rand()%(3 -(1)+1)+1)*niv;
                nbActeurAff = nbActeurAff+nbrParVague;
                printf("%d ", nbrParVague);
            }
        }
        blit(terrain1, page, 0,0,0,0, terrain1->w, terrain1->h);

        //Affichage des tours
         rectfill(page,0,0,800,70,makecol(20,20,40));

        for (k=0; k<nb_tourmax; k++)
        {
            draw_sprite(page,b_nuage,nuage[k].pos_x,nuage[k].pos_y);
            draw_sprite(page,b_arc_enciel,arc_en_ciel[k].pos_x,arc_en_ciel[k].pos_y);
            draw_sprite(page,b_bonbon,bonbons[k].pos_x,bonbons[k].pos_y);

        }

        for(j=0;j<nbActeurAff;j++)
        {
            if(acteur[j].aff == 1)
            {
                acteur[j] = Deplacement(acteur[j], TESTterrain1);
                rectfill(page,acteur[j].posx+2,acteur[j].posy-5,acteur[j].posx+62,acteur[j].posy,makecol(0,0,0));
                rectfill(page,acteur[j].posx+4,acteur[j].posy-4,acteur[j].posx+15,acteur[j].posy-1,makecol(255,0,255));
                draw_sprite(page,acteur[j].seq.img[acteur[j].numImg[nuIm]],acteur[j].posx, acteur[j].posy);
            }

            //allegro_message("yoyo");
            acteur[j].posx = acteur[j].posx + acteur[j].depx;              //On déplace l'unitée
            acteur[j].posy = acteur[j].posy + acteur[j].depy;
            if (acteur[j].posx>=750)
            {
                acteur[j].aff=0;
            }

        }
        compt++;

        // Drag and drop des tours

        if (mouse_b&1)
        {
            if (mouse_x<=100 && mouse_y<=50 && n>=0)
            {
                do
                {
                    draw_sprite(page,b_nuage,mouse_x,mouse_y);
                    nuage[n].pos_x=mouse_x;
                    nuage[n].pos_y=mouse_y;
                    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
                while(mouse_b&1);
                n--;
            } else if (150<=mouse_x && mouse_x<=250 && mouse_y<=50 && a>=0)
            {

                do{
                    draw_sprite(page,b_arc_enciel,mouse_x,mouse_y);
                    arc_en_ciel[a].pos_x=mouse_x;
                    arc_en_ciel[a].pos_y=mouse_y;
                    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
                while(mouse_b&1);
                a--;
            }else if (300<=mouse_x && mouse_x<=450 && mouse_y<=50 && b>=0)
            {
                do
                {
                    draw_sprite(page,b_bonbon,mouse_x,mouse_y);
                    bonbons[b].pos_x=mouse_x;
                    bonbons[b].pos_y=mouse_y;
                    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }while(mouse_b&1);
                b--;
            }
        }

        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        nuIm++;
        rest(100);
        clear_bitmap(page);
    }
    sauvegarde_partie(acteur,nbActeur,nbActeurAff);
    menu_jeu();
}

void sauvegarde_partie(t_poney tab[100],int nbPoney,int nbPoneyAff)
{
    int i,j;
    int compt = 0;
    FILE* fic=NULL;
    fic=fopen("fichier_partie.txt","w");
    if (fic==NULL)
    {
        allegro_message("fichier de sauvegarde partie non trouver");
    }
    else
    {
        fprintf(fic,"%d \n",nbPoney);
        fprintf(fic,"%d \n",nbPoneyAff);
        for (i=0;i<nbPoney;i++)
        {
            fprintf(fic,"%d ",tab[i].posx);
            fprintf(fic,"%d ",tab[i].posy);
            fprintf(fic,"%d ",tab[i].depx);
            fprintf(fic,"%d ",tab[i].depy);
            fprintf(fic,"%d ",tab[i].tx);
            fprintf(fic,"%d ",tab[i].ty);
            fprintf(fic,"%d ",tab[i].ptsdebonheur);
            fprintf(fic,"%d ",tab[i].val);
            fprintf(fic,"%d \n",tab[i].aff);
        }
        fclose(fic);
    }
}

void initialiser_niveau(int niv)
{
    b_nuage=load_bitmap("image/nuage1.bmp",NULL);
    if (!b_nuage)
    {
        allegro_message("pas pu trouver nuage.bmp");
        exit(EXIT_FAILURE);
    }

    b_bonbon=load_bitmap("image/bonbon1.bmp",NULL);
    if (!b_bonbon)
    {
        allegro_message("pas pu trouver bonbon.bmp");
        exit(EXIT_FAILURE);
    }
    b_arc_enciel=load_bitmap("image/arc_en_ciel1.bmp",NULL);
    if (!b_arc_enciel)
    {
        allegro_message("pas pu trouver arc_en_ciel1.bmp");
        exit(EXIT_FAILURE);
    }
}
void cinematique(int niv)
{
    histoire=load_bitmap("images/cinematiques/cinematique.bmp",NULL);
    if (!histoire)
    {
        allegro_message("pas pu trouver cinematiques.bmp");
        exit(EXIT_FAILURE);
    }
    blit(histoire,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    rest(1000);
    clear_bitmap(page);
    clear_bitmap(screen);
    boucle_de_jeu(niv);
}

int lire_niveau()
{
    int diffi;
    FILE* fc=NULL;
    fc=fopen("fichier_niveau.txt","r");
    if (fc==NULL)
    {
        allegro_message("fichier de sauvegarde numero niveau non trouver");
    }
    else
    {
        fscanf(fc,"%d \n",&diffi);
        if(diffi<1 || diffi>3)
        {
            allegro_message("erreur de valeur fichier niveau");
        }
        fclose(fc);
        return diffi;
    }
}


void choix_niveau()
{
    int niv;
    niv = lire_niveau();
    do
    {
        textprintf_ex(page,font,0,0,makecol(250,30,0),-1,"Bienenue sur le Jeu My little Poney");
        textprintf_ex(page,font,30,50,makecol(250,240,0),-1,"Choisissez votre niveau");
        textprintf_ex(page,font,30,100,makecol(250,240,0),-1,"1 2 ou 3");
        blit (page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    while(!key[KEY_1]  &&  !key[KEY_2]  && !key[KEY_3]  && !key[KEY_4] && !(mouse_b&1 && mouse_x>=750 && mouse_y<=20));

    int a;
    if (key[KEY_1])
    {
        if(niv>=1)
        {
            key[KEY_1]=0;
            key[KEY_2]=0;
            key[KEY_3]=0;
            key[KEY_4]=0;
            a=1;
            initialiser_niveau(a);
            boucle_de_jeu(a);
            cinematique(a);
        }
    }
    if (key[KEY_2])
    {
        if(niv>=2)
        {
            key[KEY_1]=0;
            key[KEY_2]=0;
            key[KEY_3]=0;
            key[KEY_4]=0;
            a=2;
            initialiser_niveau(a);
            boucle_de_jeu(a);
            cinematique(a);
        }
        else
        {
            allegro_message("niveau non debloque");
            choix_niveau();
        }
    }
    if (key[KEY_3])
    {
        if(niv>=3)
        {
            key[KEY_1]=0;
            key[KEY_2]=0;
            key[KEY_3]=0;
            key[KEY_4]=0;
            a=3;
            initialiser_niveau(a);
            boucle_de_jeu(a);
            cinematique(a);
        }
        else
        {
            allegro_message("niveau non debloque");
            choix_niveau();
        }
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
    while(!key[KEY_1]  && !key[KEY_2]  && !key[KEY_3] && !(mouse_b&1 && mouse_x>=750 && mouse_y<=20));

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
