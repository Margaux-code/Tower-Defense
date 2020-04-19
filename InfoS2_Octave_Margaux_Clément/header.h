#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#define nb_tour 3
#define rayon_nuage 50
#define tire_nuage 3
#define ralentir_nuage 1
#define vitesse_missile_nuage 10
BITMAP *page;
BITMAP *decor;
BITMAP *b_tour[nb_tour];
BITMAP * b_missile[nb_tour];

typedef struct sequence // structure pour recuperer image poney
{
    char* nomimage;
    int nimg;        // nombre d'images dans la séquence
    int tx,ty;       // largeur et hauteur des images de la séquence
    int ncol;        // nbr images cotes à cotes horizontalement dans le fichier image
    int inix;          // coordonnée de la premiere image
    BITMAP* img[32];    // tableau de pointeurs pour indiquer les images
} t_sequence;

typedef struct poney
{
    int posx;
    int posy;
    int depx;
    int depy;
    int tx;
    int ty;
    int ptsdebonheur;
    int val;
    t_sequence seq;
}t_poney;


typedef struct t_missile t_missile;
struct t_missile
{
    int pos_x;
    int pos_y;
    int vitesse;
    int cible_x;
    int cible_y;
    int degat;
};


typedef struct t_tour t_tour;
struct t_tour
{
    int pos_x;
    int pos_y;
    int rayon_action;
    int type_tour;
    int frequence_tir;
    int ralentir;
    t_missile missile;

};

void initalisation();

/// affichage graphique ///
BITMAP * load_bitmap_check(char *nomImage);  // Charger une bitmap

/// affichage poney ///
void inimagMech1(t_sequence tab[3]);
void iniseqMech(t_sequence tab[3]);
void iniMech(t_poney tab[3],t_sequence t[3]);

typedef enum e_forme e_forme;
enum e_forme
{
    NUAGE=0,ARC_EN_CIEL=1,BONBON=2
};


#endif // HEADER_H_INCLUDED
