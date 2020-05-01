#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#define nb_tourmax 6
#define rayon_nuage 50
#define tire_nuage 3
#define ralentir_nuage 1
#define vitesse_missile_nuage 10
BITMAP *page; // Double buffer
BITMAP *buffer;//triple buffer
BITMAP *decor; // Décor en fonction des niveaux
BITMAP *petitsponey; //Page de chargement du jeu décor
BITMAP *b_nuage; //Bitmap de la tour nuage
BITMAP *b_arc_enciel;//BItmap de la tour arc en ciel
BITMAP *b_bonbon;// Bitmap de la tour bonbon
BITMAP *b_distributeur;//BItmap de la tour du distributeur
BITMAP * b_missile; //Type de missile en fonction du style de tour
BITMAP *regles; // Page des règles du jeu
BITMAP *menu;// Page du menu du jeu
BITMAP *histoire;// Page de cinematique du jeu
BITMAP *niveau; // Interface du niveau
BITMAP *donjon;
BITMAP *explo[8];
BITMAP *b_distributeur;

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
    int depx_init;//des unité vont ralentir les poney
    int depy;
    int depy_init;//des unité vont ralentir les poney
    int tx;
    int ty;
    int ptsdebonheur;//point de vie au debut
    int ptsbonPres;//point de vie instant t
    int val; //numero de poney
    int aff;//afficher ou non
    int att;// attaque du poney
    t_sequence seq;
    int numImg[4] ;
}t_poney;


typedef struct t_missile t_missile;
struct t_missile
{
    int pos_x;
    int pos_y;
    int vitesse;
    int cible_x;
    int cible_y;
    int dep_x;
    int dep_y;
    int degat;
    int existe;

};


typedef struct t_tour t_tour;
struct t_tour
{
    int pos_x;
    int pos_y;
    int rayon_action;
    int type_tour;
    int frequence_tir;
<<<<<<< HEAD
    int test;
    int numeImg;
=======
    int degat;
    int active;
    int target;
>>>>>>> 7f818714b2b4ca04b93d147aaf1b73d9deba24bc
};

typedef struct t_nuages t_nuages;
struct t_nuages
{
    int pos_x;
    int pos_y;
    int rayon_action;
    int ralentir;
    int active;
};

// SOus programme de l'architecture du jeu
void boucle_de_jeu();
void regles_du_jeu();
void menu_jeu();
void jeu_presentation();
void choix_niveau();
void initialiser_niveau(int niv);
void cinematique(int niv);

void initalisation();

// Sous programme tours
void initialise_tour(t_tour * nuage);

/// affichage graphique ///
BITMAP * load_bitmap_check(char *nomImage);  // Charger une bitmap

/// affichage poney ///
void inimagMech1(t_sequence tab[3]);
void iniseqMech(t_sequence tab[3]);
void iniMech(t_poney tab[3],t_sequence t[3]);
void affichageMech(t_poney act[100],int nbAct);
t_poney Deplacement(t_poney poney, BITMAP* TEST,int* a);

/// creation tableau acteur ///
int creaTabActeur(t_poney acteur[100],t_poney typeperso[3],int i,int difficulte);


/// sauvegarde de partie///
void sauvegarde_partie(t_poney tab[100],int nbPoney,int nbPoneyAffiche);
int lire_niveau();
void sauvegarde_niveau(int diff);

/// initialisation image explosion///
void inimagCoeur(BITMAP* tab[8]);


typedef enum e_forme e_forme;
enum e_forme
{
    NUAGE=0,ARC_EN_CIEL=1,BONBON=2
};


#endif // HEADER_H_INCLUDED
