#include "header.h"

void iniseqMech(t_sequence tab[3])
{
    tab[0].nomimage="image/petitponey/pp1.bmp";
    tab[1].nomimage="image/petitponey/pp2.bmp";
    tab[2].nomimage="image/petitponey/pp3.bmp";
    int j;
    for(j=0;j<3;j++)
    {
        tab[j].nimg = 32; // nombre d'image de petit poney
        tab[j].ncol = 4; // nombre de colonne dans l'image
        tab[j].tx = 64; // largeur de l'image
        tab[j].ty = 64; // hauteur de l'image
    }
    tab[0].inix = 0; //debut de la sequence sur l'image 1
    tab[1].inix = 192; //debut de la sequence sur l'image 2
    tab[2].inix = 0; //debut de la sequence sur l'image 3
}

void inimagMech1(t_sequence tab[3])// credit M.Fercoq
{
    iniseqMech(tab);
    int j;
    for (j=0;j<3;j++)
    {
    BITMAP *source;
    int i;           // indice de l'image dans la séquence
    int ix,iy;       // indices (horizontal et vertical) dans le "tableau" des images
    int sx,sy;       // coordonnées correspondantes (en pixels)

    source=load_bitmap(tab[j].nomimage,NULL);
    if (!source)
    {
        allegro_message("pas pu trouver %s", tab[j].nomimage);
        exit(EXIT_FAILURE);
    }

    ix = 0;
    iy = 0;
    for (i=0;i<tab[j].nimg;i++)
    {
        // allouer image
        tab[j].img[i]=create_bitmap(tab[j].tx,tab[j].ty);

        // récupérer image
        sx=ix*tab[j].tx+tab[j].inix;
        sy=iy*tab[j].ty;
        blit(source,tab[j].img[i],sx,sy,0,0,tab[j].tx,tab[j].ty);

        // préparer indices pour l'image suivante
        ix++;          // colonne suivante
        if (ix >= tab[j].ncol)  // si je suis à droite de la dernière colonne alors...
        {
            ix=0;      // repartir sur la colonne 0
            iy++;      // à la ligne en dessous
        }
    }
    destroy_bitmap(source);
    }
}

void iniMech(t_poney tab[3],t_sequence t[3])
{
    tab[0].depx =2;
    tab[0].depy =0;
    tab[0].tx =64;
    tab[0].ty =64;
    tab[0].posx =0;
    tab[0].posy =250;
    tab[0].ptsdebonheur =500;
    tab[0].val = 1;
    tab[0].aff = 1;
    tab[0].att = 50;
    tab[0].seq = t[0];

    tab[1].depx =4;
    tab[1].depy =0;
    tab[1].tx =64;
    tab[1].ty =64;
    tab[1].posx =0;
    tab[1].posy =250;
    tab[1].ptsdebonheur =300;
    tab[1].val = 2;
    tab[1].aff = 1;
    tab[1].att = 30;
    tab[1].seq = t[1];

    tab[2].depx =6;
    tab[2].depy =0;
    tab[2].tx =64;
    tab[2].ty =64;
    tab[2].posx =0;
    tab[2].posy = 250;
    tab[2].ptsdebonheur =100;
    tab[2].val = 3;
    tab[2].aff = 1;
    tab[2].att = 5;
    tab[2].seq = t[2];
}

int creaTabActeur(t_poney acteur[100],t_poney typeperso[3],int i,int difficulte)
{
    int niv;
    if (difficulte == 1)
    {
        niv = 20;
    }
    else if (difficulte == 2)
    {
        niv = 50;
    }
    else if (difficulte >= 3)
    {
        niv = 100;
    }
    i = 0;
    int pos;
    int compt=0;
    int type;
    while(compt<niv)
    {
        pos = rand()%(270 -(245)+1)+245;
        if (compt<(niv-2))
        {
            type = rand()%(2 -(0)+1)-0;
            printf("%d ",type);
            acteur[i]=typeperso[type];
            acteur[i].posy = pos;
            compt = compt+type+1;
        }
        else if (compt == (niv-2))
        {
            type = rand()%(1 -(0)+1);
            acteur[i]=typeperso[type];
            acteur[i].posy = pos;
            compt = compt+type+1;
        }
        else if (compt == (niv-1))
        {
            type = 0;
            printf("yo %d ",type);
            acteur[i]=typeperso[type];
            acteur[i].posy = pos;
            compt = compt+type+1;
        }
        i++;
    }
    return i;
}

void affichageMech(t_poney act[100],int nbAct)
{
    int j,i;
    for (j=0;j<nbAct;j++)
    {
        if(act[j].depx>0)
        {
            if(act[j].depy == 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=i+8;
                }
            }
            else if(act[j].depy > 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=i+12;
                }
            }
            else if(act[j].depy < 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=i+4;
                }
            }
        }
        else if(act[j].depx < 0)
        {
            if(act[j].depy == 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=i+24;
                }
            }
            else if(act[j].depy > 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=i+20;
                }
            }
            else if(act[j].depy < 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=i+28;
                }
            }
        }
        else if (act[j].depx == 0)
        {
            if(act[j].depy == 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=11;
                }
            }
            else if(act[j].depy > 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=i+16;
                }
            }
            else if(act[j].depy < 0)
            {
                for(i=0;i<4;i++)
                {
                    act[j].numImg[i]=i;
                }
            }
        }
    }
}







