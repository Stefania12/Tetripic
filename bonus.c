// Copyright 2018 Damian Stefania-Dorina 312CD

#include <stdio.h>
#include <stdlib.h>
#include "./bmp_header.h"
#include "./functions.h"
#include "./game.h"

// structure for the information on each piece found
typedef struct piece_info {
    char type;
    int rotation, coloumn;
} piece_info;

// return the piece type from the codified color
char piece_type(int n) {
    if (n == 1) {
        return 'O';
    } else {
        if (n == 2) {
            return 'I';
        } else {
            if (n == 3) {
                return 'S';
            } else {
                if (n == 4) {
                    return 'Z';
                } else {
                    if (n == 5) {
                        return 'L';
                    } else {
                        if (n == 6) {
                            return 'J';
                        } else {
                            return 'T';
                        }
                    }
                }
            }
        }
    }
}

// board the game unit map
void board(int ***GAME, int *lines, int *coloumns) {
    int i, j;
    // move to the right
    for (i = 0; i < *lines; i++) {
        for (j = *coloumns; j > 0; j--) {
            (*GAME)[i][j] = (*GAME)[i][j - 1];
        }
    }
    // move down
    for (j = 1; j < *coloumns + 1; j++) {
        for (i = *lines; i > 0; i--) {
            (*GAME)[i][j] = (*GAME)[i - 1][j];
        }
    }
    (*lines) += 2;
    (*coloumns) += 2;

    // board
    for (i = 0; i < *lines; i++) {
        (*GAME)[i][0] = -1;
        (*GAME)[i][*coloumns - 1] = -1;
    }
    for (j = 0; j < *coloumns; j++) {
        (*GAME)[0][j] = -1;
        (*GAME)[*lines - 1][j] = -1;
    }
}

// find color block and set its extremities and number of
// units of the specified codified color
void find_color_group(int **GAME, int val, int x, int y, int *nr_units,
                        int coord_x[4], int coord_y[4],
                        int *top, int *bottom, int *left, int *right,
                        int ***viz) {
    int i, X, Y;

    (*nr_units) += 1;
    (*viz)[x][y] = 1;

    // check for new extremities
    if (x < *top) {
        *top = x;
    }
    if (x > *bottom) {
        *bottom = x;
    }
    if (y < *left) {
        *left = y;
    }
    if (y > *right) {
        *right = y;
    }
    // move to the next unit of the same value
    for (i = 0; i < 4; i++) {
        X = x + coord_x[i];
        Y = y + coord_y[i];
        if (GAME[X][Y] == val && (*viz)[X][Y] == 0) {
            find_color_group(GAME, val, X, Y, nr_units, coord_x, coord_y,
                            top, bottom, left, right, viz);
        }
    }
}

// find next unit within the extremities
void next_unit(int **GAME, int val, int top, int bottom,
                int left, int right, int *x, int *y) {
    if (*y + 1 > right) {
        *y = left;
        (*x) += 1;
    } else {
        (*y) += 1;
    }
}

// identify the pieces from the color group
void identify_piece(int ***GAME, int val, int x, int y, int nr_pieces,
                    int top, int bottom, int left, int right, int *found,
                    int **Piece, char type, int lines, int coloumns,
                    piece_info **pieces, int *current_piece) {
    int i, j, r, l = lines, c = coloumns, is_fit, **Piece2, X = x, Y = y;

    // copy the piece to be able to rotate it properly
    Piece2 = malloc(l * sizeof(int*));
    for (i = 0; i < l; i ++) {
        Piece2[i] = calloc(c, sizeof(int));
        for (j = 0; j < c; j++) {
            Piece2[i][j] = Piece[i][j];
        }
    }

    // check for each rotation if the piece fits within the color block
    for (r = 0; r <= 3 && *found < nr_pieces; r++) {
        is_fit = 1;
        // check if it fits
        if (x + l - 1 <= bottom && y + c - 1 <= right) {
            for (i = 0; i < l && is_fit == 1; i++) {
                for (j = 0; j < c && is_fit == 1; j++) {
                    if ((*GAME)[x + i][y + j] != val && Piece2[i][j] == val) {
                        is_fit = 0;
                    }
                }
            }
        } else {
            is_fit = 0;
        }

        // if it fits, clear the game map where the piece was
        if (is_fit == 1) {
            (*found) += 1;
            for (i = 0; i < l; i++) {
                for (j = 0; j < c; j++) {
                    if (Piece2[i][j] == val) {
                        (*GAME)[x + i][y + j] = 0;
                    }
                }
            }

            // check for new piece
            if (*found < nr_pieces) {
                next_unit(*GAME, val, top, bottom, left, right, &X, &Y);
                identify_piece(GAME, val, X, Y, nr_pieces,
                                top, bottom, left, right, found,
                                Piece, type, lines, coloumns,
                                pieces, current_piece);
            }

            // choice was right, retain piece info
            if (*found == nr_pieces) {
                (*pieces)[*current_piece].type = type;
                (*pieces)[*current_piece].rotation = r % 4 * 90;
                (*pieces)[*current_piece].coloumn = y - 1;
                (*current_piece) += 1;
            } else {
                // the piece was not good, add it back to the map
                for (i = 0 ; i < l; i++) {
                    for (j = 0; j < c; j++) {
                        (*GAME)[x + i][y + j] += Piece2[i][j];
                    }
                }
            }
        }

    rotate_90_degrees(&Piece2, &l, &c);
    }

    // the coordinates were not good
    if (*found < nr_pieces) {
        next_unit(*GAME, val, top, bottom, left, right, &X, &Y);
        identify_piece(GAME, val, X, Y, nr_pieces, top, bottom, left, right,
                        found, Piece, type, lines, coloumns,
                        pieces, current_piece);
    }

    for (i = 0; i < l; i++) {
        free(Piece2[i]);
    }
    free(Piece2);
}

int main() {
    bmp_fileheader f_header;
    bmp_infoheader i_header;
    int padding, **GAME = NULL, i, j, k, lines, coloumns,
        coord_x[4] = {-1, 0, 1, 0}, coord_y[4] = {0, 1, 0, -1},
        nr_units, top, bottom, left, right, **viz = NULL, x, y,
        **Piece = NULL, l, c, nr_pieces, found, total = 0, current_piece = 0;
    char type;
    piece_info *pieces = NULL;
    FILE *in = fopen("bonus.bmp", "rb");

    read_bmp_info(in, &f_header, &i_header, &padding);
    lines = i_header.height / 10;
    coloumns = i_header. width / 10;
    read_bmp(in, &GAME, lines, coloumns, padding);
    fclose(in);

    pieces = malloc(lines * coloumns / 4 * sizeof(piece_info));

    board(&GAME, &lines, &coloumns);

    // matrix for visited areas
    viz = malloc(lines * sizeof(int*));
    for (i = 0; i < lines; i++) {
        viz[i] = calloc(coloumns, sizeof(int));
    }

    // find pieces within each color block
    for (i = 1; i < lines - 1; i++) {
        for (j = 1; j < coloumns - 1; j++) {
            if (GAME[i][j] != 0) {
                x = i;
                y = j;
                top = x;
                bottom = x;
                left = y;
                right = y;
                nr_units = 0;

                find_color_group(GAME, GAME[i][j], x, y, &nr_units,
                                    coord_x, coord_y,
                                    &top, &bottom, &left, &right, &viz);

                nr_pieces = nr_units / 4;
                total += nr_pieces;
                found = 0;
                type = piece_type(GAME[i][j]);
                choose_piece(type, &Piece, &l, &c);

                identify_piece(&GAME, GAME[i][j], top, left, nr_pieces,
                                top, bottom, left, right, &found,
                                Piece, type, l, c, &pieces, &current_piece);

                for (k = 0; k < l; k++) {
                    free(Piece[k]);
                }
                free(Piece);
            }
        }
    }


    for (i = 0; i < lines; i++) {
        free(GAME[i]);
        free(viz[i]);
    }
    free(GAME);
    free(viz);

    FILE *out = fopen("bonus.out", "w");
    fprintf(out, "%d\n", total);
    for (i = 0; i < total; i++) {
        fprintf(out, "%c %d %d\n",
                pieces[i].type, pieces[i].rotation, pieces[i].coloumn);
    }

    free(pieces);
    fclose(out);

    return 0;
}
