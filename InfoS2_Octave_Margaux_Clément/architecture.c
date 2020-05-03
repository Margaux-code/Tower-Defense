#include "header.h"

void boucle_de_jeu(int niv)
{

 
    // Initialisation des poney
    int money = 100+(niv)*(15);
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
    //int compteur_superposition = 0;
    inimagCoeur(explo);
    inimagMech1(tab);
    iniMech(pon,tab);
    nbActeur = creaTabActeur(acteur,pon,nbActeur,niv);

    t_nuages nuage[nb_tourmax];
    t_tour arc_en_ciel[nb_tourmax];
    t_tour bonbons[nb_tourmax];
    t_tour distributeur[nb_tourmax];
    t_missile missiles[nb_tourmax];
    int k;
    for (k=0; k<nb_tourmax; k++)
    {
        distributeur[k].active=0;
        nuage[k].active=0;
        nuage[k].nivo=0;
        arc_en_ciel[k].active=0;
        bonbons[k].active=0;
        nuage[k].pos_x=0;
        nuage[k].pos_y=0;
        arc_en_ciel[k].pos_x=100;
        arc_en_ciel [k].pos_y=10;
        arc_en_ciel[k].nivo==0;
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
    nbActeurAff = 2;
    /*int min_x;
    int max_x;
    int min_y;
    int max_y;*/
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

        affichage_donnees_jeu(page,niv,ptsTour,money,ptsTourDEB);

        //  Sous - programme d'upgrade;
        uprude_nuage(nuage, &money,page);
        uprude_arc_en_ciel(arc_en_ciel ,&money ,page);
        //Affichage des tour
        affichage_tour(page, b_nuage, b_nuage_2, b_arc_enciel, b_arc_enciel_2, b_bonbon, b_distributeur, b_missile,
                     nuage, arc_en_ciel, bonbons, distributeur, missiles, acteur, nuIm);
        //Fin affichage des tours
        //affichage des poneys et interactions avec les tours
        interaction_poney(page, TESTterrain1, b_nuage, b_bonbon, b_arc_enciel, explo, nbActeurAff, &ptsTour, &vivant, &money, nuIm,acteur,nuage,
                          bonbons,arc_en_ciel,niv);
        //fin affichage poney et interaction tours

        //Fonction qui gere le fonctionnement des friandise du distributeur
        gestion_missile (distributeur,missiles,acteur,nbActeurAff);

        // Drag and drop des tours
        drag_and_drop(TESTterrain1,buffer,page,screen,b_nuage,b_nuage_2,b_arc_enciel,b_arc_enciel_2,b_bonbon, b_distributeur,nuage,arc_en_ciel
                  ,bonbons,distributeur,&a,&b,&d,&n,&money);
        // Fin du dépot d'une tour

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
        //sauvegarde_partie(acteur,nbActeur,nbActeurAff);
    }

}


void interaction_poney(BITMAP* page, BITMAP* TESTterrain1,BITMAP* b_nuage,BITMAP* b_bonbon, BITMAP* b_arc_enciel, BITMAP* explo[8],
                       int nbActeurAff,int* ptsTour, int* vivant ,int* money,int nuIm,t_poney acteur[100],t_nuages nuage[nb_tourmax],
                       t_tour bonbons[nb_tourmax],t_tour arc_en_ciel[nb_tourmax],int niv)
{
    int j,k;
    *vivant = 0;
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
                        if(((acteur[j].depx > 1) || (acteur[j].depy >1)) && nuage[k].nivo==0)
                        {
                            acteur[j].depx=acteur[j].depx/2;
                            acteur[j].depy=acteur[j].depy/2;
                        }
                        if((acteur[j].depx > 1 || acteur[j].depy >1) && nuage[k].nivo==1)
                        {
                            acteur[j].depx=1;
                            acteur[j].depy=1;
                        }
                    }
                }
                acteur[j] = Deplacement(acteur[j], TESTterrain1,ptsTour);
                textprintf_ex(page,font,acteur[j].posx,acteur[j].posy - 4,makecol(250,30,0),-1,"%d / %d",acteur[j].ptsbonPres,acteur[j].ptsdebonheur);
                draw_sprite(page,acteur[j].seq.img[acteur[j].numImg[nuIm]],acteur[j].posx, acteur[j].posy);
                (*vivant)++;
                //printf("%d : %d//", j, acteur[j].ptsdebonheur);
                for (k=0; k<nb_tourmax; k++)
                {
                //POUVOIR ARC EN CIEL
                    if(acteur[j].posx+50>=arc_en_ciel[k].pos_x && acteur[j].posx+10<=arc_en_ciel[k].pos_x+b_arc_enciel->w && acteur[j].posy+50>=arc_en_ciel[k].pos_y && acteur[j].posy+10<=arc_en_ciel[k].pos_y+b_arc_enciel->h)
                    {
                        if(arc_en_ciel[k].nivo==0)
                        {
                            acteur[j].ptsbonPres = acteur[j].ptsbonPres - 3;
                        }
                        else
                        {
                            acteur[j].ptsbonPres = acteur[j].ptsbonPres - 4;
                        }

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
        // Rapport de points par poney heureux
                if(acteur[j].ptsbonPres<=0)
                {
                    acteur[j].aff = 0;
                    *money = *money + acteur[j].val*9*(4-niv);
                }
            }
        }
}

void affichage_tour(BITMAP* page,BITMAP* b_nuage,BITMAP* b_nuage_2,BITMAP* b_arc_enciel,BITMAP* b_arc_enciel_2,BITMAP* b_bonbon,BITMAP* b_distributeur,BITMAP* b_missile,
                    t_nuages nuage[nb_tourmax],t_tour arc_en_ciel[nb_tourmax],t_tour bonbons[nb_tourmax],t_tour distributeur[nb_tourmax],t_missile missiles[nb_tourmax],
                    t_poney acteur[100],int nuIm)
{
    int k,i;
    for (k=0; k<nb_tourmax; k++)
        {
            if(nuage[k].nivo==0)
            {
                draw_sprite(page,b_nuage,nuage[k].pos_x,nuage[k].pos_y);
                textprintf_ex(page,font,25,530,makecol(255,255,0),-1,"Upgrade");
                textprintf_ex(page,font,30,545,makecol(255,255,0),-1,"Nuage");
                textprintf_ex(page,font,15,560,makecol(255,255,0),-1,"Cout : 50");
            }
            else
            {
                draw_sprite(page,b_nuage_2,nuage[k].pos_x,nuage[k].pos_y);
                textprintf_ex(page,font,25,530,makecol(155,155,155),-1,"Upgrade");
                textprintf_ex(page,font,30,545,makecol(155,155,155),-1,"Nuage");
                textprintf_ex(page,font,15,560,makecol(155,155,155),-1,"Cout : 50");
            }
            if(arc_en_ciel[k].nivo==0)
            {
                draw_sprite(page,b_arc_enciel,arc_en_ciel[k].pos_x,arc_en_ciel[k].pos_y);
                textprintf_ex(page,font,125,530,makecol(200,0,255),-1,"Upgrade");
                textprintf_ex(page,font,110,545,makecol(200,0,255),-1,"Arc en ciel");
                textprintf_ex(page,font,113,560,makecol(200,0,255),-1,"Cout : 100");

            }
            else
            {
                draw_sprite(page,b_arc_enciel_2,arc_en_ciel[k].pos_x,arc_en_ciel[k].pos_y);
                textprintf_ex(page,font,125,530,makecol(155,155,155),-1,"Upgrade");
                textprintf_ex(page,font,110,545,makecol(155,155,155),-1,"Arc en ciel");
                textprintf_ex(page,font,113,560,makecol(155,155,155),-1,"Cout : 100");
            }

            if(bonbons[k].test<2)
            {
                draw_sprite(page,b_bonbon,bonbons[k].pos_x,bonbons[k].pos_y);
            }
            draw_sprite(page,b_distributeur,distributeur[k].pos_x,distributeur[k].pos_y);

            if (distributeur[k].active==0 || distributeur[k].target==-1)
            {
                draw_sprite(page,b_distributeur,distributeur[k].pos_x,distributeur[k].pos_y);
            }
            else
            {
                if (nuIm==0 || nuIm==2)
                {
                    draw_sprite(page,b_distributeur,distributeur[k].pos_x,distributeur[k].pos_y);
                }
                else
                {
                    if (nuIm==0 || nuIm==2)
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
                            if(missiles[k].pos_x>=0)
                            {
                                draw_sprite(page,b_missile,missiles[k].pos_x,missiles[k].pos_y);
                            }
                            else
                            {
                                draw_sprite_h_flip(page,b_missile,missiles[k].pos_x,missiles[k].pos_y);
                            }
                            missiles[k].pos_x=missiles[k].pos_x +(missiles[k].dep_x/10);
                            missiles[k].pos_y=missiles[k].pos_y +(missiles[k].dep_y/10);
                        }
                        acteur[distributeur[k].target].ptsbonPres=acteur[distributeur[k].target].ptsbonPres-3;
                    }
                }
            }
        }
}

void uprude_nuage(t_nuages nu[nb_tourmax] ,int* money ,BITMAP* page)
{
    int i = 0;
    if (mouse_x>=0 && mouse_x<=100 && mouse_y>=520&& mouse_y<=600 && nu[i].nivo == 0)
    {
        rect(page, 0, 520,100, 599, makecol(255,255,0));
        if (mouse_b&1 && *money >= 50)
        {
            for(i=0;i<nb_tourmax;i++)
            {
                nu[i].nivo=1;
            }
            *money = *money-50;
        }
    }
}

void gestion_missile (t_tour distributeur[nb_tourmax],t_missile missiles [nb_tourmax],t_poney acteur[100],int nbActeurAff)
{
    int k1;
    int i1;
    int k;
    int i;
    //Ces quatres valeurs permettent de simplifier le reperage d'un enemi dans la zone de tir d'un distributeur
    int min_x;//Valeur permettant de savoir si un ennemi est dans la bonne zone
    int min_y;
    int max_x;
    int max_y;
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
                                    missiles[k1].existe=2;
                                    missiles[k1].pos_x=distributeur[k1].pos_x+b_distributeur->w/2 ;
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

                        missiles[k].existe=1; //Tour activé
                        missiles[k].pos_x=distributeur[k].pos_x; //
                        missiles[k].pos_y=distributeur[k].pos_y;
                        missiles[k].cible_x=acteur[distributeur[k].target].posx;
                        missiles[k].cible_y=acteur[distributeur[k].target].posy;
                }

            }//Fin des tours qui sont actives donc des tours qui sont placées//
        }//Fin de la boucle qui tire sur des ennemis
}

void uprude_arc_en_ciel(t_tour arc[nb_tourmax] ,int* money ,BITMAP* page)
{
    int i = 0;
    if (mouse_x>=100 && mouse_x<=200 && mouse_y>=520&& mouse_y<=600 && arc[i].nivo == 0)
    {
        rect(page, 101, 520,200, 599, makecol(200,0,255));
        if (mouse_b&1 && *money >= 100)
        {
            for(i=0;i<nb_tourmax;i++)
            {
                arc[i].nivo=1;
            }
            *money = *money-100;
        }
    }
}

void affichage_donnees_jeu(BITMAP* page, int niv, int ptsTour,int money, int ptsTourDEB)
{
    rectfill(page,0,0,800,70,makecol(20,20,40));
    rectfill(page,0,520,800,600,makecol(20,20,40));
    textprintf_ex(page,font,400,30,makecol(0,255,255),-1,"niveau :");
    textprintf_ex(page,font,400,45,makecol(0,255,255),-1,"   %d",niv);
    textprintf_ex(page,font,600,30,makecol(0,200,0),-1,"Points de vie Tour :");
    textprintf_ex(page,font,635,45,makecol(0,255,0),-1,"%d / %d", ptsTour,ptsTourDEB);
    textprintf_ex(page,font,500,30,makecol(255,255,0),-1,"monnaie :");
    textprintf_ex(page,font,500,45,makecol(255,255,0),-1,"  %d",money);
    textprintf_ex(page,font,300,540,makecol(0,255,255),-1,"cout nuage : 30");
    textprintf_ex(page,font,300,570,makecol(200,0,255),-1,"cout arc-en-ciel: 50");
    textprintf_ex(page,font,500,540,makecol(255,0,200),-1,"cout BonBombe : 20");
    textprintf_ex(page,font,500,570,makecol(255,0,0),-1,"cout Distributeur : 40");

}

void drag_and_drop(BITMAP* TESTterrain1,BITMAP* buffer,BITMAP* page,BITMAP* screen,BITMAP* b_nuage, BITMAP* b_nuage_2, BITMAP* b_arc_enciel,BITMAP* b_arc_enciel_2, BITMAP* b_bonbon, BITMAP* b_distributeur,
                   t_nuages nuage[nb_tourmax],t_tour arc_en_ciel[nb_tourmax],t_tour bonbons[nb_tourmax],t_tour distributeur[nb_tourmax],
                   int* a,int* b,int* d, int* n ,int* money)
{
     int i;
     int compteur_superposition;
     if (mouse_b&1)
    {
        ///PLACER NUAGE ///
            if (mouse_x<=100 && mouse_y<=50 && *n>=0 && *money>=30) //placer nuage
            {
                do
                {
                    clear(buffer);//Pour ne pas laisser de trainer derriere quand on pose la tour
                    compteur_superposition=0;
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    if(nuage[*n].nivo==0)
                    {
                        draw_sprite(buffer,b_nuage,mouse_x,mouse_y);
                    }
                    else
                    {
                        draw_sprite(buffer,b_nuage_2,mouse_x,mouse_y);
                    }
                    for (i=0;i<nb_tourmax;i++)
                    {
                        if(mouse_x>=arc_en_ciel[i].pos_x - b_arc_enciel->w  && mouse_x<=arc_en_ciel[i].pos_x + b_arc_enciel->w && mouse_y>=arc_en_ciel[i].pos_y - b_arc_enciel->h && mouse_y<=arc_en_ciel[i].pos_y + b_arc_enciel->h)
                        {
                            compteur_superposition++;
                        }
                    }
                    for (i=nb_tourmax-1;i>*n;i--)
                    {
                        if(mouse_x>=nuage[i].pos_x - b_nuage->w && mouse_x<=nuage[i].pos_x + b_nuage->w && mouse_y>=nuage[i].pos_y - b_nuage->h && mouse_y<=nuage[i].pos_y + b_nuage->h)
                        {
                            compteur_superposition++;
                        }
                    }
                    nuage[*n].pos_x=mouse_x;
                    nuage[*n].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
                while(mouse_b&1);
                //blinde_pos_nuage(TESTterrain1,nuage,&n,&money);
                if(getpixel(TESTterrain1,nuage[*n].pos_x,nuage[*n].pos_y)!=makecol(0,0,0)&&getpixel(TESTterrain1,nuage[*n].pos_x+b_nuage->h,nuage[*n].pos_y+b_nuage->h)!=makecol(0,0,0)&& compteur_superposition==0)
                {
                    nuage[*n].active=1;
                    (*n)--;
                    *money = *money - 30;
                }
                else
                {
                    nuage[*n].active=0;
                    nuage[*n].pos_x=0;
                    nuage[*n].pos_y=0;
                }
            }
            ///PLACER ARC EN CIEL///
            else if (101<=mouse_x && mouse_x<=201 && mouse_y<=50 && *a>=0 && *money>=50)//Placer arc-en-ciel
            {

                do{
                    clear(buffer);//Pour ne pas laisser de trainer derriere quand on pose la tour
                    compteur_superposition=0;
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    if(arc_en_ciel[*a].nivo==0)
                    {
                        draw_sprite(buffer,b_arc_enciel,mouse_x,mouse_y);
                    }
                    else
                    {
                        draw_sprite(buffer,b_arc_enciel_2,mouse_x,mouse_y);
                    }
                    arc_en_ciel[*a].pos_x=mouse_x;
                    arc_en_ciel[*a].pos_y=mouse_y;
                    for (i=0;i<nb_tourmax;i++)
                    {
                        if(mouse_x>=nuage[i].pos_x - b_nuage->w && mouse_x<=nuage[i].pos_x + b_nuage->w && mouse_y>=nuage[i].pos_y - b_nuage->h && mouse_y<=nuage[i].pos_y + b_nuage->h)
                        {
                            compteur_superposition++;
                        }
                    }
                    for (i=nb_tourmax-1;i>*a;i--)
                    {
                        if(mouse_x>=arc_en_ciel[i].pos_x - b_arc_enciel->w  && mouse_x<=arc_en_ciel[i].pos_x + b_arc_enciel->w && mouse_y>=arc_en_ciel[i].pos_y - b_arc_enciel->h && mouse_y<=arc_en_ciel[i].pos_y + b_arc_enciel->h)
                        {
                            compteur_superposition++;
                        }
                    }
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
                while(mouse_b&1);
                if(getpixel(TESTterrain1,arc_en_ciel[*a].pos_x,arc_en_ciel[*a].pos_y)!=makecol(0,0,0)&&getpixel(TESTterrain1,arc_en_ciel[*a].pos_x+b_arc_enciel->h,arc_en_ciel[*a].pos_y+b_arc_enciel->h)!=makecol(0,0,0) && compteur_superposition==0)
                {
                        arc_en_ciel[*a].active=1;
                        (*a)--;
                        *money = *money - 50;
                }
                else
                {
                    arc_en_ciel[*a].active=0;
                    arc_en_ciel[*a].pos_x=100;
                    arc_en_ciel[*a].pos_y=10;
                }
            }
            /// PLACER BONBOMBE (petit jeu de mot ahah)///
            else if (201<=mouse_x && mouse_x<=300 && mouse_y<=50 && *b>=0  && *money>=20)//placer bonbon
            {
                do
                {
                    clear(buffer); //Pour ne pas laisser de trainer derriere quand on pose la tour
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_bonbon,mouse_x,mouse_y);
                    bonbons[*b].pos_x=mouse_x;
                    bonbons[*b].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }while(mouse_b&1);
                if(getpixel(TESTterrain1,bonbons[*b].pos_x,bonbons[*b].pos_y)!=makecol(0,0,0)&&getpixel(TESTterrain1,bonbons[*b].pos_x+b_bonbon->h,bonbons[*b].pos_y+b_bonbon->h)!=makecol(0,0,0))
                {
                    bonbons[*b].active=1;
                    (*b)--;
                    *money = *money - 20;
                }
                else
                {
                    bonbons[*b].active=0;
                    bonbons[*b].pos_x=200;
                    bonbons[*b].pos_y=0;
                }
            }
            ///PLACER DISTIBRUTEUR DE FRIANDISE///
            else if (301<=mouse_x && mouse_x<=400 && mouse_y<=50 && *d>=0 && *money>=40)// verification de la positions de la sousis pour la pioche et de l'argent du joueur
            {
                do
                {
                    clear(buffer); //Pour ne pas laisser de trainer derriere quand on pose la tour
                    blit(page,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(buffer,b_distributeur,mouse_x,mouse_y);//Draw sprite dans la boucle pour voir l'image se déplacer avec la souris
                    distributeur[*d].pos_x=mouse_x;
                    distributeur[*d].pos_y=mouse_y;
                    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H); //triple buffer ici pour ne pas voir la trainer
                }while(mouse_b&1);
                if(getpixel(TESTterrain1,distributeur[*d].pos_x,distributeur[*d].pos_y)==makecol(0,0,0)&&
                   getpixel(TESTterrain1,distributeur[*d].pos_x+b_distributeur->h, distributeur[*d].pos_y+b_distributeur->h)==makecol(0,0,0)&&
                   distributeur[*d].pos_y >= 70 && distributeur[*d].pos_y + b_distributeur->w <= 530 ) // Blindage de pose pour le distributeur
                {
                    distributeur[*d].active=1;//distibuteur activé il peut tirer
                    (*d)--; // nombre de distributeur dans la pioche -1;
                    *money = *money - 40; // soustraction du prix du distributeur a l'argent du joueur
                }
                else // si les conditions de blindage pas valide
                {
                    distributeur[*d].active=0; // le distributeur n'est pas actif : il ne tire pas
                    distributeur[*d].pos_x=300; // on remets le distributeur a la position de la pioche
                    distributeur[*d].pos_y=0;
                }
            }
        }
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
