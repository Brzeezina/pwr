#include <stdio.h>
#include <math.h>
#include "const.h"
#include "funkcje.h"
#include <string.h>

#define WSZYSTKO_OK 0

#define B_NIEPOPRAWNAOPCJA -1
#define B_BRAKNAZWY -2
#define B_BRAKWARTOSCI -3
#define B_BRAKPLIKU -4

int przetwarzaj_opcje(int argc, char ** argv, Options *choice){
    char *fileInName, *fileOutName;
    char polecenie[DL_LINII];

    choice->fileIn = NULL;
    choice->fileOut = NULL;
    choice->negatyw = 0;
    choice->kontur = 0;
    choice->progowanie = 0;
    choice->wyswietlenie = 0;
    choice->rx = 0;
    choice->ry = 0;
    choice->h = 0;
    choice->menu = 0;

    //choice->fileOut = stdout;
    if(argc == 1){
        choice->menu = 1;
        return WSZYSTKO_OK;
    }
    for(int i = 1; i < argc; i++){
        if(argv[i][0] != '-') return B_NIEPOPRAWNAOPCJA;
        switch(argv[i][1]){
            case 'i': {                      /* opcja z nazwa pliku wejsciowego */
          if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
            fileInName=argv[i];
            if (strcmp(fileInName,"-")==0){ /* gdy nazwa jest "-"        */
              choice->fileIn=stdin;             /* ustwiamy wejscie na stdin */
            } else {                               /* otwieramy wskazany plik   */
              choice->fileIn=fopen(fileInName,"r");
            }
          } else {
            return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
            }
          break;
        }
        case 'o': {                   /* opcja z nazwa pliku wyjsciowego */
          if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
            fileOutName=argv[i];
            if (strcmp(fileOutName,"-")==0){ /* gdy nazwa jest "-"         */
              choice->fileOut=stdout;         /* ustwiamy wyjscie na stdout */
            } else{                             /* otwieramy wskazany plik    */
              choice->fileOut=fopen(fileOutName,"w");
              }
          } else {
              return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
            }
          break;
        }
            case 'n':{
                choice->negatyw = 1;
                //printf("Negatyw");
                break;
            }
            case 'k':{
                choice->kontur = 1;
                break;
            }
            case 'h':{
                choice->h = 1;
                break;
            }
            case 'w':{
                choice->wyswietlenie = 1;
                break;
            }
            case 'x':{
                choice->rx = 1;
                break;
            }
            case 's':{
                choice->saveimg = 1;
                break;
            }
            case 'y':{
                choice->ry = 1;
                break;
            }
            case 'b':{
                if(argv[i][2] == 'a'){
                  if(argv[i][3] == 'w'){
                    choice->ppmtopgm = 1;
                    break;
                  }
                }
            }
            default:
                return B_NIEPOPRAWNAOPCJA;
        }
    }
    if(choice->fileIn!=NULL || argv[1][1] == 'm'){
        return WSZYSTKO_OK;
    }else return B_BRAKPLIKU;
}