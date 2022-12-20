#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int wartosc;
    struct Element *nastepny;
}Element;

typedef struct{
    Element *ostatni;
    Element *pierwszy;
    int licz;
}Stos;

void init(Stos *stos){
    stos = NULL;
    stos->licz = 0;
    stos->pierwszy = NULL;
    stos->ostatni = NULL;
}

void push(Stos *stos, Element *element){
    Element *elem = (Element*)malloc(sizeof(Element));
    if(element == NULL) return;

    stos->licz++;
    stos->ostatni->wartosc = &element;
}

int main(){
    Stos stos;
    init(&stos);
    push(&stos, 14);
}