#include <stdio.h>
#include "funkcje.h"
#include "const.h"
#include "math.h"

#define true 1
#define false 0
#define P2 2
#define P3 3

/*
Funkcja sprawdza czy jest "magiczny numerek", a następnie ustawia go zależnie od pliku:
 - P3 (3) dla obrazów ppm
 - P2 (2) dla obrazów pgm
Gdy poprawnie załadowane -> zwraca magiczny numerek
Gdy brak numerka, który możemy przetważać -> wyświetla odpowiedni komunikat
*/
int checkMagickNumber(Image *img, char *firstLine){
  img->magick_number = 0;
  if(firstLine[0] == 'P'){
    switch(firstLine[1]){
      case '2':
        img->magick_number = P2;
        //printf("Magiczny numer to P2");
        return P2;
      case '3':
        img->magick_number = P3;
        //printf("Magiczny numer to P3");
        return P3;
      default:
        printf("Nie jest to plik PGM ani PPM!");
    }
  }else{
    printf("Nie jest to plik PGM ani PPM!");
  } 
}

/*
Funkcja ładuje pokolei pixele do tablicy wielkości zależnej od rodzaju obrazka.
Gdy wymiary się nie zgadzają -> Odpowiedni komunikat, przerwanie działania programu.
Gdy się zgadzają -> nic się nie dzieje
*/
int loadImg(Image *img, Options *option){
  if(img->magick_number == P2){
    for (int i=0;i<img->wymy;i++) {
      for (int j=0;j<img->wymx;j++) {
        if (fscanf(option->fileIn,"%d",&(img->tab[i][j]))!=1) {
          fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
          return(0);
        }
      }
    }
  }else if(img->magick_number == P3){
    for (int i=0;i<img->wymy;i++) {
      for (int j=0;j<3*(img->wymx);j++) {
        if (fscanf(option->fileIn,"%d",&(img->tab[i][j]))!=1) {
          fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
          return(0);
        }
      }
    }
  }
}

/*
Funkcja czyta obraz i sprawdza czy wszystko jest tak jak powinno, dla odpowiedniego rodzaju pliku.
Gdy plik jest w pożądku -> alokuj odpowiednią ilość miejsca dla tablicy dwuwymiarowej, a następnie
wywołaj funkcję loadImg().
Funkcja nic nie zwraca. 
*/
int readImg(Image *img, Options *option) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j,number;
  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (option->fileIn==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }
  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf,DL_LINII,option->fileIn)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  //if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
  //  fprintf(stderr,"Blad: To nie jest plik PGM\n");
  //  return(0);
  //}
  number = checkMagickNumber(img,buf);
  if(number == P2 || number == P3){
    /* Pominiecie komentarzy */
    do {
      if ((znak=fgetc(option->fileIn))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
        if (fgets(buf,DL_LINII,option->fileIn)==NULL)  /* Przeczytaj ja do bufora                */
	        koniec=1;                   /* Zapamietaj ewentualny koniec danych */
      }else {
        ungetc(znak,option->fileIn);                   /* Gdy przeczytany znak z poczatku linii */
      }                                         /* nie jest '#' zwroc go                 */
    }while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

    /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
    if (fscanf(option->fileIn,"%d %d %d",&(img->wymx),&(img->wymy),&(img->grayscale))!=3) {
      fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
      return(0);
    }
    
    if(img->magick_number==P2){  /*obraz jest pgm? alokuj normalnie*/
      img->tab=(int**)malloc(img->wymy*sizeof(int*));
      for (int k = 0; k < img->wymy; k++){
        img->tab[k]=(int*)malloc(img->wymx*sizeof(int));
      }
      if(img->tab==NULL){ /*sprawdzenie czy pamiec sie przydzielila*/
        fprintf(stderr,"Przydzielenie pamieci dla .pgm nie powiodlo sie\n");
      } 
    }
    if(img->magick_number==3){ /*obraz jest ppm? alokuj potrÃ³jny wymiar x*/
     img->tab=(int**)malloc(img->wymy*sizeof(int*));
      for (int k = 0; k < img->wymy; k++){
        img->tab[k]=(int*)malloc(img->wymx*sizeof(int)*3);
      }
      if(img->tab==NULL){ /*sprawdzenie czy pamiec sie przydzielila*/
        fprintf(stderr,"Przydzielenie pamieci dla .ppm nie powiodlo sie\n");
      } 
    }

    /* Pobranie obrazu i zapisanie w tablicy*/
    loadImg(img, option);
  }
}

/*
Funkcja zapisuje obraz do pliku o podanej przez użytkownika nazwie przy wywołaniu. 
Funkcja nic nie zwraca. 
*/
int saveImg(Image *img, Options *option){
  if(option->fileOut == NULL){
    printf("Blad podczas otwierania pliku %s\n", option->fileOut);
    return 0;
  }

  fprintf(option->fileOut, "P%d \n%d %d\n%d\n",img->magick_number, img->wymx, img->wymy, img->grayscale);
  if(img->magick_number != 0){
    if(img->magick_number == P2){
      for(int y = 0; y < img->wymy; y++){
        for(int x = 0; x < img->wymx; x++){
          fprintf(option->fileOut,"%d ", img->tab[y][x]);
        }
        fprintf(option->fileOut, "\n");
      }
    }else if(img->magick_number == P3){
      for(int y = 0; y < img->wymy; y++){
        for(int x = 0; x < 3*(img->wymx); x++){
          fprintf(option->fileOut,"%d ", img->tab[y][x]);
        }
        fprintf(option->fileOut, "\n");
      }
    }
  }
  //fclose(option->fileOut);
}

/*
Funkcja wyświetla obraz.
*/
void show(Options *option) {
  char polecenie[DL_LINII];
    strcpy(polecenie, "display ");
    strcat(polecenie, option->newName);
    strcat(polecenie, " &");
    system(polecenie);
}

/*
Funkcja konwertuje obraz z formatu P3 na P2. 
Gdy obraz nie jest P3 -> wyświetla odpowiedni komunikat.
Gdy jest P3 -> oblicza średnią arytmetyczną trzech pixeli odpowiednio: R, G, B.
Funkcja nic nie zwraca. 
*/
int P3toP2(Image *img){
  int a=0;
  if(img->magick_number != P3){
    printf("Podany obrazek nie jest PPM!");
    return 0;
  }else{
    img->magick_number = P2;
    for(int i = 0; i < img->wymy; i++){
      for(int j = 0; j < img->wymx;j++){
        img->tab[i][j] = ((img->tab[i][a] + img->tab[i][(a+1)] + img->tab[i][(a+2)])/3);
        //printf("%d ", img->tab[i][j]);
        a+=3;
      }
      a=0;
    }
    a=0;
  }
}

/*
Funkcja tworzy negatyw podanego obrazu.
Funkcja nic nie zwraca. 
*/
int negative(Image *img){
  int mnoznik = 0;
  if(img->magick_number == P2) mnoznik = 1;
  else mnoznik = 3;
  for(int i = 0; i < img->wymy;i++){
    for(int j = 0; j < (mnoznik)*(img->wymx); j++){
      img->tab[i][j] = img->grayscale - img->tab[i][j];
    }
  }
}

/*
Funkcja tworzy rozmycie poziome obrazu.
Preferowane dla obrazów PGM, ponieważ dla PPM zmieniają się tylko kolory.
Funkcja nic nie zwraca.  
*/
int rx(Image *img){
  int mnoznik = 0;
  if(img->magick_number == P2) mnoznik = 1;
  else mnoznik = 3;
  for(int i = 0; i < img->wymy-1;i++){
    for(int j = 0; j < (mnoznik)*(img->wymx)-1; j++){
      img->tab[i][j] = ((img->tab[i][j-1] + img->tab[i][j] + img->tab[i][j+1])/3);
    }
  }
}

/*
Funkcja tworzy rozmycie pionowe obrazu.
Preferowane dla obrazów PGM, ponieważ dla PPM zmieniają się tylko kolory.
Funkcja nic nie zwraca.  
*/
int ry(Image *img){
  int mnoznik = 0;
  if(img->magick_number == P2) mnoznik = 1;
  else mnoznik = 3;
  for(int i = 1; i < img->wymy-1;i++){
    for(int j = 1; j < (mnoznik)*(img->wymx)-1; j++){
      img->tab[i][j] = ((img->tab[i-1][j] + img->tab[i][j] + img->tab[i+1][j])/3);
    }
  }
}

/*
Funkcja rozciąga histogram obrazu.
Funkcja nic nie zwraca.  
*/
int histogram(Image *img){
  int mnoznik = 0;
  img->maxpixel,img->minpixel = img->tab[0][0];
  if(img->magick_number == P2) mnoznik = 1;
  else mnoznik = 3;
  for(int i = 0; i < img->wymy;i++){
    for(int j = 0; j < (mnoznik)*img->wymx; j++){
      if(img->tab[i][j] < img->minpixel){
        img->minpixel = img->tab[i][j];
      }
      if(img->tab[i][j] > img->maxpixel){
        img->maxpixel = img->tab[i][j];
      }
    }
  }
  for(int i = 0; i < img->wymy;i++){
    for(int j = 0; j < (mnoznik)*(img->wymx); j++){
      img->tab[i][j] = (img->tab[i][j] - img->minpixel) * ((img->grayscale)/(img->maxpixel - img->minpixel));
    }
  }
}

/*
Funkcja tworzy kontur obrazu.
Zalecane dla obrazów PGM, ponieważ dla PPM funkcja nakłada efekt bardziej Rentgen.
Funkcja nic nie zwraca.  
*/
int kontur(Image *img){
  int mnoznik = 0;
  if(img->magick_number == P2) mnoznik = 1;
  else mnoznik = 3;
  for(int i = 0; i < img->wymy-1;i++){
    for(int j = 0; j < img->wymx*mnoznik-1;j++){
      img->tab[i][j] = (abs(img->tab[i+1][j] - img->tab[i][j]) + abs(img->tab[i][j+1] - img->tab[i][j]));
    }
  }
}