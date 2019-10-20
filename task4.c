// Copyright 2018 Damian Stefania-Dorina 312CD

#include <stdio.h>
#include <stdlib.h>
#include "./bmp_header.h"
#include "./functions.h"
#include "./game.h"

int main() {
    bmp_fileheader f_header;
    bmp_infoheader i_header;
    int padding, **GAME = NULL, i, j, lines, coloumns, N;
    FILE *img = fopen("cerinta4.bmp", "rb");

    read_bmp_info(img, &f_header, &i_header, &padding);
    lines = i_header.height / 10;
    coloumns = i_header. width /10;
    read_bmp(img, &GAME, lines, coloumns, padding);
    fclose(img);

    FILE *in = fopen("cerinta4.in", "r");
    fscanf(in, "%d", &N);

    play(in, &GAME, N, lines, coloumns);
    fclose(in);

    // set unoccupied areas to black
    for (i = 4; i < lines; i++) {
        for (j = 0; j < coloumns; j++) {
            if (GAME[i][j] == 0) {
                GAME[i][j] = -1;
            }
        }
    }

    FILE *out = fopen("task4.bmp", "wb");

    write_bmp(out, GAME, lines, coloumns, f_header, i_header);
    for (i = 0; i < lines + 2; i++) {
        free(GAME[i]);
    }
    free(GAME);

    return 0;
}
