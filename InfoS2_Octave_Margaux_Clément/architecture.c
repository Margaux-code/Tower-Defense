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
    image_fin = load_bitmap("image/image_fin_petits_poney.bmp",NULL);
    game_over = load_bitmap("image/poney_triste.bmp",NULL);
    // Initialisation des poney
    int money = 100+(niv)*(20);
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
    inimagCoeur(explo);
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
    t_missile missiles[nb_tourmax];
    int i;
    int k;
    int k1;
    int i1;
    for (k=0; k<nb_tourmax; k++)
    {
        distributeur[k].active=0;
        nuage[k].active=0;
        arc_en_ciel[k].active=0;
        bonbons[k].active=0;
        nuage[k].pos_x=0;
        nuage[k].pos_y=0;
        arc_en_ciel[k].pos_x=100;
        arc_en_ciel [k].pos_y=10;
        bonbons[k].pos_x=200;
        bonbons[k].pos_y=0;
        bonbons[k].test=0;
        bonbons[k].numeImg=0;
        bonbons [k].rayon_action=100;
        distributeur[k].pos_x=300;
        distributeur[k].pos_y=0;
        arc_en_ciel[k].rayon_action=500;
        nuage[k].rayon_action=300;
        distributeur[k].rayon_action=300;
        distributeur[k].target=-1;
        missiles[k].existe=0;
    }
    int n=nb_tourmax-1;// compteur des tours nuages
    int a=nb_tourmax-1; //compteur arc_en_ciel
    int b=nb_tourmax-1;//compteur bonbons
    int d=nb_tourmax-1; //compteur distributeur
    int nuIm=0; // numero d'image dans la sequence d'animation
    int j;
    nbActeurAff = 2;
    //Ces quatres valeurs permettent de simplifier le reperage d'un enemi dans la zone de tir d'un distributeur
    int min_x;//Valeur permettant de savoir si un ennemi est dans la bonne zone
    int max_x;
    int min_y;
    int max_y;
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
            }
        }
        blit(terrain1, page, 0,0,0,0, terrain1->w, terrain1->h);
        draw_sprite(page,donjon,800-donjon->w, 290);

        //Affichage des données de jeu
        rectfill(page,0,0,800,70,makecol(20,20,40));
        textprintf_ex(page,font,400,30,makecol(0,255,255),-1,"niveau :");
        textprintf_ex(page,font,400,45,makecol(0,255,255),-1,"   %d",niv);
        textprintf_ex(page,font,600,30,makecol(0,200,0),-1,"Points de vie Tour :");
        textprintf_ex(page,font,635,45,makecol(0,255,0),-1,"%d / %d", ptsTour,ptsTourDEB);
        textprintf_ex(page,font,500,30,makecol(255,255,0),-1,"monnaie :");
        textprintf_ex(page,font,500,45,makecol(255,255,0),-1,"  %d",money);
        //Affichage des tours
        for (k=0; k<nb_tourmax; k++)
        {

            draw_sprite(page,b_nuage,nuage[k].pos_x,nuage[k].pos_y);

            draw_sprite(page,b_arc_enciel,arc_en_ciel[k].pos_x,arc_en_ciel[k].pos_y);

            if(bonbons[k].test<2)
            {
                draw_sprite(page,b_bonbon,bonbons[k].pos_x,bonbons[k].pos_y);
            }
            draw_sprite(page,b_distributeur,distributeur[k].pos_x,distributeur[k].pos_y);

        if (distributeur[k].active==0 || distributeur[k].target==0)
            draw_sprite(page,b_distributeur,distributeur[k].pos_x,distributeur[k].pos_y);
            else
            {if (nuIm==0 || nuIm==2)
            {
                draw_sprite(page,b_distributeur,distributeur[k].pos_x,distributeur[k].pos_y);
                
            }
            if (nuIm==1 || nuIm==3)
            {
                draw_sprite_h_flip(page,b_distributeur,distributeur[k].pos_x,distributeur[k].pos_y);
            }
            }
                if (acteur[distributeur[k].target].ptsbonPres<=0)
                {
                    distributeur[k].target=-1;

                    missiles[k].existe=0;
                }
            if (missiles[k].existe!=0)
            {

                if (missiles[k].pos_x != missiles[k].cible_x)
                {
                    missiles[k].existe--;
                    for(i=0; i<5; i++)
                    {
                        draw_sprite(page,b_missile,missiles[k].pos_x,missiles[k].pos_y);
                        missiles[k].pos_x=missiles[k].pos_x +(missiles[k].dep_x/10);
                        missiles[k].pos_y=missiles[k].pos_y +(missiles[k].dep_y/10);

                    }
                    acteur[distributeur[k].target].ptsbonPres=acteur[distributeur[k].target].ptsbonPres-50;
                }
            }
        }
        //Fin affichage des tours
        vivant = 0;
        //affichage des poneys et interactions avec les tours
        for(j=0;j<nbActeurAff;j++)
        {
            if(acteur[j].aff == 1)
            {
                acteur[j].depx=acteur[j].depx_init;
                acteur[j].depy=acteur[j].depy_init;
                for (k=0; k<nb_tourmax; k++)
                {
                    if(acteur[j].posx+50>=nuage[k].pos_x && acteur[j].posx+10<=nuage[k].pos_x+b_nuage->w && acteur[j].posy+50>=nuage[k].pos_y && acteur[j].posy+10<=nuage[k].pos_y+b_nuage->h)
                    {
                        if(acteur[j].depx > 1 || acteur[j].depy >1)
                        {
                            acteur[j].depx=acteur[j].depx/2;
                            acteur[j].depy=acteur[j].depy/2;
                        }
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
        //POUVOIR ARC EN CIEL
                    if(acteur[j].posx+50>=arc_en_ciel[k].pos_x && acteur[j].posx+10<=arc_en_ciel[k].pos_x+b_arc_enciel->w && acteur[j].posy+50>=arc_en_ciel[k].pos_y && acteur[j].posy+10<=arc_en_ciel[k].pos_y+b_arc_enciel->h)
                    {
                        acteur[j].ptsbonPres = acteur[j].ptsbonPres - 3;
                    }
        // POUVOIR BONBON
                    if(acteur[j].posx+40>=bonbons[k].pos_x && acteur[j].posx+5<=bonbons[k].pos_x+b_bonbon->w && acteur[j].posy+40>=bonbons[k].pos_y && acteur[j].posy+40<=bonbons[k].pos_y+b_bonbon->h)
                    {
                        if(bonbons[k].test==1 && bonbons[k].numeImg <8 )
                        {
                            draw_sprite(page,explo[bonbons[k].numeImg],acteur[j].posx-20,acteur[j].posy-20);
                            bonbons[k].numeImg++;
                            if(bonbons[k].numeImg==8)
                            {
                                bonbons[k].test = 2;
                                acteur[j].ptsbonPres = acteur[j].ptsbonPres - 300;
                            }
                        }
                        if(bonbons[k].test==0)
                        {
                            bonbons[k].test = 1;
                        }
                    }

                }
        // Rapport de points par ennemie
                if(acteur[j].ptsbonPres<=0)
                {
                    acteur[j].aff = 0;
                    money = money + acteur[j].val*(15);
                }
            }
        }
        //fin affichage poney et interaction tours
        
               //Boucle des tours qui tirent sur des ennemis
        for (k1=0;k1<nb_tourmax;k1++)
        {
            if (distributeur[k1].active==1)
            {
                if (distributeur[k1].target==-1) //Si la tour n'a pas d'ennemis attitré
                {
                    min_x=distributeur[k1].pos_x-distributeur[k1].rayon_action;
                    max_x=distributeur[k1].pos_x+distributeur[k1].rayon_action;
                    min_y=distributeur[k1].pos_y-distributeur[k1].rayon_action;
                    max_y=distributeur[k1].pos_y+distributeur[k1].rayon_action;

                    for (i1=0; i1<nbActeurAff; i1++)
                    {

                            if (acteur[i1].aff==1) // Si l'ennemi est dans le bon rayon
                            {
                               // if (distributeur[k].target==0)// Si la tour n'a pas de target
                               // {
                                    distributeur[k1].target=i1;
                                     printf("%d", distributeur[k].target);
                                    missiles[k1].existe=2;
                                    missiles[k1].pos_x=distributeur[k1].pos_x;
                                    missiles[k1].pos_y=distributeur[k1].pos_y;

                               // }
                            }



                    }// Fin du for de tous les ennemis : chaque tour a maintenant un ennemis si il y en a un dans le coin

                }

                if (distributeur[k1].target!=-1)// SI la tour a un ennemi attitré
                {


                    missiles[k1].cible_x=acteur[distributeur[k1].target].posx;
                    missiles[k1].cible_y=acteur[distributeur[k1].target].posy;
                    missiles[k1].dep_x=missiles[k1].cible_x-missiles[k1].pos_x;
                    missiles[k1].dep_y=missiles[k1].cible_y-missiles[k1].pos_y;
                    if (acteur[distributeur[k1].target].ptsbonPres<=0)
                        {
                            distributeur[k1].type_tour=-1;
                            missiles[k1].existe=0;

                        }
                    if (missiles[k1].cible_x>missiles[k1].pos_x-20&& missiles[k1].cible_x<missiles[k1].pos_x+20)
                    {
                        missiles[k1].existe=2;
                        missiles[k1].pos_x=distributeur[k1].pos_x;
                        missiles[k1].pos_y=distributeur[k1].pos_y;

                    }
                }

            }//Fin des tours qui sont actives donc des tours qui sont placées
        }//Fin de la boucle qui tire sur des ennemis

        // Drag and drop des tours

    //drag_and_drop(buffer,page,screen,b_nuage,b_arc_enciel,b_bonbon,b_distributeur,nuage,arc_en_ciel,bonbons,distributeur,&a,&b,&d,&n ,&money);
    if (mouse_b&1)
        {
            if (mouse_x<=100 && mouse_y<=50 && n>=0 && money>=30) //placer nuage
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
                //blinde_pos_nuage(TESTterrain1,nuage,&n,&money);
                if(getpixel(TESTterrain1,nuage[n].pos_x,nuage[n].pos_y)!=makecol(0,0,0)&&getpixel(TESTterrain1,nuage[n].pos_x+b_nuage->h,nuage[n].pos_y+b_nuage->h)!=makecol(0,0,0))
                {
                    nuage[n].active=1;
                    n--;
                    money = money - 30;
                }
                else
                {
                    nuage[n].active=0;
                    nuage[n].pos_x=0;
                    nuage[n].pos_y=0;
                }
            }
            else if (101<=mouse_x && mouse_x<=201 && mouse_y<=50 && a>=0 && money>=50)//Placer arc-en-ciel
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
                if(getpixel(TESTterrain1,arc_en_ciel[a].pos_x,arc_en_ciel[a].pos_y)!=makecol(0,0,0)&&getpixel(TESTterrain1,arc_en_ciel[a].pos_x+b_arc_enciel->h,arc_en_ciel[a].pos_y+b_arc_enciel->h)!=makecol(0,0,0))
                {
                    arc_en_ciel[a].active=1;
                    a--;
                    money = money - 50;
                }
                else
                {
                    arc_en_ciel[a].active=0;
                    arc_en_ciel[a].pos_x=100;
                    arc_en_ciel[a].pos_y=10;
                }
            }else if (201<=mouse_x && mouse_x<=300 && mouse_y<=50 && b>=0  && money>=20)//placer bonbon
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
                if(getpixel(TESTterrain1,bonbons[b].pos_x,bonbons[b].pos_y)!=makecol(0,0,0)&&getpixel(TESTterrain1,bonbons[b].pos_x+b_bonbon->h,bonbons[b].pos_y+b_bonbon->h)!=makecol(0,0,0))
                {
                    bonbons[b].active=1;
                    b--;
                    money = money - 20;
                }
                else
                {
                    bonbons[b].active=0;
                    bonbons[b].pos_x=200;
                    bonbons[b].pos_y=0;
                }
            }else if (301<=mouse_x && mouse_x<=400 && mouse_y<=50 && d>=0 && money>=40)
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
                if(getpixel(TESTterrain1,distributeur[d].pos_x,distributeur[d].pos_y)==makecol(0,0,0)&&getpixel(TESTterrain1,distributeur[d].pos_x+b_distributeur->h,distributeur[d].pos_y+b_distributeur->h)==makecol(0,0,0)&& distributeur[d].pos_y >= 70 )
                {
                    distributeur[d].active=1;
                    d--;
                    money = money - 40;
                }
                else
                {
                    distributeur[d].active=0;
                    distributeur[d].pos_x=300;
                    distributeur[d].pos_y=0;
                }
            }
        }
        // Fin du dépot d'une tour

        //Boucle des tours qui tirent sur des ennemis
        for (k=nb_tourmax; k>0; k--)
        {

            if (distributeur[k].active==1)
            {
                if (distributeur[k].target==-1) //Si la tour n'a pas d'ennemis attitré
                {
                    min_x=distributeur[k].pos_x-distributeur[k].rayon_action;
                    max_x=distributeur[k].pos_x+distributeur[k].rayon_action;
                    min_y=distributeur[k].pos_y-distributeur[k].rayon_action;
                    max_y=distributeur[k].pos_y+distributeur[k].rayon_action;
                    for (i=0; i<nbActeurAff; i++)
                    {
                        if (min_x<=acteur[i].posx && acteur[i].posx<=max_x && min_y<=acteur[i].posy && acteur[i].posy<=max_y) // Si l'ennemi est dans le bon rayon
                        {
                            if (distributeur[k].target==-1)// Si la tour n'a pas de target
                            {
                                distributeur[k].target=i;
                            }
                        }

                    }// Fin du for de tous les ennemis : chaque tour a maintenant un ennemis si il y en a un dans le coin

                }
                if (distributeur[k].target!=-1)// SI la tour a un ennemi attitré
                {

                        missiles[k].existe=1;
                        missiles[k].pos_x=distributeur[k].pos_x;
                        missiles[k].pos_y=distributeur[k].pos_y;
                        missiles[k].cible_x=acteur[distributeur[k].target].posx;
                        missiles[k].cible_y=acteur[distributeur[k].target].posy;



                }

            }//Fin des tours qui sont actives donc des tours qui sont placées
        }//Fin de la boucle qui tire sur des ennemis
        //draw_sprite(page,donjon,800-donjon->w, 290);
        compt++;//nbre de tours de boucle : utile pour modulo
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        nuIm++;//gère animation poney
        rest(100);//fige la boucle pendant un certains temps
        clear_bitmap(page);
        //debut des dfférents cas de sortie de jeu
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
        //debut des dfférents cas de sortie de jeu
}
//fin boucle while
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
            draw_sprite(page,image_fin,0,0);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(5000);
            clear(page);
            menu_jeu();
        }
    }
    if(test==2)
    {
        draw_sprite(page,game_over,0,0);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(5000);
        clear(page);
        menu_jeu();
    }
    if(test==1)
    {
        allegro_message("ABANDON : Retour au menu");
        menu_jeu();
    }
    sauvegarde_partie(acteur,nbActeur,nbActeurAff);
}

/*
void blinde_pos_nuage(BITMAP* TESTterrain1,t_nuages nuage[nb_tourmax], int* n, int* money)
{
    if(getpixel(TESTterrain1,nuage[*n].pos_x,nuage[*n].pos_y)!=makecol(0,0,0)&&getpixel(TESTterrain1,nuage[*n].pos_x+b_nuage->h,nuage[*n].pos_y+b_nuage->h)!=makecol(0,0,0))
    {
        nuage[*n].active=1;
        *n--;
        *money = *money - 30;
    }
    else
    {
        nuage[*n].active=0;
        nuage[*n].pos_x=0;
        nuage[*n].pos_y=0;
    }
}
*/

/*
void drag_and_drop(BITMAP* buffer,BITMAP* page,BITMAP* screen,BITMAP* b_nuage,BITMAP* b_arc_enciel, BITMAP* b_bonbon, BITMAP* b_distributeur,
                   t_nuages nuage[nb_tourmax],t_tour arc_en_ciel[nb_tourmax],t_tour bonbons[nb_tourmax],t_tour distributeur[nb_tourmax],
                   int* a,int* b,int* d, int* n ,int* money)
{
    if (mouse_b&1)
        {
            if (mouse_x<=100 && mouse_y<=50 && *n>=0 && *money>=30) //placer nuage
            {
                do
                {
                    clear(buffer);
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_nuage,mouse_x,mouse_y);
                    nuage[*n].pos_x=mouse_x;
                    nuage[*n].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
                while(mouse_b&1);
                nuage[*n].active=1;
                *n--;
                *money = *money - 30;
            }
            else if (101<=mouse_x && mouse_x<=201 && mouse_y<=50 && *a>=0 && *money>=50)//Placer arc-en-ciel
            {

                do{
                    clear(buffer);
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_arc_enciel,mouse_x,mouse_y);
                    arc_en_ciel[*a].pos_x=mouse_x;
                    arc_en_ciel[*a].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
                while(mouse_b&1);
                arc_en_ciel[*a].active=1;
                *a--;
                *money = *money - 50;
            }else if (201<=mouse_x && mouse_x<=300 && mouse_y<=50 && *b>=0  && *money>=20)//placer bonbon
            {
                do
                {
                    clear(buffer);
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_bonbon,mouse_x,mouse_y);
                    bonbons[*b].pos_x=mouse_x;
                    bonbons[*b].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }while(mouse_b&1);
                bonbons[*b].active=1;
                *b--;
                *money = *money - 20;
            }else if (301<=mouse_x && mouse_x<=400 && mouse_y<=50 && *d>=0 && *money>=40)
            {
                do
                {
                    clear(buffer);
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_distributeur,mouse_x,mouse_y);
                    distributeur[*d].pos_x=mouse_x;
                    distributeur[*d].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }while(mouse_b&1);
                distributeur[*d].active=1;
                *d--;
                *money = *money - 40;
            }
        }
}
*/

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
    rest(1000);
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
    im_choix_niv = load_bitmap("image/im_niveau.bmp",NULL);
    int clique = 0;
    if(im_choix_niv == NULL )
    {
        allegro_message("probleme de chargement image niveau");
    }
    else
    {
        int niv = 1;
        niv = lire_niveau();
        key[KEY_1]=0;
        key[KEY_2]=0;
        key[KEY_3]=0;
        key[KEY_4]=0;
        do
        {
            blit(im_choix_niv,page,0,0,0,0,SCREEN_W,SCREEN_H);
            if(niv == 1)
            {
                if (mouse_x>=50 && mouse_x<=200 && mouse_y>=125 && mouse_y<=275 )
                {
                    rect(page, 50, 120,180, 252, makecol(150,0,255));
                    if (mouse_b&1)
                    {
                        clique=1;
                    }
                }
                line(page, 340, 120, 470, 250, makecol(255,0,0));
                line(page, 340, 250, 470, 120, makecol(255,0,0));
                line(page, 625, 120, 757, 250, makecol(255,0,0));
                line(page, 625, 250, 757, 120, makecol(255,0,0));
            }
            else if (niv==2)
            {
                if (mouse_x>=50 && mouse_x<=200 && mouse_y>=125 && mouse_y<=275 )
                {
                    rect(page, 50, 120,180, 250, makecol(150,0,255));
                    if (mouse_b&1)
                    {
                        clique=1;
                    }
                }

                else if (mouse_x>= 340 && mouse_x<=470 && mouse_y>=120 && mouse_y<=250)
                {
                    rect(page, 340,120,470, 250, makecol(150,0,255));
                    if (mouse_b&1)
                    {
                        clique=2;
                    }
                }
                line(page, 625, 120, 757, 250, makecol(255,0,0));
                line(page, 625, 250, 757, 120, makecol(255,0,0));
            }
            else if (niv>=3)
            {
                if (mouse_x>=50 && mouse_x<=200 && mouse_y>=125 && mouse_y<=275 )
                {
                    rect(page, 50, 120,180, 252, makecol(150,0,255));
                    if (mouse_b&1)
                    {
                        clique=1;
                    }
                }

                else if (mouse_x>= 340 && mouse_x<=470 && mouse_y>=120 && mouse_y<=250)
                {
                    rect(page, 340,120,470, 250, makecol(150,0,255));
                    if (mouse_b&1)
                    {
                        clique=2;
                    }
                }
                else if (mouse_x>= 625 && mouse_x<=757 && mouse_y>=120 && mouse_y<=250)
                {
                    rect(page, 625,118,757, 250, makecol(150,0,255));
                    if (mouse_b&1)
                    {
                        clique=3;
                    }
                }
            }
            blit (page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        while(!key[KEY_1]  &&  !key[KEY_2]  && !key[KEY_3]  && !key[KEY_4] && !clique);
        int a;
        if (key[KEY_1] || clique==1)
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
        if (key[KEY_2] || clique == 2)
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
        if (key[KEY_3] || clique == 3)
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
    int clique_test=0;
    key[KEY_1]=0;
    key[KEY_2]=0;
    key[KEY_3]=0;
    do
    {
        blit(menu,page,0,0,0,0,SCREEN_W,SCREEN_H);
        if (mouse_x>=245 && mouse_x<=535 && mouse_y>=220 && mouse_y<=255 )
        {
            hline(page, 245, 255,535, makecol(150,0,255));
            if (mouse_b&1)
            {
                clique_test=1;
            }
        }
        if (mouse_x>=265 && mouse_x<=515 && mouse_y>=280 && mouse_y<=315 )
        {
            hline(page, 265, 310,515, makecol(150,0,255));
            if (mouse_b&1)
            {
                clique_test=2;
            }
        }
        if (mouse_x>=265 && mouse_x<=515 && mouse_y>=330 && mouse_y<=365 )
        {
            hline(page, 265, 365,515, makecol(150,0,255));
            if (mouse_b&1)
            {
                clique_test=3;
            }
        }
        blit (page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    while(!key[KEY_1]  && !key[KEY_2]  && !key[KEY_3] && !(mouse_b&1 && mouse_x>=750 && mouse_y<=20) && !clique_test);
    clear_bitmap(page);
    if (key[KEY_1] || clique_test == 1)
    {
        key[KEY_1]=0;
        key[KEY_2]=0;
        rest(200);
        choix_niveau();
    }
    else if(key[KEY_2]|| clique_test == 2)
    {
        key[KEY_1]=0;
        key[KEY_2]=0;
        rest(200);
        regles_du_jeu();
    }
}

void jeu_presentation()
{
    blit(petitsponey,page,0,0,0,0,SCREEN_W,SCREEN_H);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    rest(1000);
    clear_bitmap(page);
    menu_jeu();
}
