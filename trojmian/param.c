#include <stdio.h>

int proba = 1, parametr;

int main(){
    printf("Podaj %d. wartosc parametru: ", proba);
    scanf("%d", &parametr);
    if(parametr <= 5 && parametr >= -5){
        printf("Aktualna wartosc parametru: %d\n", parametr);
    }else if(parametr == 99){
        return 0;
    }else printf("Bledna wartosc parametru!\n");
    proba++;
    do{
        printf("Podaj %d. wartosc parametru: ", proba);
        scanf("%d", &parametr);
        if(parametr <= 5 && parametr >= -5){
            printf("Aktualna wartosc parametru: %d\n", parametr);
        }else if(parametr == 99){
            return 0;
        }else printf("Bledna wartosc parametru!\n");
        proba++;
    }
    while(parametr!=99);

    return 0;
}