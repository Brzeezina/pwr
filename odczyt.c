#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

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

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"F:/ImageMagick-7.1.0-Q16-HDRI/imdisplay.exe ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

void negatyw(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci){
  //int odczytano = czytaj(plik_we,obraz_pgm,wymx,wymy,szarosci);  
  //if(odczytano != 0){
    FILE *plik_wyjsciowy; 
    plik_wyjsciowy = fopen("zapis.pgm", "r+");
    fprintf(plik_wyjsciowy, "P2\n");
    fprintf(plik_wyjsciowy, "%d %d\n", *wymx, *wymy);
    fprintf(plik_wyjsciowy, "%d\n", *szarosci);
    for(int i = 0; i < *wymy; i++){
      for(int j = 0; j < *wymx; j++){
        int pixel = abs(obraz_pgm[i][j] - *szarosci);
        fprintf(plik_wyjsciowy, "%d ", pixel);
      }
      //printf("\n");
      fprintf(plik_wyjsciowy, "\n");
    }
    fclose(plik_wyjsciowy);
    wyswietl("zapis.pgm");
  }
//}

int min_pixel(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy){
  int min = 0;
  for(int i = 0; i < *wymy; i++){
    for(int j = 0; j < *wymx; j++){
      if(obraz_pgm[i][j] < min){
        min = obraz_pgm[i][j];
      }
    }
  }
  //printf("%d\n",min);
  return min;
}
int max_pixel(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy){
  int max = 0;
  for(int i = 0; i < *wymy; i++){
    for(int j = 0; j < *wymx; j++){
      if(obraz_pgm[i][j] > max){
        max = obraz_pgm[i][j];
      }
    }
  }
  //printf("%d\n",max);
  return max;
}

void rozciagniecie_histogramu(FILE *plik_we, int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci){
  FILE *plik_wyjsciowy; 
    plik_wyjsciowy = fopen("zapis.pgm", "r+");
    fprintf(plik_wyjsciowy, "P2\n");
    fprintf(plik_wyjsciowy, "%d %d\n", *wymx, *wymy);
    fprintf(plik_wyjsciowy, "%d\n", *szarosci);
    int minpixel = min_pixel(plik_we, obraz_pgm, wymx, wymy);
    int maxpixel = max_pixel(plik_we, obraz_pgm, wymx, wymy);
    for(int i = 0; i < *wymy; i++){
      for(int j = 0; j < *wymx; j++){
        int pixel = (obraz_pgm[i][j]-minpixel)*((*szarosci)/(maxpixel-minpixel));
        fprintf(plik_wyjsciowy, "%d ", pixel);
      }
      fprintf(plik_wyjsciowy, "\n");
    }
    fclose(plik_wyjsciowy);
    wyswietl("zapis.pgm");
  }

int main() {
  int obraz[MAX][MAX] ;
  int wymx,wymy,odcieni;

  int odczytano = 0;
  FILE *plik;
  char nazwa[100];

  /* Wczytanie zawartosci wskazanego pliku do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s",nazwa);
  plik=fopen(nazwa,"r");

  if (plik != NULL) {       /* co spowoduje zakomentowanie tego warunku */
    odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
    //negatyw(plik,obraz,&wymx,&wymy,&odcieni);
    fclose(plik);
  }

  /* Wyswietlenie poprawnie wczytanego obraza zewnetrznym programem */
  if (odczytano != 0)
    //min_pixel(plik,obraz,&wymx,&wymy);
    //max_pixel(plik,obraz,&wymx,&wymy);
    //negatyw(plik,obraz,&wymx,&wymy,&odcieni);
    //wyswietl(nazwa);
    rozciagniecie_histogramu(plik,obraz,&wymx,&wymy,&odcieni);

  return odczytano;
}