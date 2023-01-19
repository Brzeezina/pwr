#include <stdio.h>
#include "funkcje.h"

int main(){
    Stos *stos = initStos();
    int a,b,arg,wynik;
    char znaki[100];
    while(1){
        printf("Podaj liczbe: ");
        scanf("%s", znaki);
        if(sscanf(znaki, "%d", &arg)){
            push(stos, arg);
            printf("Dodano do stosu liczbe %d\n", arg);
            printf("Aktualny stos: ");print(stos);printf("\n");
            int ilosc = count(stos);
            printf("Ilosc elementow w stosie: %d\n", ilosc);
        }else{
            switch(znaki[0]){
                case '+':
                    if(count(stos) < 2){
                        fprintf(stderr, "Blad: Za malo elementow w stosie\n");
                    }else{
                        a = pop(stos);
                        b = pop(stos);
                        wynik = a + b;
                        push(stos, wynik);
                        printf("Wykonano dodawanie, o to wynik: %d\n", wynik);
                        printf("Aktualny stos: ");print(stos);printf("\n");
                    }
                    break;
                case '-':
                    if(count(stos) < 2){
                        fprintf(stderr, "Blad: Za malo elementow w stosie\n");
                    }else{
                        a = pop(stos);
                        b = pop(stos);
                        wynik = a-b;
                        push(stos, wynik);
                        printf("Wykonano odejmowanie, o to wynik: %d\n", wynik);
                        printf("Aktualny stos: ");print(stos);printf("\n");
                    }
                    break;
                case '*':
                    if(count(stos) < 2){
                        fprintf(stderr, "Blad: Za malo elementow w stosie\n");
                    }else{
                        a = pop(stos);
                        b = pop(stos);
                        wynik = a*b;
                        push(stos, wynik);
                        printf("Wykonano mnozenie, o to wynik: %d\n", wynik);
                        printf("Aktualny stos: ");print(stos);printf("\n");
                    }
                    break;
                case '/':
                    if(count(stos) < 2){
                        fprintf(stderr, "Blad: Za malo elementow w stosie\n");
                    }else{
                        a = pop(stos);
                        b = pop(stos);
                        if(b == 0){
                            fprintf(stderr,"Blad: Nie mozna dzielic przez zero!\n");
                            break;
                        }
                        wynik = a/b;
                        push(stos, wynik);
                        printf("Wykonano dzielenie, o to wynik: %d\n", wynik);
                        printf("Aktualny stos: ");print(stos);printf("\n");
                    }
                    break;
                case 'r':
                    if(count(stos) == 0){
                        fprintf(stderr, "Blad: Stos pusty\n");
                        break;
                    }
                    reverse(stos);
                    printf("Odwrocono stos\n");
                    printf("Aktualny stos: ");print(stos);printf("\n");
                    break;
                case 'c':
                    clear(stos);
                    printf("Wyczyszczono stos\n");
                    break;
                case 'd':
                    duplicate(stos);
                    if(count(stos) < 1){
                        fprintf(stderr,"Blad: Brak elementow do duplikowania - stos pusty\n");
                        break;
                    }
                    printf("Zduplikowano pierwsza liczbe\n");
                    printf("Aktualny stos: ");print(stos);printf("\n");
                    printf("Ilosc elementow na stosie: %d\n", count(stos));
                    break;
                case 'q':
                    printf("Zakanczanie dzialania\n");
                    return 0;
                case '#':
                    if(count(stos) < 1){
                        fprintf(stderr,"Blad: Stos pusty\n");
                        break;
                    }
                    pop(stos);
                    printf("Usunieto ostatnio wprowadzony element\n");
                    printf("Aktualny stos: ");print(stos);printf("\n");
                    break;
                case '$':
                    if(count(stos) < 2){
                        fprintf(stderr, "Blad: Za malo elementow na stosie\n");
                        break;
                    }
                    a = pop(stos);
                    b = pop(stos);
                    push(stos, a);
                    push(stos, b);
                default:
                    printf("Podaj prosze jakas liczbe lub jeden z dostepnych operatorow operator (r,c,d,q,#,$)\n");
                    break;
            }
        }
    }
    return 0;
}