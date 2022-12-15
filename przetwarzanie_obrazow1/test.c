#include <stdio.h>

#include "const.h"

typedef struct
{
  FILE *fileIn;
  int wymy,wymx,tab[MAX][MAX],grayscale;
}Obraz;

int readImg(Obraz *obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;
  //obraz->tab = malloc(obraz->wymx * obraz->wymy * sizeof(int));

  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (obraz->fileIn==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf,DL_LINII,obraz->fileIn)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(obraz->fileIn))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,obraz->fileIn)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,obraz->fileIn);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(obraz->fileIn,"%d %d %d",obraz->wymx),obraz->wymy,obraz->grayscale)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  printf("%d %d %d", obraz->wymx, obraz->wymy, obraz->grayscale);
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  /*for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      if (fscanf(obraz->fileIn,"%d",&(obraz->tab[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }*/
  //wyswietl(obraz);
  return obraz->wymx*obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}

int main(void) {
  char line[256];  // bufor na pierwszą linię pliku
  Obraz img;
  img.fileIn = fopen("kubus.pgm", "r");  // otwarcie pliku do odczytu

  // wczytanie pierwszej linii pliku do bufora
  while (fgets(line, sizeof line, img.fileIn)) {
    // wyświetlenie pierwszej linii pliku
    printf("%s", line);
    break;  // zakończenie pętli
  }

  readImg(&img);
  printf("%d", img.grayscale);

  fclose(img.fileIn);  // zamknięcie pliku
  return 0;
}