#include "const.h"

int min_pixel(FILE *, int (*)[MAX], int *, int *);
int max_pixel(FILE *, int (*)[MAX], int *, int *);
void negatyw(FILE *, int (*)[MAX], int *, int *, int *, char *);
void kontur(FILE *, int (*)[MAX], int *, int *, int *, char *);
void filtr_gamma(FILE *, int (*)[MAX],int *,int *,int*,char *,float);
int czytaj(FILE *, int (*)[MAX], int *, int *, int* );
void wyswietl(char *);