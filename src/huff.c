#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "kodowanie.h"
#include "szyfruj.h"
#include "flagi.h"


/*
╔═══╗╔═══╗╔═╗╔═╗╔═══╗╔═══╗
║╔═╗║║╔═╗║║║╚╝║║║╔═╗║║╔═╗║
║╚═╝║║║ ║║║╔╗╔╗║║║ ║║║║ ╚╝
║╔══╝║║ ║║║║║║║║║║ ║║║║ ╔╗
║║   ║╚═╝║║║║║║║║╚═╝║║╚═╝║
╚╝   ╚═══╝╚╝╚╝╚╝╚═══╝╚═══╝
  */

void help() {
	printf("--------DEKOMPRESOR I KOMPRESOR ALGORYTUMU HUFFMANA--------\n");
	printf("Program służy kompresji bądź dekompresji plików za pomocą algorytmu Huffmana. W wywołaniu programu należy podać nazwę pliku wejściowego, oraz flagi w zależności od tego jaką czynność program ma wykonać:\n");
	printf("-k - kompresowanie pliku\n");
	printf("-d - dekompresowanie pliku\n");
	printf("-s - szyfrowanie/deszyfrowanie pliku");
	printf("-h - wyświetlenie pomocy\n");
}

/*
╔╗ ╔╗╔╗ ╔╗ ╔═══╗ ╔═══╗╔═╗╔═╗╔═══╗╔═╗ ╔╗
║║ ║║║║ ║║ ║╔══╝ ║╔══╝║║╚╝║║║╔═╗║║║╚╗║║
║╚═╝║║║ ║║ ║╚══╗ ║╚══╗║╔╗╔╗║║║ ║║║╔╗╚╝║
║╔═╗║║║ ║║ ║╔══╝ ║╔══╝║║║║║║║╚═╝║║║╚╗║║
║║ ║║║╚═╝║╔╝╚╗  ╔╝╚╗  ║║║║║║║╔═╗║║║ ║║║
╚╝ ╚╝╚═══╝╚══╝  ╚══╝  ╚╝╚╝╚╝╚╝ ╚╝╚╝ ╚═╝
                                       
╔═╗╔═╗╔═══╗╔══╗╔═╗ ╔╗
║║╚╝║║║╔═╗║╚╣╠╝║║╚╗║║
║╔╗╔╗║║║ ║║ ║║ ║╔╗╚╝║
║║║║║║║╚═╝║ ║║ ║║╚╗║║
║║║║║║║╔═╗║╔╣╠╗║║ ║║║
╚╝╚╝╚╝╚╝ ╚╝╚══╝╚╝ ╚═╝
*/

int main(int argc, char* argv[]){
	FILE *pin, *pout, *pinh;//plik in (pin), plik out (pout)
	char nazwaPliku[1024]={0}, nazwaSzyfru[512]={0},tylkoNazwa[512]={0};
	strcpy(nazwaPliku,"dane/");
	unsigned int czesto[128]={0},i;
	int kompresja=0,dekompresja=0,szyfrowanie=0,poziom=1,pomoc=0;
	for(int i=0;i<argc-1;i++){
		sprawdzArgv(argv[i+1],&kompresja,&dekompresja,&szyfrowanie,&poziom,nazwaPliku,tylkoNazwa,&pomoc);
	}

	if(strcmp(tylkoNazwa,"")!=0 && kompresja==0 && dekompresja==0){
		if((pin=fopen(nazwaPliku,"r"))==NULL){
			printf("\nBłąd otwarcia pliku\n");
			help();
			return 1;
		}
		if(sprawdzCzyDekod(pin)) kompresja=1;
		else dekompresja=1;
		fclose(pin);
	}
	
	//printf("\n\nkompresja:%d dekompresja:%d szyfrowanie:%d poziom:%d nazwa:%s\n\n\n",kompresja,dekompresja,szyfrowanie,poziom,nazwaPliku);
	
	if(strlen(nazwaPliku)>=128){
		printf("\nZa długa nazwa pliku (max 128 znaków)\n");
		help();
		return 1;
	}	


	if(pomoc) {
		help();
		return 0;
	}
/*	

╔═══╗╔════╗╔╗  ╔╗ ╔═══╗╔═══╗╔═══╗╔╗╔╗╔╗╔═══╗╔═╗ ╔╗╔══╗╔═══╗
║╔═╗║╚══╗ ║║╚╗╔╝║ ║╔══╝║╔═╗║║╔═╗║║║║║║║║╔═╗║║║╚╗║║╚╣╠╝║╔══╝
║╚══╗  ╔╝╔╝╚╗╚╝╔╝ ║╚══╗║╚═╝║║║ ║║║║║║║║║║ ║║║╔╗╚╝║ ║║ ║╚══╗
╚══╗║ ╔╝╔╝  ╚╗╔╝  ║╔══╝║╔╗╔╝║║ ║║║╚╝╚╝║║╚═╝║║║╚╗║║ ║║ ║╔══╝
║╚═╝║╔╝ ╚═╗  ║║  ╔╝╚╗  ║║║╚╗║╚═╝║╚╗╔╗╔╝║╔═╗║║║ ║║║╔╣╠╗║╚══╗
╚═══╝╚════╝  ╚╝  ╚══╝  ╚╝╚═╝╚═══╝ ╚╝╚╝ ╚╝ ╚╝╚╝ ╚═╝╚══╝╚═══╝

*/
	if (szyfrowanie==1 && kompresja==1){
		if((pin=fopen(nazwaPliku,"r"))==NULL){
			printf("\nBłąd otwarcia pliku\n");
			help();
			return 1;
		}
		strcpy(nazwaSzyfru,nazwaPliku);
		*strstr(nazwaSzyfru,".txt")='\0';
		strcat(nazwaSzyfru,"zaszyfr.txt");
		pout=fopen(nazwaSzyfru,"w");
		szyfruj(pin,pout,tylkoNazwa);
		fclose(pout);
		fclose(pin);
		//pin=fopen(nazwaSzyfru,"r");
		strcpy(nazwaPliku,nazwaSzyfru);
	}
/*

╔╗╔═╗╔═══╗╔═╗╔═╗╔═══╗╔═══╗╔═══╗╔═══╗  ╔╗╔═══╗
║║║╔╝║╔═╗║║║╚╝║║║╔═╗║║╔═╗║║╔══╝║╔═╗║  ║║║╔═╗║
║╚╝╝ ║║ ║║║╔╗╔╗║║╚═╝║║╚═╝║║╚══╗║╚══╗  ║║║║ ║║
║╔╗║ ║║ ║║║║║║║║║╔══╝║╔╗╔╝║╔══╝╚══╗║╔╗║║║╚═╝║
║║║╚╗║╚═╝║║║║║║║║║   ║║║╚╗║╚══╗║╚═╝║║╚╝║║╔═╗║
╚╝╚═╝╚═══╝╚╝╚╝╚╝╚╝   ╚╝╚═╝╚═══╝╚═══╝╚══╝╚╝ ╚╝
                          
*/
	if(kompresja==1){
		if((pin=fopen(nazwaPliku,"r"))==NULL){
			printf("\nBłąd otwarcia pliku\n");
			help();
			return 1;
		}
		przetworzPlik(pin,czesto);
		
		//tu pisanie
		//wypisz(czesto);
		//
		strcat(nazwaPliku,".huffman");
		pout=fopen(nazwaPliku,"w");
		
		for(i=0; i<128; i++){
			fprintf(pout,"%c",(char)czesto[i]);
		}
		fprintf(pout,"123456789\n");
		
		koduj(pin,pout,czesto);
		fclose(pin);
		fclose(pout);
		
		if(szyfrowanie==1){
			remove(nazwaSzyfru);
			*strstr(nazwaPliku,"zaszyfr")='\0';
			rename(strcat(nazwaSzyfru,".huffman"),strcat(nazwaPliku,".txt.huffman"));
		}
		
	}
/*

╔═══╗╔═══╗╔╗╔═╗╔═══╗╔═╗╔═╗╔═══╗╔═══╗╔═══╗╔═══╗  ╔╗╔═══╗
╚╗╔╗║║╔══╝║║║╔╝║╔═╗║║║╚╝║║║╔═╗║║╔═╗║║╔══╝║╔═╗║  ║║║╔═╗║
 ║║║║║╚══╗║╚╝╝ ║║ ║║║╔╗╔╗║║╚═╝║║╚═╝║║╚══╗║╚══╗  ║║║║ ║║
 ║║║║║╔══╝║╔╗║ ║║ ║║║║║║║║║╔══╝║╔╗╔╝║╔══╝╚══╗║╔╗║║║╚═╝║
╔╝╚╝║║╚══╗║║║╚╗║╚═╝║║║║║║║║║   ║║║╚╗║╚══╗║╚═╝║║╚╝║║╔═╗║
╚═══╝╚═══╝╚╝╚═╝╚═══╝╚╝╚╝╚╝╚╝   ╚╝╚═╝╚═══╝╚═══╝╚══╝╚╝ ╚╝

*/
	else if(dekompresja==1){
		if(strstr(nazwaPliku,"huffman") == NULL){
			printf("\nBłędne rozszerzenie pliku wejsciowego do dekodowania\n");
			help();
			return 1;
		}
		if((pinh = fopen(nazwaPliku,"r"))==NULL){
			printf("\nBłąd otwarcia pilku\n");
			help();
			return 1;
		}
		*strstr(nazwaPliku,".txt") = '\0';
		pout=fopen(strcat(nazwaPliku,"O.txt"),"w");
		dekoduj(pinh,pout,czesto);
		fclose(pinh);
		fclose(pout);
	}
/*

╔═══╗╔═══╗╔═══╗╔════╗╔╗  ╔╗ ╔═══╗╔═══╗╔═══╗╔╗╔╗╔╗╔═══╗╔═╗ ╔╗╔══╗╔═══╗
╚╗╔╗║║╔══╝║╔═╗║╚══╗ ║║╚╗╔╝║ ║╔══╝║╔═╗║║╔═╗║║║║║║║║╔═╗║║║╚╗║║╚╣╠╝║╔══╝
 ║║║║║╚══╗║╚══╗  ╔╝╔╝╚╗╚╝╔╝ ║╚══╗║╚═╝║║║ ║║║║║║║║║║ ║║║╔╗╚╝║ ║║ ║╚══╗
 ║║║║║╔══╝╚══╗║ ╔╝╔╝  ╚╗╔╝  ║╔══╝║╔╗╔╝║║ ║║║╚╝╚╝║║╚═╝║║║╚╗║║ ║║ ║╔══╝
╔╝╚╝║║╚══╗║╚═╝║╔╝ ╚═╗  ║║  ╔╝╚╗  ║║║╚╗║╚═╝║╚╗╔╗╔╝║╔═╗║║║ ║║║╔╣╠╗║╚══╗
╚═══╝╚═══╝╚═══╝╚════╝  ╚╝  ╚══╝  ╚╝╚═╝╚═══╝ ╚╝╚╝ ╚╝ ╚╝╚╝ ╚═╝╚══╝╚═══╝

*/
	if(dekompresja==1 && szyfrowanie==1){
		*strstr(tylkoNazwa,".huffman")='\0';
		pin=fopen(nazwaPliku,"r");
		strcpy(nazwaSzyfru,nazwaPliku);
		pout=fopen(strcat(nazwaSzyfru,"O"),"w");
		deszyfruj(pin,pout,tylkoNazwa);
		fclose(pin);
		fclose(pout);
		remove(nazwaPliku);
		rename(nazwaSzyfru,nazwaPliku);
	}

	return 0;
}
