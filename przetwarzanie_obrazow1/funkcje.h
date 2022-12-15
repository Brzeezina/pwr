#include "const.h"

typedef struct{
    int value, szarosci, r, g, b;
}Pixel;

typedef struct{
    int tab[MAX][MAX], wymx, wymy, grayscale, min_pixel, max_pixel, magick_number;
    FILE *fileIn, *fileOut;
    char *name, nameToSave[256];
}Obraz;

typedef struct{
    FILE *fileIn, *fileOut;
    int negatyw;
}Opcje;

int readImg(FILE *fileIn, Obraz *obraz);
void saveImg(Obraz *obraz);
void wyswietl(Obraz *obraz);
void checkMagickNumber(Obraz *obraz);