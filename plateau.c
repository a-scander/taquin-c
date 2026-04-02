#include "plateau.h"
#include <stdio.h>
#include <MLV/MLV_all.h>



int InitialisationPlateau(Plateau *P, const char* chemin_image) {
    MLV_Image* image_complete = MLV_load_image(chemin_image);
    MLV_resize_image(image_complete, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (image_complete == NULL) {
        fprintf(stderr, "Erreur : impossible de charger l'image %s\n", chemin_image);
        return -1;
    }

    int i, j;
    for (i = 0; i < NB_LIG; i++) {
        for (j = 0; j < NB_COL; j++) {
            P->bloc[i][j].lig = i;
            P->bloc[i][j].col = j;

           MLV_Image* image = MLV_copy_partial_image(
                image_complete,
                j * TILE_SIZE,   
                i * TILE_SIZE,   
                TILE_SIZE,
                TILE_SIZE
            );
           MLV_resize_image(image, TILE_SIZE - 2*BORDER, TILE_SIZE - 2*BORDER);

            P->bloc[i][j].img =image;
        }
    }

    P->vide.col = NB_COL - 1;
    P->vide.lig = NB_LIG - 1;
    P->vide.img = NULL;

    MLV_free_image(image_complete);

    return 0;
}

void LibererPlateau(Plateau *P) {
    int i, j;
    for (i = 0; i < NB_LIG; i++)
        for (j = 0; j < NB_COL; j++)
            if (P->bloc[i][j].img != NULL)
                MLV_free_image(P->bloc[i][j].img);
}

void AfficherPlateau(Plateau *P) {
    int i, j;

    MLV_draw_filled_rectangle(0, 0, NB_COL * TILE_SIZE, NB_LIG * TILE_SIZE, MLV_COLOR_BLACK);

    for (i = 0; i < NB_LIG; i++) {
        for (j = 0; j < NB_COL; j++) {
            Carre *c = &P->bloc[i][j];

            if (!(i == P->vide.lig && j == P->vide.col)) {
                int x = j * TILE_SIZE + BORDER;
                int y = i * TILE_SIZE + BORDER;

                MLV_draw_image(c->img, x, y);
            }
        }
    }

    MLV_actualise_window();
}


int Deplacer(Plateau *P, int dlig, int dcol) {
    int nvlig = P->vide.lig + dlig;
    int nvcol = P->vide.col + dcol;

    if (nvlig < 0 || nvlig >= NB_LIG || nvcol < 0 || nvcol >= NB_COL)
        return 0;

    Carre tmp = P->bloc[nvlig][nvcol];
    P->bloc[nvlig][nvcol] = P->bloc[P->vide.lig][P->vide.col];
    P->bloc[P->vide.lig][P->vide.col] = tmp;

    P->vide.lig = nvlig;
    P->vide.col = nvcol;

    return 1;
}

void MelangerPlateau(Plateau *P) {
    int dligs[] = {-1, 1,  0, 0};
    int dcols[] = { 0, 0, -1, 1};

    int k;
    for (k = 0; k < 120; k++) {
        int dir;
        do {
            dir = MLV_get_random_integer(0, 3);
        } while (!Deplacer(P, dligs[dir], dcols[dir]));
    }
}

int EstGagne(Plateau *P) {
    int i, j;
    for (i = 0; i < NB_LIG; i++)
        for (j = 0; j < NB_COL; j++)
            if (P->bloc[i][j].lig != i || P->bloc[i][j].col != j)
                return 0; 
    return 1;  
}


void JouerPlateau(Plateau *P) {
    int x, y;

    while (1) {
        MLV_wait_mouse(&x, &y);

        int lig_cliq = y / TILE_SIZE;
        int col_cliq = x / TILE_SIZE;

        int dlig = lig_cliq - P->vide.lig;
        int dcol = col_cliq - P->vide.col;

        if ((dlig == 0 && (dcol == 1 || dcol == -1)) ||
            (dcol == 0 && (dlig == 1 || dlig == -1))) {
            Deplacer(P, dlig, dcol);
            AfficherPlateau(P);

            if (EstGagne(P)) {
                MLV_draw_text(10, 10, "YOU WIN !!!", MLV_COLOR_RED);
                MLV_actualise_window();
                MLV_wait_seconds(3);
                return;  
            }
        }
    }
}


/*Pour debugger*/
void AfficheVide(const Plateau *P) {
    printf("Case vide : ligne = %d, colonne = %d\n", P->vide.lig, P->vide.col);
}

void AfficheBloc(const Plateau *P) {
    int i,j;
    printf("Plateau :\n");
    for(i = 0; i < NB_LIG; i++) {
        for(j = 0; j < NB_COL; j++) {
            printf("[%d,%d] ", P->bloc[i][j].lig, P->bloc[i][j].col);
        }
        printf("\n");
    }
}