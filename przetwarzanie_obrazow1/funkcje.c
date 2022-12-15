#include <stdio.h>
#include "funkcje.h"
#include "const.h"

#define true 1
#define false 0
#define P2 2
#define P3 3



/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/

void wyswietl(Obraz *obraz) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */
  printf("%s\n", obraz->name);
  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,obraz->name);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

int readImg(FILE *fileIn,Obraz *obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;
  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (fileIn==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf,DL_LINII,fileIn)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(fileIn))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,fileIn)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,fileIn);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(fileIn,"%d %d %d",&obraz->wymx,&obraz->wymy,&obraz->grayscale)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      if (fscanf(obraz->fileIn,"%d",&(obraz->tab[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return obraz->wymx*obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}

void saveImg(Obraz *obraz){
  FILE *plik = fopen(obraz->nameToSave,"w");
  /*if(plik == NULL){
    printf("Blad podczas otwierania pliku %s\n", obraz->nameToSave);
    return;
  }*/

  fprintf(plik, "P2 \n%d %d\n%d\n", obraz->wymx, obraz->wymy, obraz->grayscale);
  for(int y = 0; y < obraz->wymy; y++){
    for(int x = 0; x < obraz->wymx; x++){
      fprintf(plik,"%d ", obraz->tab[y*obraz->wymx + x]);
    }
    fprintf(plik, "\n");
  }
  fclose(plik);
}

void checkMagickNumber(Obraz *obraz){
  char mn[2] = fgets(obraz->fileIn,2,obraz->fileOut);
  if(mn == 'P2'){
    obraz->magick_number = P2;
  }else if(mn == 'P3'){
    obraz->magick_number = P3;
  }
}