#include "const.h"
#include "funkcje.h"

//cc -X odczyt.c funkcje.c opcje.c -lm

int main(int argc, char **argv){
  Image img;
  Options option;
  int kod_bledu = 0;
  kod_bledu = przetwarzaj_opcje(argc,argv,&option);
  if(kod_bledu != 0){
    printf("Blad numer %d\n", kod_bledu);
  }else{
    readImg(&img, &option);
    if (option.menu == 0){
      if(option.h == 1){
        histogram(&img);
      }
      if(option.negatyw == 1){
        negative(&img);
      }
      if(option.kontur == 1){
        kontur(&img);
      }
      if(option.rx == 1){
        rx(&img);
      }
      if(option.ry == 1){
        ry(&img);
      }
      if(option.ppmtopgm == 1){
        P3toP2(&img);
      }
      if(option.wyswietlenie == 1){
        show(&option);
      }
      if(option.saveimg == 1){
        saveImg(&img, &option);
      }
    }else{
      printf("---------- Menu ----------\n");
      printf("1. '-i <nazwa pliku>' - wczytuje plik o podanej nazwie\n");
      printf("2. '-o <nazwa pliku>' - zapisuje plik o podanej nazwie (gdy jest sam '-' to zapisuje jako plik, który zostal wczytany)\n");
      printf("3. '-w' - wyswietla obraz\n");
      printf("4. '-n' - funkcja negatyw\n");
      printf("5. '-k' - konturowanie (tylko dla PGM)\n");
      printf("6. '-x' - rozmycie poziome\n");
      printf("7. '-y' - rozmycie pionowe\n");
      printf("8. '-h' - rozciaganie histogramu\n");
      printf("9. '-baw' - zamienia plik ppm na czarnobialy\n");
      printf("10. '-s' - zapis pliku\n");
      printf("---------------------------\n");
    }
  }
}