#include <stdio.h>

int main(void) {
  char line[256];  // bufor na pierwszą linię pliku
  FILE *file = fopen("kubus.pgm", "r");  // otwarcie pliku do odczytu

  // wczytanie pierwszej linii pliku do bufora
  while (fgets(line, sizeof line, file)) {
    // wyświetlenie pierwszej linii pliku
    printf("%s", line);
    break;  // zakończenie pętli
  }

  fclose(file);  // zamknięcie pliku
  return 0;
}