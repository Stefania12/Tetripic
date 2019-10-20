// Copyright 2018 Damian Stefania-Dorina 312CD

#include <stdio.h>
#include <stdlib.h>
#include "./bmp_header.h"
#include "./functions.h"
#include "./game.h"

int main() {
    bmp_fileheader f_header;
    bmp_infoheader i_header;
    set_bmp_info(&f_header, &i_header);

    int N, H, L, i, j, **GAME = NULL;
    FILE *in = fopen("cerinta3.in", "r");

    fscanf(in, "%d", &N);
    fscanf(in, "%d", &H);
    fscanf(in, "%d", &L);

    // create game map unit matrix
    GAME = malloc((H + 4) * sizeof(int*));

    for (i = 0; i < H + 4; i++) {
        GAME[i] = calloc(L, sizeof(int));
    }

    play(in, &GAME, N, H + 4, L);
    fclose(in);

    // set unoccupied areas to black
    for (i = 4; i < H + 4; i++) {
        for (j = 0; j < L; j++) {
            if (GAME[i][j] == 0) {
                GAME[i][j] = -1;
            }
        }
    }

    FILE *out = fopen("task3.bmp", "wb");

    write_bmp(out, GAME, H + 4, L, f_header, i_header);

    for (i = 0; i < H + 4; i++) {
        free(GAME[i]);
    }
    free(GAME);

    return 0;
}
