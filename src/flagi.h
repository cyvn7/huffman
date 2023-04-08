#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

void sprawdzArgv(char* flaga,int *kompresja,int *dekompresja,int *szyfrowanie,int *poziom,char* nazwaPliku,char* tylkoNazwa);
int sprawdzCzyDekod(FILE* pin);
