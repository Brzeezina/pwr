#include "const.h"

typedef struct{
    int **tab, wymx, wymy, grayscale, magick_number, minpixel, maxpixel; //Potrzebne zmienne obrazu
    //tablica dwuwymiarowa, wymiary poziome, wymiary pionowe, skala szarości, magiczny numerek, najmniejsza i największa wartość z tablicy.
}Image;

typedef struct{
    FILE *fileIn, *fileOut; //Plik wejściowy i wyjściowy
    int negatyw,progowanie,kontur,wyswietlenie,menu,rx,ry,h,ppmtopgm,saveimg; //Wszystkie opcje filtrowania
    char *newName; //Nazwa nowego pliku
}Options;

int readImg(Image *img, Options *option);
int saveImg(Image *img, Options *option);
int checkMagickNumber(Image *img, char *firstLine);
int loadImg(Image *img, Options *option);
int P3toP2(Image *img);
int negative(Image *img);
int przetwarzaj_opcje(int argc, char **argv, Options *choice);
int histogram(Image *img);
int ry(Image *img);
int rx(Image *img);
int kontur(Image *img);
void show(Options *option);