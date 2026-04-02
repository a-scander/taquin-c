#include "graphique.h"
#include <MLV/MLV_all.h>



#define WINDOW_WIDTH  512
#define WINDOW_HEIGHT  512

void open_window(void) {
    MLV_create_window(
        "Taquin",
        "Taquin",
        WINDOW_WIDTH ,
        WINDOW_HEIGHT 
    );
}

void close_window(void) {
    MLV_free_window();
}

