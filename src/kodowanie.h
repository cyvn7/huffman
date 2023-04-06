#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct wezel_t { //typ węzła
	struct wezel_t *left, *right;
	int czesto;
	char c;
} *wezel;

wezel nowyWezel(int czesto,char c,wezel a,wezel b);
void dodajK(wezel n);
wezel usunK();
void znajdzKody(wezel n,char *sl,int dl);
void przetworzPlik(FILE *pin,unsigned int *czesto);
void koduj(FILE* pin,FILE* pout,unsigned int *czesto);
void wypisz(unsigned int *czesto);
void czytajTabele(FILE *pint, unsigned int *czesto);
void dekoduj(FILE *pinh,FILE *pout,unsigned int *czesto);
