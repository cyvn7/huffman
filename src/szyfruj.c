#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

void szyfruj(FILE* pin,FILE* pout,char* nazwaPliku){
	FILE *klucz;
	char sciezka[512]={0};
	*strstr(nazwaPliku,".txt")='\0';
	strcpy(sciezka,"klucz/");
	strcat(sciezka,nazwaPliku);
	strcat(sciezka,".klucz");
	klucz=fopen(sciezka,"w");
	char c;
	int ile=0,baza;
	srand(time(NULL));
	int wzor=rand()%100;
	baza=wzor;
	fprintf(klucz,"%d",baza);
	int licz=7;
	while((c=fgetc(pin))!=EOF){
		if(baza>0) ile=1;
		else ile=-1;
		//ile=baza%licz;
		fprintf(pout,"%c",c+ile);
		baza-=licz;
		//printf("%d %d\n",ile,baza);
		if(baza*-1>100) baza=wzor;
	}
	fclose(klucz);
}

void deszyfruj(FILE* pin,FILE* pout,char* nazwaPliku){
	FILE *klucz;
	char sciezka[512]={0};
	*strstr(nazwaPliku,".txt")='\0';
	strcpy(sciezka,"klucz/");
	strcat(sciezka,nazwaPliku);
	strcat(sciezka,".klucz");
	if((klucz=fopen(sciezka,"r"))==NULL){
		printf("Błąd pliku klucza! Zapewnij odpowiedni plik .klucz .\n");
	}
	char c;
	int ile=0,baza,licz=7,wzor;
	fscanf(klucz,"%d",&wzor);
	baza=wzor;
	while((c=fgetc(pin))!=EOF){
		if(baza>0) ile=1;
		else ile=-1;
		//ile=baza%licz;
		fprintf(pout,"%c",c-ile);
		//printf("%c %i\n",c,ile);
		baza-=licz;
		if(baza<-100) baza=wzor;
	}
	fclose(klucz);
}
