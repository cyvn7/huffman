#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

void sprawdzArgv(char* flaga,int *kompresja,int *dekompresja,int *szyfrowanie,int *poziom,char* nazwaPliku,char* tylkoNazwa){
	//printf("%s\n",flaga);
	if(strcmp(flaga,"-s")==0) *szyfrowanie=1;
	else if(strcmp(flaga,"-k")==0) *kompresja=1;
	else if(strcmp(flaga,"-d")==0) *dekompresja=1;
	else if(strcmp(flaga,"-0")==0) *poziom=0;
	else if(strcmp(flaga,"-1")==0) *poziom=1;
	else if(strcmp(flaga,"-2")==0) *poziom=2;
	else if(strcmp(flaga,"-3")==0) *poziom=3;
	else{
		strcpy(tylkoNazwa,flaga);
		strcat(nazwaPliku,flaga);
	}
	return;
}

int sprawdzCzyDekod(FILE* pin){
	char sprawdz;
	while((sprawdz=getc(pin))!=EOF){
		if(isascii(sprawdz)==0){
			rewind(pin);
			return 0;
		}
	}
	rewind(pin);
	return 1;
}
