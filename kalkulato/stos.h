#include <stdio.h>
#include <stdlib.h>

typedef struct Element{
    int wartosc;
    struct Element *nastepny;
}Element;

typedef struct Stos
{
    Element *pierwszy;
}Stos;
