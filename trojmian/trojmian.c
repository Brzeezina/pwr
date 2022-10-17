/* 
    kompilacja: Sun C: cc -xc99 -Xc trojmian.c -lm
                GNU C: gcc -std=c99 -pedantic -Wall trojmian.c -lm */
#include <stdio.h>
#include <math.h>

int main() {
  float a,b,c,delta;

  printf("Program oblicza pierwiastki rownania w postaci\n");
  printf("     2\n");
  printf("  a x + b x +c =0\n");
  printf("Podaj wartosc a:");
  scanf("%f",&a);
  printf("Podaj wartosc b:");
  scanf("%f",&b);
  printf("Podaj wartosc c:");
  scanf("%f",&c);
  
  if (a==0.0)    /*przypadek rownania liniowego */
    if (b!=0.0) 
      printf("Jest to równanie liniowe o rozwiazaniu x=%f\n",-c/b);
    else  if (c==0.0)  /* oraz a==b==0.0 */
      printf("Rozwiazaniem jest dowolne x\n");
    else              /* a==b==0.0 != c  */
      printf("Brak rozwiazan\n");
  else {   /*przypadek rownania kwadratowego */
    delta=pow(b,2)-4.0*a*c;
    if (delta<0) 
      printf("Brak rozwiazan rzeczywistych\n");
    else            /* delta>=0 */
      if (delta>0) 
	printf("Rozwiazaniem sa x1=%f i x2=%f\n",(-b-sqrt(delta))/(2*a),(-b+sqrt(delta))/(2*a));
      else
      	printf("Rozwiazaniem sa x1=x2=%f\n",-b/2*a);
  }
}


/*

1. Delta większa od zera
2. Delta równa zero
3. Delta mniejsza od zera
4. a = 0 (równanie liniowe)
5. a = 0 i b = 0
6. a = 0 i c = 0
7. a = 0, b = 0, c = 0
8. Losowe liczby z przecinkami
9. Wynik z pierwiastkiem niewymiernym
10. a = -1, b = 0 i bardzo duze c
11. a = 0, b małe, c bardzo duże
12. Dla losowych dodatnich argumentow
13. Dla losowych ujemnych argumentow
14. Gdy wpisany zostanie tekst (lub wszystkie znaki za wyjątkiem "+" oraz "-") zamiast liczby
15. Gdy wpisany zostanie znak "+" lub "-"

Sprawozdanie z zadania 1

Imię i nazwisko: Konrad Brzeziński, nr albumu: 275461
Data wykonania: 16.10.2022
Temat ćwiczenia: Poprawa błędów kodu źródłowego oraz sprawdzenie poprawności wyników programu

Kod źródłowy skompilowanego programu: kbrzezin/home/Dokumenty/trojmian.out

Celem testów będzie sprawdzenie poprawności wyników programu oraz działania algorytmu 
(testy zostaną wykonane na wszystkich możliwych sytuacjach oraz porównanie z wynikami obliczonymi ręcznie oraz za pomocą kalkulatora naukowego)

Test 1:
 - Cel: Sprawdzenie poprawności programu dla delty większej od zera
 - Metoda testowania (dane wejściowe): a = 1; b = -6; c = 5
 - Oczekiwany rezultat: x1 = 1; x2 = 5
 - Dane wyjściowe: "Rozwiazaniem sa x1=1.000000 i x2=5.000000"
 - Komentarz: Program poprawnie oblicza i wypisuje pierwiastki, wyniki zgadzają się z wynikami oczekiwanymi. 
   Ponieważ warości a,b,c są typem float to program wypisuje wszystkie cyfry w zaokrągleniu do 6 cyfr po przecinku.

Test 2.1:
 - Cel: Sprawdzenie poprawności programu dla delty równej zero
 - Metoda testowania (dane wejściowe): a = 4; b = -40; c = 100
 - Oczekiwany rezultat: x1 = x2 = 5
 - Dane wyjściowe: "Rozwiazaniem sa x1=x2=80.000000"
 - Komentarz: Po kilkukrotnym sprawdzeniu czy wynik jest poprawny na panamint oraz na windowskie stwierdzam, że 
   program ten nie przeszedł testu, ponieważ błednie oblicza podane równanie. Poprawnym rozwiązaniem jest x = 5. 
   Dzieje się tak ze względu na to, że autor zapisał rozwiązanie jako -b/2*a. Program najpierw zmienia znak współczynnika b, 
   następnie dzieli współczynnik b przez 2, a na koniec mnoży przez współczynnik a. Poprawnym tokiem obliczania tego rozwiązania
   jest odwrócenie znaku "b", potem pomnożenie "a" przez 2, a na koniec podzielenie obu wartości przez siebie w takiej kolejności 
   w jakiej wypisałem. Program potrzebuje poprawki. Aby wynik wychodził poprawny należy część 2*a wziąć w nawias: -b/(2*a).
   Wykonam jeszcze jeden test z innymi, specjalnie ustawionymi, współczynnikami, w których ten brakujący nawias nie gra 
   roli i wynik wychodzi poprawny.

Test 2.2:
 - Cel: Celowe wybranie współczynników aby delta była równa zero i podpasowanie do programu aby wynik był zgodny z oczekiwaniami
 - Metoda testowania (dane wejściowe): a = 1; b = 2; c = 1
 - Oczekiwany rezultat: x1 = x2 = -1
 - Dane wyjściowe: "Rozwiazaniem sa x1=x2=-1.000000"
 - Komentarz: Tym razem wynik jest poprawny, gdyż specjalnie ustawiłem współczynniki, aby program obliczył i podał
   poprawną wartość. Jednak jak to było w tescie 2.1, nie dla wszystkich wartości ten program będzie działał poprawnie.
   Należałoby poprawić ten dość poważny błąd.

Test 3:
 - Cel: Sprawdzenie wyniku dla delty mniejszej od zera
 - Metoda testowania (dane wejściowe): a = 1; b = 1; c = 1
 - Oczekiwany rezultat: Brak rozwiązań rzeczywistych
 - Dane wyjściowe: "Brak rozwiazan rzeczywistych"
 - Komentarz: Program zareagował poprawnie. Nie pojawił się żaden błąd, tak jak zakładaliśmy.

Test 4:
 - Cel: Sprawdzenie wyniku i jego poprawności dla a = 0, czyli równania liniowego
 - Metoda testowania (dane wejściowe): a = 0; b = 5; c = 10
 - Oczekiwany rezultat: x = -2
 - Dane wyjściowe: "Jest to r├│wnanie liniowe o rozwiazaniu x=-2.000000"
 - Komentarz: Program dobrze rozpoznał, że jest to rówanie liniowe i podał jego jedyny wynik oraz poinformował, że to właśnie rówanie liniowe.
   Niestety terminal bądź kompilator języka C nie obsługuje polskich znaków. 

 Test 5:
 - Cel: Sprawdzanie wyniku i jego poprawności gdy a i b = 0
 - Metoda testowania (dane wejściowe): a = 0; b = 0; c = 10
 - Oczekiwany rezultat: "Brak rozwiązań"
 - Dane wyjściowe: "Brak rozwiązań"
 - Komentarz: Program zadziałał poprawnie.

 Test 6:
 - Cel: Sprawdzenie wyniku i jego poprawności gdy a i c = 0
 - Metoda testowania (dane wejściowe): a = 0; b = 10; c = 0
 - Oczekiwany rezultat: x = 0
 - Dane wyjściowe: "Jest to r├│wnanie liniowe o rozwiazaniu x=-0.000000"
 - Komentarz: Wynik zgadza się z oczekiwaniami, jednak widzimy tutaj znak "-" przed zerem. Wiemy że zero nie jest ujemne, więc w tym przypadku
   wypadałoby dodać krótki algorytm usprawniający program, który usuwa znak "-" sprzed zera.

 Test 7:
 - Cel: Sprawdzenie wyniku i jego poprawności gdy a, b oraz z jest równe 0 
 - Metoda testowania (dane wejściowe): a = 0; b = 0; c = 0
 - Oczekiwany rezultat: X jest dowolną liczbą rzeczywistą
 - Dane wyjściowe: "Rozwiazaniem jest dowolne x"
 - Komentarz: Możnaby dodać, że rozwiązaniem jest dowolne x należące do zbioru liczb rzeczywistych. Po za tym program zareagował bez błędnie.

 Test 8:
 - Cel: Sprawdzenie wyniku i jego poprawności gdy podamy losowe liczby po przecinku.
 - Metoda testowania (dane wejściowe): a = 5.45; b = -10.5; c = 0.896
 - Oczekiwany rezultat (w przybliżeniu): x1 = 0.0894901; x2 = 1.83712
 - Dane wyjściowe: Rozwiazaniem sa x1=0.089490 i x2=1.837116
 - Komentarz: Rozwiązania zgadzają się z oczekiwanymi. Widzimy, że x2 jest zaokrąglone, czyli nasz program dał nam dokładniejszy wynik 
   niż kalkulator naukowy, jednak z wartością x1 mamy odwrotną sytuację, gdyż zdefiniowaliśmy nasze a,b oraz c jako zmienną typu float i wynik
   zaokrąglony jest do 6 cyfr po przecinku.

 Test 9:
 - Cel: Sprawdzenie wyniku i jego poprawności gdy wynik jest liczbą z pierwiastkiem niewymiernym
 - Metoda testowania (dane wejściowe): a = 1; b = -4; c = 2
 - Oczekiwany rezultat: x1 = 3.414213; x2 = 0.585786
 - Dane wyjściowe: "Rozwiazaniem sa x1=0.585786 i x2=3.414214"
 - Komentarz: Wynik się zgadza tak samo jak i zaokrąglenia.

 Test 10:
 - Cel: Sprawdzenie wyniku i jego poprawności gdy a = -1; b = 0; c jest bardzo duże
 - Metoda testowania (dane wejściowe): a = -1; b = 0; c = 114568115684
 - Oczekiwany rezultat: x1 = -338479,12149; x2 = 338479,12149
 - Dane wyjściowe: "Rozwiazaniem sa x1=338479.125000 i x2=-338479.125000"
 - Komentarz: Wyniki różnią się od siebie od 3 cyfry po przecinku. 

 Test 11:
 - Cel:
 - Metoda testowania (dane wejściowe):
 - Oczekiwany rezultat:
 - Dane wyjściowe:
 - Komentarz:

 Test 12:
 - Cel:
 - Metoda testowania (dane wejściowe):
 - Oczekiwany rezultat:
 - Dane wyjściowe:
 - Komentarz:

 Test 13:
 - Cel:
 - Metoda testowania (dane wejściowe):
 - Oczekiwany rezultat:
 - Dane wyjściowe:
 - Komentarz:

 Test 14:
 - Cel:
 - Metoda testowania (dane wejściowe):
 - Oczekiwany rezultat:
 - Dane wyjściowe:
 - Komentarz:

 Test 15:
 - Cel:
 - Metoda testowania (dane wejściowe):
 - Oczekiwany rezultat:
 - Dane wyjściowe:
 - Komentarz:

*/