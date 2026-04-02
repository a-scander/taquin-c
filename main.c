#include <MLV/MLV_all.h>
#include "graphique.h"
#include "plateau.h"



int main(int argc, char* argv[]) {
    Plateau P;

    if (argc < 2) {
        fprintf(stderr, "Usage : %s <image.png>\n", argv[0]);
        return 1;
    }

    open_window();

    if (InitialisationPlateau(&P, argv[1]) == -1) {
        close_window();
        return 1;
    }

    MelangerPlateau(&P);
    AfficherPlateau(&P);
    JouerPlateau(&P);

    LibererPlateau(&P);
    close_window();

    return 0;
}