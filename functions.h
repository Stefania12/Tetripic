// Copyright 2018 Damian Stefania-Dorina 312CD

// sets default bmp info
void set_bmp_info(bmp_fileheader *f_header, bmp_infoheader *i_header) {
    f_header->fileMarker1 = 'B';
    f_header->fileMarker2 = 'M';
    f_header->unused1 = 0;
    f_header->unused2 = 0;
    f_header->imageDataOffset = 54;
    i_header->biSize = 40;
    i_header->planes = 1;
    i_header->bitPix = 24;
    i_header->biCompression = 0;
    i_header->biXPelsPerMeter = 0;
    i_header->biYPelsPerMeter = 0;
    i_header->biClrUsed = 0;
    i_header->biClrImportant = 0;
}

// writes bmp fileheader and infoheader
void write_bmp_info(FILE *p, bmp_fileheader f_header, bmp_infoheader i_header) {
    fwrite(&f_header.fileMarker1, sizeof(unsigned char), 1, p);
    fwrite(&f_header.fileMarker2, sizeof(unsigned char), 1, p);
    fwrite(&f_header.bfSize, sizeof(int), 1, p);
    fwrite(&f_header.unused1, sizeof(unsigned short), 1, p);
    fwrite(&f_header.unused2, sizeof(unsigned short), 1, p);
    fwrite(&f_header.imageDataOffset, sizeof(int), 1, p);

    fwrite(&i_header.biSize, sizeof(unsigned int), 1, p);
    fwrite(&i_header.width, sizeof(signed int), 1, p);
    fwrite(&i_header.height, sizeof(signed int), 1, p);
    fwrite(&i_header.planes, sizeof(unsigned short), 1, p);
    fwrite(&i_header.bitPix, sizeof(unsigned short), 1, p);
    fwrite(&i_header.biCompression, sizeof(unsigned int), 1, p);
    fwrite(&i_header.biSizeImage, sizeof(unsigned int), 1, p);
    fwrite(&i_header.biXPelsPerMeter, sizeof(int), 1, p);
    fwrite(&i_header.biYPelsPerMeter, sizeof(int), 1, p);
    fwrite(&i_header.biClrUsed, sizeof(unsigned int), 1, p);
    fwrite(&i_header.biClrImportant, sizeof(unsigned int), 1, p);
}

// create piece O unit matrix with white margin
void O_units(int ***IMG, int *lines, int *coloumns) {
    int i;
    *lines = 4;
    *coloumns = 4;
    *IMG = malloc(*lines * sizeof(int *));
    for (i = 0; i < *lines; i++) {
        (*IMG)[i] = calloc(*coloumns, sizeof(int));
    }

    (*IMG)[1][1] = 1;
    (*IMG)[1][2] = 1;
    (*IMG)[2][1] = 1;
    (*IMG)[2][2] = 1;
}

// create piece I unit matrix with white margin
void I_units(int ***IMG, int *lines, int *coloumns) {
    int i;
    *lines = 6;
    *coloumns = 3;
    *IMG = malloc((*lines) * sizeof(int *));
    for (i = 0; i < *lines; i++) {
        (*IMG)[i] = calloc(*coloumns, sizeof(int));
    }

    (*IMG)[1][1] = 2;
    (*IMG)[2][1] = 2;
    (*IMG)[3][1] = 2;
    (*IMG)[4][1] = 2;
}

// create piece S unit matrix with white margin
void S_units(int ***IMG, int *lines, int *coloumns) {
    int i;
    *lines = 4;
    *coloumns = 5;
    *IMG = malloc(*lines * sizeof(int *));
    for (i = 0; i < *lines; i++) {
        (*IMG)[i] = calloc(*coloumns, sizeof(int));
    }

    (*IMG)[1][2] = 3;
    (*IMG)[1][3] = 3;
    (*IMG)[2][1] = 3;
    (*IMG)[2][2] = 3;
}

// create piece Z unit matrix with white margin
void Z_units(int ***IMG, int *lines, int *coloumns) {
    int i;
    *lines = 4;
    *coloumns = 5;
    *IMG = malloc(*lines * sizeof(int *));
    for (i = 0; i < *lines; i++) {
        (*IMG)[i] = calloc(*coloumns, sizeof(int));
    }

    (*IMG)[1][1] = 4;
    (*IMG)[1][2] = 4;
    (*IMG)[2][2] = 4;
    (*IMG)[2][3] = 4;
}

// create piece L unit matrix with white margin
void L_units(int ***IMG, int *lines, int *coloumns) {
    int i;
    *lines = 5;
    *coloumns = 4;
    *IMG = malloc(*lines * sizeof(int *));
    for (i = 0; i < *lines; i++) {
        (*IMG)[i] = calloc(*coloumns, sizeof(int));
    }

    (*IMG)[1][1] = 5;
    (*IMG)[2][1] = 5;
    (*IMG)[3][1] = 5;
    (*IMG)[3][2] = 5;
}

// create piece J unit matrix with white margin
void J_units(int ***IMG, int *lines, int *coloumns) {
    int i;
    *lines = 5;
    *coloumns = 4;
    *IMG = malloc(*lines * sizeof(int *));
    for (i = 0; i < *lines; i++) {
        (*IMG)[i] = calloc(*coloumns, sizeof(int));
    }

    (*IMG)[1][2] = 6;
    (*IMG)[2][2] = 6;
    (*IMG)[3][1] = 6;
    (*IMG)[3][2] = 6;
}

// create piece T unit matrix with white margin
void T_units(int ***IMG, int *lines, int *coloumns) {
    int i;
    *lines = 4;
    *coloumns = 5;
    *IMG = malloc(*lines * sizeof(int *));
    for (i = 0; i < *lines; i++) {
        (*IMG)[i] = calloc(*coloumns, sizeof(int));
    }

    (*IMG)[1][1] = 7;
    (*IMG)[1][2] = 7;
    (*IMG)[1][3] = 7;
    (*IMG)[2][2] = 7;
}

// choose r, g and b values for the codified colour
void choose_colour(int value, int *r, int *g, int *b) {
    switch (value) {
        case -1:
                *r = 0;
                *g = 0;
                *b = 0;
                break;
        case 0:
                *r = 255;
                *g = 255;
                *b = 255;
                break;
        case 1:
                *r = 255;
                *g = 255;
                *b = 0;
                break;
        case 2:
                *r = 0;
                *g = 0;
                *b = 255;
                break;
        case 3:
                *r = 255;
                *g = 0;
                *b = 0;
                break;
        case 4:
                *r = 0;
                *g = 255;
                *b = 0;
                break;
        case 5:
                *r = 255;
                *g = 140;
                *b = 0;
                break;
        case 6:
                *r = 255;
                *g = 0;
                *b = 255;
                break;
        case 7:
                *r = 130;
                *g = 0;
                *b = 255;
                break;
    }
}

// return codified value of the color
int choose_colour_value(unsigned char r, unsigned char g, unsigned char b) {
    if (r == 0) {
        if (g == 0) {
            if (b == 0) {
                return 0;
            } else {
                return 2;
            }
        } else {
            return 4;
        }
    } else {
        if (r == 130) {
            return 7;
        } else {
            if (g == 0) {
                if (b == 0) {
                    return 3;
                } else {
                    return 6;
                }
            } else {
                if (g == 140) {
                    return 5;
                } else {
                    if (b == 0) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
        }
    }
}

// write bmp
void write_bmp(FILE *p, int **IMG, int lines, int coloumns,
                bmp_fileheader f_header, bmp_infoheader i_header) {
    int zero = 0, i, j, k, l, padding, r, g, b;

    // set fileheader and infoheader values and write them
    i_header.width = coloumns * 10;
    i_header.height = lines * 10;
    padding = (4 - i_header.width * 3 % 4) % 4;
    i_header.biSizeImage = i_header.width * i_header.height * 3 +
                            padding * i_header.height;
    f_header.bfSize = i_header.biSizeImage + f_header.imageDataOffset;
    write_bmp_info(p, f_header, i_header);

    // write the bmp image
    for (i = lines - 1 ; i >= 0; i--) {
        for (l = 0; l < 10; l++) {
            for (j = 0; j < coloumns; j++) {
                choose_colour(IMG[i][j], &r, &g, &b);
                for (k = 0; k < 10; k++) {
                    fwrite(&b, sizeof(unsigned char), 1, p);
                    fwrite(&g, sizeof(unsigned char), 1, p);
                    fwrite(&r, sizeof(unsigned char), 1, p);
                }
            }
            // padding
            for (k = 0; k < padding; k++) {
                fwrite(&zero, sizeof(unsigned char), 1, p);
            }
        }
    }
    fclose(p);
}

// rotate a matrix 90 degrees clockwise
void rotate_90_degrees(int ***IMG, int *lines, int *coloumns) {
    int i, j, **IMG2 = NULL, lines2, coloumns2;
    lines2 = *coloumns;
    coloumns2 = *lines;

    IMG2 = malloc(lines2 * sizeof(int*));
    for (i = 0; i < lines2; i++) {
        IMG2[i] = calloc(coloumns2, sizeof(int));
    }

    // rotated matrix
    for (i = 0; i < *lines; i++) {
        for (j = 0; j < *coloumns; j++) {
            IMG2[j][coloumns2 -1 - i] = (*IMG)[i][j];
        }
    }

    for (i = 0; i < *lines; i++) {
        free((*IMG)[i]);
    }
    free(*IMG);

    // assign new values to the initial matrix
    *IMG = NULL;
    *IMG = malloc(lines2 * sizeof(int*));
    for (i = 0; i < lines2; i++) {
        (*IMG)[i] = calloc(coloumns2, sizeof(int));
        for (j = 0; j < coloumns2; j++) {
            (*IMG)[i][j] = IMG2[i][j];
        }
    }
    for (i = 0; i < lines2; i++) {
        free(IMG2[i]);
    }
    free(IMG2);
    *lines = lines2;
    *coloumns = coloumns2;
}

// read bmp fileheader and infoheader and set padding
void read_bmp_info(FILE *p, bmp_fileheader *f_header,
                    bmp_infoheader *i_header, int *padding) {
    fread(&f_header->fileMarker1, sizeof(unsigned char), 1, p);
    fread(&f_header->fileMarker2, sizeof(unsigned char), 1, p);
    fread(&f_header->bfSize, sizeof(int), 1, p);
    fread(&f_header->unused1, sizeof(unsigned short), 1, p);
    fread(&f_header->unused2, sizeof(unsigned short), 1, p);
    fread(&f_header->imageDataOffset, sizeof(int), 1, p);

    fread(&i_header->biSize, sizeof(unsigned int), 1, p);
    fread(&i_header->width, sizeof(signed int), 1, p);
    fread(&i_header->height, sizeof(signed int), 1, p);
    fread(&i_header->planes, sizeof(unsigned short), 1, p);
    fread(&i_header->bitPix, sizeof(unsigned short), 1, p);
    fread(&i_header->biCompression, sizeof(unsigned int), 1, p);
    fread(&i_header->biSizeImage, sizeof(unsigned int), 1, p);
    fread(&i_header->biXPelsPerMeter, sizeof(int), 1, p);
    fread(&i_header->biYPelsPerMeter, sizeof(int), 1, p);
    fread(&i_header->biClrUsed, sizeof(unsigned int), 1, p);
    fread(&i_header->biClrImportant, sizeof(unsigned int), 1, p);
    *padding = (i_header->biSizeImage -
                i_header->width * i_header->height * 3) / i_header->height;
}

// read unit matrix from the bmp
void read_bmp(FILE *p, int ***GAME, int lines, int coloumns, int padding) {
    int i, j;
    unsigned char r, g, b;

    // add 2 more lines and coloumns when boarding is needed
    *GAME = malloc((lines + 2) * sizeof(int*));
    for (i = 0; i < lines + 2; i++) {
        (*GAME)[i] = calloc(coloumns + 2, sizeof(int));
    }

    for (i = lines - 1; i >= 0; i--) {
        for (j = 0; j < coloumns; j++) {
            fread(&b, sizeof(unsigned char), 1, p);
            fread(&g, sizeof(unsigned char), 1, p);
            fread(&r, sizeof(unsigned char), 1, p);
            (*GAME)[i][j] = choose_colour_value(r, g, b);
            // skip next 9 pixels
            fseek(p, 9 * 3, SEEK_CUR);
        }
        // skip padding and the next 9 lines of pixels
        fseek(p, padding, SEEK_CUR);
        fseek(p, 9 * (3 * coloumns * 10 + padding), SEEK_CUR);
    }
}
