// Copyright 2018 Damian Stefania-Dorina 312CD

// generate a piece without the white margin
void choose_piece(char c, int ***Piece, int *lines, int *coloumns) {
    int i, j, **Piece2 = NULL;
    // generate piece type
    switch (c) {
        case 'O':
                O_units(&Piece2, lines, coloumns);
                break;
        case 'I':
                I_units(&Piece2, lines, coloumns);
                break;
        case 'S':
                S_units(&Piece2, lines, coloumns);
                break;
        case 'Z':
                Z_units(&Piece2, lines, coloumns);
                break;
        case 'L':
                L_units(&Piece2, lines, coloumns);
                break;
        case 'J':
                J_units(&Piece2, lines, coloumns);
                break;
        case 'T':
                T_units(&Piece2, lines, coloumns);
                break;
    }

    // cut out the white margin
    *Piece = NULL;
    *Piece = malloc((*lines - 2) * sizeof(int*));
    for (i = 0; i < *lines - 2; i++) {
        (*Piece)[i] = calloc(*coloumns - 2, sizeof(int));
        for (j = 0; j < *coloumns - 2; j ++) {
            (*Piece)[i][j] = Piece2[i + 1][j + 1];
        }
    }

    for (i = 0; i < *lines; i++) {
        free(Piece2[i]);
    }
    free(Piece2);

    (*lines) -= 2;
    (*coloumns) -= 2;
}

// checks collision and returns 0 if the piece can go down one line
// and 1 otherwise
int collision(int **GAME, int **Piece, int l, int c,
                int coordinate, int current_line) {
    int i, j;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            if (GAME[current_line + i + 1][coordinate + j] != 0
                && Piece[i][j] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// add the piece to the game map
void add_piece_to_game_map(int ***GAME, int **Piece, int l, int c,
                            int current_line, int coordinate) {
    int i, j;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            (*GAME)[current_line + i][coordinate + j] += Piece[i][j];
        }
    }
}

// returns 1 if a piece does not fit entirely on the white part
// and 0 otherwise
int end_game(int **GAME, int coloumns) {
    int i, j;
    for (i = 3; i >= 0; i--) {
        for (j = 0; j < coloumns; j++) {
            if (GAME[i][j] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// return index of full line and -1 if it does not exist
int line_to_delete(int **GAME, int lines, int coloumns) {
    int i, j, ok;
    for (i = 0; i < lines; i++) {
        ok = 1;
        for (j = 0; j < coloumns && ok == 1; j++) {
            if (GAME[i][j] == 0) {
                ok = 0;
            }
        }
        if (ok == 1) {
            return i;
        }
    }
    return -1;
}

// delete the specified full line
void delete_full_line(int ***GAME, int lines, int coloumns, int full_line) {
    int i, j;
    for (i = full_line; i >= 4; i--) {
        for (j = 0; j < coloumns; j++) {
            (*GAME)[i][j] = (*GAME)[i - 1][j];
        }
    }
}

// make piece go down
void go_down(int ***GAME, int l1, int c1, int *ok,
                int **Piece, int l2, int c2, int coordinate) {
    int current_line = 0, col, full_line;
    // check for collision
    col = collision(*GAME, Piece, l2, c2, coordinate, current_line);
    while (col == 0 && current_line + l2 - 1 < l1 - 1) {
        current_line++;
        if (current_line + l2 - 1 < l1 - 1) {
            col = collision(*GAME, Piece, l2, c2, coordinate, current_line);
        }
    }

    add_piece_to_game_map(GAME, Piece, l2, c2, current_line, coordinate);

    // check end game condition
    if (end_game(*GAME, c1) == 1) {
        *ok = 0;
    } else {
        // delete full lines
        full_line = line_to_delete((*GAME), l1, c1);
        while (full_line >= 0) {
            delete_full_line(GAME, l1, c1, full_line);
            full_line = line_to_delete((*GAME), l1, c1);
        }
    }
}

// play the game
void play(FILE *in, int ***GAME, int N, int game_lines, int game_coloumns) {
    int i, j, ok = 1, **Piece, lines, coloumns, rotation, coordinate;
    char name;

    for (i = 1; i <= N && ok == 1; i++) {
        // read name 2 times as the first character is \n
        fscanf(in, "%c", &name);
        fscanf(in, "%c", &name);
        fscanf(in, "%d", &rotation);
        fscanf(in, "%d", &coordinate);

        choose_piece(name, &Piece, &lines, &coloumns);

        for (j = 1; j <= rotation / 90; j++) {
            rotate_90_degrees(&Piece, &lines, &coloumns);
        }

        go_down(GAME, game_lines, game_coloumns, &ok,
                Piece, lines, coloumns, coordinate);

        for (j = 0; j < lines; j++) {
            free(Piece[j]);
        }
        free(Piece);
    }
}
