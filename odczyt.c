#include "const.h"
#include "funkcje.h"
#include "odczyt2.h"

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

//cc -X odczyt.c funkcje.o

//cc -X odczyt.c funkcje.o -lm

//./a.out odczyt.c

int main() {
  int obraz[MAX][MAX] ;
  int wymx,wymy,odcieni,wybor;
  float gamma;

  int odczytano = 0;
  FILE *plik;
  char nazwa[100];

  /* Wczytanie zawartosci wskazanego pliku do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s",nazwa);
  plik=fopen(nazwa,"r");

//Jeżeli plik nie jest pusty -> wyświetl menu
  if (plik != NULL) { 
    odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
    fclose(plik);
    printf("MENU\n");
    printf("1 - Negatyw\n");
    printf("2 - Kontur\n");
    printf("3 - Korekcja gamma\n");
    printf("4 - Zakonczenie programu\n");
    printf("Twoj wybor: ");scanf("%d", &wybor);
  }

  //Użycie wybranej w menu funkcji filtrowania
  if (odczytano != 0){
    switch (wybor)
    {
    case 1:
      negatyw(plik, obraz, &wymx, &wymy, &odcieni, nazwa);
      break;
    case 2:
      kontur(plik, obraz, &wymx, &wymy, &odcieni, nazwa);
      break;
    case 3:
      gamma = 0;
      printf("Podaj wartosc gamma: "); scanf("%f", &gamma);
      filtr_gamma(plik, obraz, &wymx, &wymy, &odcieni, nazwa, gamma);
      break;
    case 4:
        printf("Zakanczanie dzialania programu...\n");
        return 0;
    default:
        printf("Nie ma takiej opcji wyboru!\n");
        return 0;
    }
  }

  return odczytano;
}