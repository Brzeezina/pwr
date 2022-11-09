#include <stdio.h>
#include <stdlib.h>

//#define ABS(A) ((A) < 0) ? (-A) : (A)

/*float abs(float a){
    if(a<0){
        return -a;
    } return a;
}*/

char init_func(){
  char* config = 
  "printf('Hello world')";
  return *config;
}

int main(){
    //printf("%f", abs(-5.2));
    init_func();
    return 0;
}