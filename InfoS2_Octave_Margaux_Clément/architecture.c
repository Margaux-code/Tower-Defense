#include "header.h"

void boucle_de_jeu(int niv)
{
    // Déclaration des pointeurs sur BITMAP devant recevoir des images
    BITMAP *terrain1;
    BITMAP *TESTterrain1;
    //BITMAP *anim;
    decor=create_bitmap(SCREEN_W,SCREEN_H);
    //anim=create_bitmap(SCREEN_W,SCREEN_H);
    donjon = load_bitmap("image/Donjon_tour_fin.bmp",NULL);
    // Initialisation des poney
    int money = 100;
    t_sequence tab[3]; // Declaration du tableau avec sequence image poney
    t_poney pon[3]; // Declaration du tableau avec les différentes sorte de poney
    t_poney acteur[100];
    int nbActeur = 0; // nombre d'acteur totale depuis le debut du niveau
    int nbActeurAff; //nombre d'acteur afficher depuis le debut du niveau
    int compt=1;
    int nbrParVague;
    int ptsTour = 2000;
    int ptsTourDEB = 2000;
    int test=0;
    int vivant=0;
    inimagMech1(tab);
    iniMech(pon,tab);
    nbActeur = creaTabActeur(acteur,pon,nbActeur,niv);
    // Chargement des images (l'allocation a lieu en même temps)
    terrain1 = load_bitmap_check ("image/terrain/terrainlvl1.bmp");
    TESTterrain1 = load_bitmap_check ("image/terrain/ligneterrainlvl1.bmp");
    t_nuages nuage[nb_tourmax];
    t_tour arc_en_ciel[nb_tourmax];
    t_tour bonbons[nb_tourmax];
    t_tour distributeur[nb_tourmax];
    int k;
    for (k=0; k<nb_tourmax; k++)
    {
        distributeur[k].active=0;
        nuage[k].active=0;
        arc_en_ciel[k].active=0;
        bonbons[k].active=0;
        nuage[k].pos_x=0;
        nuage[k].pos_y=0;
        arc_en_ciel[k].pos_x=100;
        arc_en_ciel [k].pos_y=0;
        bonbons[k].pos_x=200;
        bonbons[k].pos_y=0;
        bonbons [k].rayon_action=100;
        distributeur[k].pos_x=300;
        distributeur[k].pos_y=0;
        arc_en_ciel[k].rayon_action=500;
        nuage[k].rayon_action=300;
    }
    int n=nb_tourmax-1;// compteur des tours nuages
    int a=nb_tourmax-1; //compteur arc_en_ciel
    int b=nb_tourmax-1;//compteur bonbons
    int d=nb_tourmax-1; //compteur distributeur
    int nuIm=0; // numero d'image dans la sequence d'animation
    int j;
    nbActeurAff = 2;
    while(test==0)
    {
        affichageMech(acteur,nbActeur);
        if (nuIm==4)
        {
            nuIm=0;
        }
        if (compt %50==0 && nbActeur!=nbActeurAff)
        {
            if(nbActeur-nbActeurAff<(5))
            {
                nbActeurAff = nbActeur;
            }
            if(nbActeur-nbActeurAff>=3)
            {
                nbrParVague= (rand()%(5 -(1)+1)+1);
                nbActeurAff = nbActeurAff+nbrParVague;
                //printf("%d ", nbrParVague);
            }
        }
        blit(terrain1, page, 0,0,0,0, terrain1->w, terrain1->h);
        draw_sprite(page,donjon,800-donjon->w, 290);
        //Affichage des tours
        rectfill(page,0,0,800,70,makecol(20,20,40));
        textprintf_ex(page,font,400,30,makecol(0,255,255),-1,"niveau :");
        textprintf_ex(page,font,400,45,makecol(0,255,255),-1,"   %d",niv);
        textprintf_ex(page,font,600,30,makecol(0,200,0),-1,"Points de vie Tour :");
        textprintf_ex(page,font,635,45,makecol(0,255,0),-1,"%d / %d", ptsTour,ptsTourDEB);
        textprintf_ex(page,font,500,30,makecol(255,255,0),-1,"monnaie :");
        textprintf_ex(page,font,500,45,makecol(255,255,0),-1,"  %d",money);
        for (k=0; k<nb_tourmax; k++)
        {
            draw_sprite(page,b_nuage,nuage[k].pos_x,nuage[k].pos_y);
            draw_sprite(page,b_arc_enciel,arc_en_ciel[k].pos_x,arc_en_ciel[k].pos_y);
            draw_sprite(page,b_bonbon,bonbons[k].pos_x,bonbons[k].pos_y);
        }
        //money = 100;
        vivant = 0;
        //Fin affichage des tours
        for(j=0;j<nbActeurAff;j++)
        {
            if(acteur[j].aff == 1)
            {
                acteur[j].depx=acteur[j].depx_init;
                acteur[j].depy=acteur[j].depy_init;
                for (k=0; k<nb_tourmax; k++)
                {
                    if(acteur[j].posx+50>=nuage[k].pos_x && acteur[j].posx+10<=nuage[k].pos_x+b_nuage->w && acteur[j].posy+50>=nuage[k].pos_y && acteur[j].posy+10<=nuage[k].pos_y+b_nuage->h && money >= 20)
                    {
                        acteur[j].depx=acteur[j].depx/2;
                        acteur[j].depy=acteur[j].depy/2;
                        //money = money - 50;
                    }
                }
                acteur[j] = Deplacement(acteur[j], TESTterrain1,&ptsTour);
                //rectfill(page,acteur[j].posx+2,acteur[j].posy-5,acteur[j].posx+62,acteur[j].posy,makecol(0,0,0));
                //rectfill(page,acteur[j].posx+4,acteur[j].posy-4,acteur[j].posx+(acteur[j].ptsbonPres/10),acteur[j].posy-1,makecol(255,0,255));
                textprintf_ex(page,font,acteur[j].posx,acteur[j].posy - 4,makecol(250,30,0),-1,"%d / %d",acteur[j].ptsbonPres,acteur[j].ptsdebonheur);
                draw_sprite(page,acteur[j].seq.img[acteur[j].numImg[nuIm]],acteur[j].posx, acteur[j].posy);
                vivant++;
                //printf("%d : %d//", j, acteur[j].ptsdebonheur);
                for (k=0; k<nb_tourmax; k++)
                {
                    if(acteur[j].posx+50>=arc_en_ciel[k].pos_x && acteur[j].posx+10<=arc_en_ciel[k].pos_x+b_arc_enciel->w && acteur[j].posy+50>=arc_en_ciel[k].pos_y && acteur[j].posy+10<=arc_en_ciel[k].pos_y+b_arc_enciel->h && money>=50)
                    {
                        acteur[j].ptsbonPres = acteur[j].ptsbonPres - 100;
                        //money = money - 20;
                    }
                }
                if(acteur[j].ptsbonPres<=0)
                {
                    acteur[j].aff = 0;
                }
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
                    clear(buffer);
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_nuage,mouse_x,mouse_y);
                    nuage[n].pos_x=mouse_x;
                    nuage[n].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
                while(mouse_b&1);
                nuage[n].active=1;
                n--;
            }
            else if (101<=mouse_x && mouse_x<=201 && mouse_y<=50 && a>=0)
            {

                do{
                    clear(buffer);
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_arc_enciel,mouse_x,mouse_y);
                    arc_en_ciel[a].pos_x=mouse_x;
                    arc_en_ciel[a].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
                while(mouse_b&1);
                arc_en_ciel[a].active=1;
                a--;
            }else if (300<=mouse_x && mouse_x<=450 && mouse_y<=50 && b>=0)
            {
                do
                {
                    clear(buffer);
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_bonbon,mouse_x,mouse_y);
                    bonbons[b].pos_x=mouse_x;
                    bonbons[b].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }while(mouse_b&1);
                bonbons[b].active=1;
                b--;
            }
        }else if (301<=mouse_x && mouse_x<=401 && mouse_y<=50 && d>=0)
            {
                do
                {
                    clear(buffer);
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_distributeur,mouse_x,mouse_y);
                    distributeur[d].pos_x=mouse_x;
                    distributeur[d].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                
                }while(mouse_b&1);
                distributeur[d].active=1;
                d--;
                
                
            } // Fin du dépot d'une tour
        //draw_sprite(page,donjon,800-donjon->w, 290);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        nuIm++;
        rest(100);
        if(key[KEY_ESC])
        {
            test=1;
        }
        else if(ptsTour <=0 )
        {
            test=2;
        }
        else if( vivant==0 && nbActeur==nbActeurAff )
        {
            test=3;
        }
        clear_bitmap(page);
}

    if(test==3)
    {
        if (niv<3)
        {
            allegro_message("Vous avez gagné vous passez au niveau supérieur");
            niv++;
            sauvegarde_niveau(niv);
            initialiser_niveau(niv);
            boucle_de_jeu(niv);
        }
        else
        {
            allegro_message("Vous avez finis le jeu bravo !!!");
            menu_jeu();
        }
    }
    if(test==2)
    {
        allegro_message("GAME OVER : ta tour a ete prise");
        menu_jeu();
    }
    if(test==1)
    {
        allegro_message("ABANDON : Retour au menu");
        menu_jeu();
    }
    sauvegarde_partie(acteur,nbActeur,nbActeurAff);
}

void sauvegarde_niveau(int diff)
{
    FILE* fic=NULL;
    fic=fopen("fichier_niveau.txt","w");
    if (fic==NULL)
    {
        allegro_message("fichier de sauvegarde partie non trouver");
    }
    else
    {
        fprintf(fic,"%d ",diff);
        fclose(fic);
    }
}

void sauvegarde_partie(t_poney tab[100],int nbPoney,int nbPoneyAff)
{
    int i;
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
       b_distributeur=load_bitmap("image/distributeur.bmp",NULL);
        if (!b_distributeur)
    {
        allegro_message("pas pu trouver distributeur.bmp");
        exit(EXIT_FAILURE);
    }
}

void cinematique(int niv)
{
    histoire=load_bitmap("image/cinematique.bmp",NULL);
    if (!histoire)
    {
        allegro_message("pas pu trouver cinematiques.bmp");
        exit(EXIT_FAILURE);
    }
    blit(histoire,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    rest(10000);
    clear_bitmap(page);
    clear_bitmap(screen);
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
    }
    return diffi;
}


void choix_niveau()
{
    int niv = 1;
    niv = lire_niveau();
    key[KEY_1]=0;
    key[KEY_2]=0;
    key[KEY_3]=0;
    key[KEY_4]=0;
    do
    {
        textprintf_ex(page,font,0,0,makecol(250,30,0),-1,"Bienvenue sur le Jeu My little Poney");
        textprintf_ex(page,font,30,50,makecol(250,240,0),-1,"Choisissez votre niveau");
        textprintf_ex(page,font,30,100,makecol(250,240,0),-1,"1 2 ou 3");
        textprintf_ex(page,font,30,200,makecol(0,200,200),-1,"Pour revenir au menu : 4");
        blit (page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

    while(!key[KEY_1]  &&  !key[KEY_2]  && !key[KEY_3]  && !key[KEY_4] && !(mouse_b&1 && mouse_x>=750 && mouse_y<=20));
    int a;
    if (key[KEY_1])
    {
        key[KEY_1]=0;
        key[KEY_2]=0;
        key[KEY_3]=0;
        key[KEY_4]=0;
        if(niv>=1)
        {
            a=1;
            initialiser_niveau(a);
            cinematique(a);
            boucle_de_jeu(a);
        }
    }
    if (key[KEY_2])
    {
        key[KEY_1]=0;
        key[KEY_2]=0;
        key[KEY_3]=0;
        key[KEY_4]=0;
        if(niv>=2)
        {
            a=2;
            initialiser_niveau(a);
            cinematique(a);
            boucle_de_jeu(a);
        }
        else
        {
            allegro_message("niveau non debloque");
            choix_niveau();
        }
    }
    if (key[KEY_3])
    {
        key[KEY_1]=0;
        key[KEY_2]=0;
        key[KEY_3]=0;
        key[KEY_4]=0;
        if(niv>=3)
        {
            a=3;
            initialiser_niveau(a);
            cinematique(a);
            boucle_de_jeu(a);
        }
        else
        {
            allegro_message("niveau non debloque");
            choix_niveau();
        }
    }
    if (key[KEY_4])
    {
        key[KEY_1]=0;
        key[KEY_2]=0;
        key[KEY_3]=0;
        key[KEY_4]=0;
        menu_jeu();
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
    key[KEY_1]=0;
    key[KEY_2]=0;
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
    else if(key[KEY_2])
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
