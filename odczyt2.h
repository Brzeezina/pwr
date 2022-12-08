#define MAX 512
typedef struct
{
    int obraz_pgm[MAX][MAX];
    int wymx,wymy;
    int szarosci; 
}obraz;

/*
void negatyw(obraz *obrazpgm){
  FILE *plik_wyjsciowy; 
  strcat(name, "_negatyw.pgm");
  plik_wyjsciowy = fopen(name, "w");
  fprintf(plik_wyjsciowy, "P2\n");
  fprintf(plik_wyjsciowy, "%d %d\n", obrazpgm->wymx, obrazpgm->wymy);
  fprintf(plik_wyjsciowy, "%d\n", *szarosci);
  for(int i = 0; i < obrazpgm->wymy; i++){
      for(int j = 0; j < obrazpgm->wymx; j++){
        int pixel = obrazpgm->szarosci - obrazpgm->obraz_pgm[i][j];
        fprintf(plik_wyjsciowy, "%d ", pixel);
      }
      fprintf(plik_wyjsciowy, "\n");
    }
  wyswietl(name);
  fclose(plik_wyjsciowy);
}
*/