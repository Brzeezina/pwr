#include<stdio.h>
#include<math.h>

int main(){
    float a,b,c,delta;
    printf("Program rozwiazuje rownanie kwadratowe\n");
    printf("Podaj a: ");
    scanf("%f",&a);
    printf("Podaj b: ");
    scanf("%f",&b);
    printf("Podaj c: ");
    scanf("%f",&c);
    if (a==0.0){
        if(b!=0.0){
            printf("To rownanie liniowe a wynikiem jest x = %f", -c/b);
        }else if(c == 0.0){ //a==b==c==0.0
            printf("Rozwiązaniem jest dowolne x");
        }
    }else{ //rownanie z delta
        delta = pow(b,2) - 4.0*a*c;
        if (delta < 0)
        {
            printf("Brak rozwiązań rzeczywistych!");
        }else{
            if(delta>0){
                printf("Rozwiazaniami tego rownania sa x1 = %f oraz x2 = %f", (-b-sqrt(delta))/(2.0*a), (-b+sqrt(delta))/(2.0*a));
            }else{
                printf("Rozwiazaniami tego rownania jest x1 = x2 = %f", -b/(2.0*a));
            }
        }
        
    }
    while(a == 0){
        printf("a=0       s");
    }
    return 1;
}
