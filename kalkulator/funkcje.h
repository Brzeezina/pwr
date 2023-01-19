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

Stos *initStos();
Element *initElem(int wartosc);
void push(Stos *stos, int arg);
void print(Stos *stos);
int pop(Stos *stos);
void clear(Stos *stos);
void reverse(Stos *stos);
int count(Stos *stos);
void duplicate(Stos *stos);