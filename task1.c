// Copyright 2018 Damian Stefania-Dorina 312CD

#include <stdio.h>
#include <stdlib.h>
#include "./bmp_header.h"
#include "./functions.h"

int main() {
    bmp_fileheader f_header;
    bmp_infoheader i_header;
    int **IMG = NULL, lines, coloumns, i;
    FILE *p;

    set_bmp_info(&f_header, &i_header);

    O_units(&IMG, &lines, &coloumns);
    p = fopen("piesa_O.bmp", "wb");
    write_bmp(p, IMG, lines, coloumns, f_header, i_header);
    for (i = 0; i < lines; i++) {
        free(IMG[i]);
    }
    free(IMG);

    I_units(&IMG, &lines, &coloumns);
    p = fopen("piesa_I.bmp", "wb");
    write_bmp(p, IMG, lines, coloumns, f_header, i_header);
    for (i = 0; i < lines; i++) {
        free(IMG[i]);
    }
    free(IMG);

    S_units(&IMG, &lines, &coloumns);
    p = fopen("piesa_S.bmp", "wb");
    write_bmp(p, IMG, lines, coloumns, f_header, i_header);
    for (i = 0; i < lines; i++) {
        free(IMG[i]);
    }
    free(IMG);

    Z_units(&IMG, &lines, &coloumns);
    p = fopen("piesa_Z.bmp", "wb");
    write_bmp(p, IMG, lines, coloumns, f_header, i_header);
    for (i = 0; i < lines; i++) {
        free(IMG[i]);
    }
    free(IMG);

    L_units(&IMG, &lines, &coloumns);
    p = fopen("piesa_L.bmp", "wb");
    write_bmp(p, IMG, lines, coloumns, f_header, i_header);
    for (i = 0; i < lines; i++) {
        free(IMG[i]);
    }
    free(IMG);

    J_units(&IMG, &lines, &coloumns);
    p = fopen("piesa_J.bmp", "wb");
    write_bmp(p, IMG, lines, coloumns, f_header, i_header);
    for (i = 0; i < lines; i++) {
        free(IMG[i]);
    }
    free(IMG);

    T_units(&IMG, &lines, &coloumns);
    p = fopen("piesa_T.bmp", "wb");
    write_bmp(p, IMG, lines, coloumns, f_header, i_header);
    for (i = 0; i < lines; i++) {
        free(IMG[i]);
    }
    free(IMG);

    return 0;
}
