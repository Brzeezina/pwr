#include "funkcje.h"

Stos *initStos(){
    Stos * stos = (Stos*)malloc(sizeof(Stos));
    stos->pierwszy = NULL;
    return stos;
}

Element *initElem(int wartosc){
    Element *elem = (Element*)malloc(sizeof(Element));
    elem->wartosc = wartosc;
    elem->nastepny = NULL;
}

void push(Stos *stos, int arg){
    Element *elem = initElem(arg);
    if(stos->pierwszy == NULL){
        stos->pierwszy = elem;
    }else{
        elem->nastepny = stos->pierwszy;
        stos->pierwszy = elem;
    }
}

void print(Stos *stos){
    Element *elem = stos->pierwszy;
    while(elem != NULL){
        printf("%d ", elem->wartosc);
        elem = elem->nastepny;
    }
}

int pop(Stos *stos){
    int wartosc;
    Element *elem;
    if(stos->pierwszy == NULL){
        fprintf(stderr, "Stos pusty");
        return -1;
    }
    else{
        wartosc = stos->pierwszy->wartosc;
        elem = stos->pierwszy;
        stos->pierwszy = elem->nastepny;
        free(elem);
        printf("Usunieto ze stosu liczbe: %d\n", wartosc);
        return wartosc;
    }
}

void clear(Stos *stos){
    Element *elem;
    while(stos->pierwszy != NULL){
        elem = stos->pierwszy;
        stos->pierwszy = elem->nastepny;
        free(elem);
    }
}

int count(Stos *stos){
    int licznik;
    Element *elem = stos->pierwszy;
    for(licznik = 0; elem!=NULL; licznik++){
        elem = elem->nastepny;
    }
    return licznik;
}

void reverse(Stos *stos){
    Element *wczesniejszy = NULL;
    Element *terazniejszy = stos->pierwszy;
    Element *nastepny;
    if(stos->pierwszy == NULL){
        fprintf(stderr, "Stos pusty");
    }else{
    while(terazniejszy != NULL){
        nastepny = terazniejszy->nastepny;
        terazniejszy->nastepny = wczesniejszy;
        wczesniejszy = terazniejszy;
        terazniejszy = nastepny;
    }
    stos->pierwszy = wczesniejszy;
    }
}
void duplicate(Stos *stos) {
    Element *first = stos->pierwszy;
    if (first == NULL) {
        return;
    }
    Element *dup = (Element *) malloc(sizeof(Element));
    dup->wartosc = first->wartosc;
    dup->nastepny = first;
    stos->pierwszy = dup;
}