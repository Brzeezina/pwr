#include "const.h"

typedef struct{
    int value, szarosci, r, g, b;
}Pixel;

typedef struct{
    int tab[MAX][MAX], wymx, wymy, grayscale, min_pixel, max_pixel;
    FILE *fileIn, *fileOut;
    char name[256], nameToSave[256];
}Obraz;

typedef struct{
    FILE *fileIn, *fileOut;
    int negatyw;
}Opcje;

int min_pixel(FILE *, int (*)[MAX], int *, int *);
int max_pixel(FILE *, int (*)[MAX], int *, int *);
void negatyw(FILE *, int (*)[MAX], int *, int *, int *, char *);
void kontur(FILE *, int (*)[MAX], int *, int *, int *, char *);
//void filtr_gamma(FILE *, int (*)[MAX],int *,int *,int*,char *,float);
int CzytajObraz(Obraz *obraz);
int CheckIfFileExists(Obraz *obraz);
void saveImg(Obraz *obraz);
void wyswietl(Obraz *obraz);
int GetPixel(Obraz *obraz);
int printImg(Obraz *obraz);