#include <MLV/MLV_all.h>

#ifndef PLATEAU_H
#define PLATEAU_H

#define NB_COL 4          /* Nombre de colonnes du plateau */
#define NB_LIG 4          /* Nombre de lignes du plateau */
#define TILE_SIZE 128     /* Taille d'une tuile en pixels */
#define WINDOW_WIDTH  512 /* Largeur de la fenêtre */
#define WINDOW_HEIGHT 512 /* Hauteur de la fenêtre */
#define BORDER 3          /* Bordure entre les tuiles */

typedef struct {
    int lig;        /* Ligne d'origine de la tuile */
    int col;        /* Colonne d'origine de la tuile */
    MLV_Image* img; /* Image MLV associée à la tuile */
} Carre;

typedef struct {
    Carre vide;                    /* Case vide du plateau */
    Carre bloc[NB_LIG][NB_COL];   /* Tableau de toutes les tuiles */
} Plateau;

int  InitialisationPlateau(Plateau *P, const char* chemin_image); /* Charge et découpe l'image en tuiles */
void LibererPlateau(Plateau *P);                                   /* Libère les images MLV allouées */
void AfficherPlateau(Plateau *P);                                  /* Redessine le plateau à l'écran */
int  Deplacer(Plateau *P, int dlig, int dcol);                     /* Déplace la case vide dans une direction */
void MelangerPlateau(Plateau *P);                                  /* Mélange le plateau aléatoirement */
void JouerPlateau(Plateau *P);                                     /* Boucle principale du jeu */
int  EstGagne(Plateau *P);                                         /* Vérifie si le puzzle est résolu */
void AfficheBloc(const Plateau *P);                                /* Debug : affiche les positions des tuiles */
void AfficheVide(const Plateau *P);                                /* Debug : affiche la position de la case vide */

#endif