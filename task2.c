// Copyright 2018 Damian Stefania-Dorina 312CD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./bmp_header.h"
#include "./functions.h"

// structure for output files
typedef struct rotiri {
    char r_90[20], r_180[20], r_270[20];
} rotiri;

// generate the rotations for each piece
void generate_rotations(bmp_fileheader f_header, bmp_infoheader i_header,
                        rotiri nume[7]) {
    int i, j, lines, coloumns, **IMG = NULL;
    FILE *p;
    // pointer to each function that generates piece
    void (*piece_gen[7])(int ***IMG, int *lines, int *coloumns);
    piece_gen[0] = O_units;
    piece_gen[1] = I_units;
    piece_gen[2] = S_units;
    piece_gen[3] = Z_units;
    piece_gen[4] = L_units;
    piece_gen[5] = J_units;
    piece_gen[6] = T_units;

    // generate rotations for each piece
    for (i = 0; i < 7; i++) {
        (piece_gen[i])(&IMG, &lines, &coloumns);
        p = fopen(nume[i].r_90, "wb");
        rotate_90_degrees(&IMG, &lines, &coloumns);
        write_bmp(p, IMG, lines, coloumns, f_header, i_header);

        p = fopen(nume[i].r_180, "wb");
        rotate_90_degrees(&IMG, &lines, &coloumns);
        write_bmp(p, IMG, lines, coloumns, f_header, i_header);

        p = fopen(nume[i].r_270, "wb");
        rotate_90_degrees(&IMG, &lines, &coloumns);
        write_bmp(p, IMG, lines, coloumns, f_header, i_header);
        for (j = 0; j < lines; j++) {
            free(IMG[j]);
        }
        free(IMG);
    }
}

int main() {
    bmp_fileheader f_header;
    bmp_infoheader i_header;
    rotiri nume[7];

    // set name for each bmp
    strcpy(nume[0].r_90, "piesa_O_90.bmp");
    strcpy(nume[0].r_180, "piesa_O_180.bmp");
    strcpy(nume[0].r_270, "piesa_O_270.bmp");

    strcpy(nume[1].r_90, "piesa_I_90.bmp");
    strcpy(nume[1].r_180, "piesa_I_180.bmp");
    strcpy(nume[1].r_270, "piesa_I_270.bmp");

    strcpy(nume[2].r_90, "piesa_S_90.bmp");
    strcpy(nume[2].r_180, "piesa_S_180.bmp");
    strcpy(nume[2].r_270, "piesa_S_270.bmp");

    strcpy(nume[3].r_90, "piesa_Z_90.bmp");
    strcpy(nume[3].r_180, "piesa_Z_180.bmp");
    strcpy(nume[3].r_270, "piesa_Z_270.bmp");

    strcpy(nume[4].r_90, "piesa_L_90.bmp");
    strcpy(nume[4].r_180, "piesa_L_180.bmp");
    strcpy(nume[4].r_270, "piesa_L_270.bmp");

    strcpy(nume[5].r_90, "piesa_J_90.bmp");
    strcpy(nume[5].r_180, "piesa_J_180.bmp");
    strcpy(nume[5].r_270, "piesa_J_270.bmp");

    strcpy(nume[6].r_90, "piesa_T_90.bmp");
    strcpy(nume[6].r_180, "piesa_T_180.bmp");
    strcpy(nume[6].r_270, "piesa_T_270.bmp");

    set_bmp_info(&f_header, &i_header);
    generate_rotations(f_header, i_header, nume);

    return 0;
}
