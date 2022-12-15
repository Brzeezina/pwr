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

int readImg(Obraz *obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (obraz->fileIn==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf,DL_LINII,obraz->fileOut)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
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
  if (fscanf(obraz->fileIn,"%d %d %d",obraz->wymx,obraz->wymy,obraz->grayscale)!=3) {
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

//obraz->tab[i][j] = fscanf(obraz->fileIn,"%d");

int printImg(Obraz *obraz){
  for(int y=0; y < obraz->wymy;y++){
    for(int x= 0;x<obraz->wymx;x++){
      printf("%d ", obraz->tab[y][x]);
    }
  }
}

int GetPixel(Obraz *obraz){
    for(int i = 0; i < obraz->wymy; i++){
        for(int j = 0; j < obraz->wymx; j++){
            if(obraz->min_pixel < obraz->tab[i][j]){
                obraz->min_pixel = obraz->tab[i][j];
            }
            if(obraz->max_pixel > obraz->tab[i][j]){
                obraz->max_pixel = obraz->tab[i][j];
            }
        }    
    }
    //printf("Minpixel: %d, Maxpixel: %d\n", obraz->min_pixel, obraz->max_pixel);
    //printf("%d", obraz->tab[20][10]);
    return 0;
}

void wyswietl(Obraz *obraz) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,obraz->nameToSave);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

//Stworzenie efektu negatywu, "odwracając" poszczególny pixel i otworzenie filtrowanego
//obrazka
void negatyw(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci, char name[60]){
  FILE *plik_wyjsciowy; 
  strcat(name, "_negatyw.pgm");
  plik_wyjsciowy = fopen(name, "w");
  fprintf(plik_wyjsciowy, "P2\n");
  fprintf(plik_wyjsciowy, "%d %d\n", *wymx, *wymy);
  fprintf(plik_wyjsciowy, "%d\n", *szarosci);
  for(int i = 0; i < *wymy; i++){
      for(int j = 0; j < *wymx; j++){
        int pixel = *szarosci - obraz_pgm[i][j];
        fprintf(plik_wyjsciowy, "%d ", pixel);
      }
      fprintf(plik_wyjsciowy, "\n");
    }
  //wyswietl(name);
  fclose(plik_wyjsciowy);
}

//Funkcja konturowania podanego obrazka i otworzenie filtrowanego
//obrazka
void kontur(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci, char name[60]){
  FILE *plik_wyjsciowy; 
  strcat(name, "_kontur.pgm");
  plik_wyjsciowy = fopen(name, "w");
  fprintf(plik_wyjsciowy, "P2\n");
  fprintf(plik_wyjsciowy, "%d %d\n", *wymx, *wymy);
  fprintf(plik_wyjsciowy, "%d\n", *szarosci);
  for(int i = 0; i < *wymy; i++){
      for(int j = 0; j < *wymx; j++){
        int pixel = abs(obraz_pgm[i+1][j] - obraz_pgm[i][j]) + abs(obraz_pgm[i][j+1]-obraz_pgm[i][j]);
        fprintf(plik_wyjsciowy, "%d ", pixel);
      }
      fprintf(plik_wyjsciowy, "\n");
    }
  //wyswietl(name);
  fclose(plik_wyjsciowy);
}

//Funkcja filtrowania gamma podanego obrazka i otworzenie filtrowanego
//obrazka
/*void filtr_gamma(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci, char name[60], float gamma_){
  FILE *plik_wyjsciowy; 
  strcat(name, "_gamma.pgm");
  plik_wyjsciowy = fopen(name, "w");
  fprintf(plik_wyjsciowy, "P2\n");
  fprintf(plik_wyjsciowy, "%d %d\n", *wymx, *wymy);
  fprintf(plik_wyjsciowy, "%d\n", *szarosci);
  int maxpixel = max_pixel(plik_we, obraz_pgm, wymx, wymy);
  for(int i = 0; i < *wymy; i++){
      for(int j = 0; j < *wymx; j++){
        int pixel = (pow(obraz_pgm[i][j], (1/gamma_)))/(pow(maxpixel, ((1-gamma_)/gamma_)));
        fprintf(plik_wyjsciowy, "%d ", pixel);
      }
      fprintf(plik_wyjsciowy, "\n");
    }
  //wyswietl(name);
  fclose(plik_wyjsciowy);
}*/

int CheckIfFileExists(Obraz *obraz){
  char buff[DL_LINII];
  //Czy istnieje taki plik
  if(obraz->fileIn == NULL){
    printf("Blad: Nie znaleziono takiego pliku\n");
    return false;
  }
  return true;
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