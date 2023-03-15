#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct wezel_t { //typ węzła
	struct wezel_t *left, *right;
	int czesto;
	char c;
} *wezel;

//zmienne pomocnicze deklarowane globalnie
int ileWezlow=0,koniec=1; //ile wezlow i gdzie koniec
struct wezel_t wszystkie[256]={{0}}; //wszytskie wezly
wezel qqq[255], *q=qqq-1; //kolejeczka
char *kod[128]={0},bufor[1024]; //kody dla znakow

wezel nowyWezel(int czesto,char c,wezel a,wezel b){
	wezel n=wszystkie+ileWezlow++;
	if(czesto!=0){
		n->c=c; //przyjecie danych wejsciowych do danych wezla
		n->czesto=czesto;
	}
	else{
		n->left=a, n->right=b; //gdy czestotliwosc jest rowna 0 mozemy usunac poprzez dodanie na koniec
		n->czesto = a->czesto+b->czesto;
	}
	return n;
}

void dodajK(wezel n){
	int j,i=koniec++;
	while((j=i/2)){
		if(q[j]->czesto <= n->czesto) break;
		q[i]=q[j],i=j;
	}
	q[i]=n;
}

wezel usunK(){
	int i,l;
	wezel n=q[i=1];
	if(koniec<2){
		return 0;
	}
	koniec--;
	while((l=i*2)<koniec){
		if(l+1<koniec && q[l+1]->czesto<q[l]->czesto){
			l++;
		}
		q[i]=q[l],i=l;
	}
	q[i]=q[koniec];
	return n;
}

void znajdzKody(wezel n,char *sl,int dl){
	static char *out=bufor;
	if(n->c){
		sl[dl]=0;
		strcpy(out,sl);
		kod[(int)n->c]=out;
		out+=dl+1;
		return;
	}

	sl[dl]='0';
	znajdzKody(n->left,sl,dl+1);
	
	sl[dl]='1';
	znajdzKody(n->right,sl,dl+1);
}

void przetworzPlik(FILE *pin,unsigned int *czesto){
	char c,sl[16]={0};
	int i=0;
	while((c=fgetc(pin))!=EOF){
		czesto[(int)c]++;
	}
	for(i=0;i<128;i++){
		if(czesto[i]){
			dodajK(nowyWezel(czesto[i],i,0,0));
		}
	}
	while(koniec>2){
		dodajK(nowyWezel(0,0,usunK(),usunK()));
	}
	znajdzKody(q[1],sl,0);
}

void koduj(FILE* pin,FILE* pout,unsigned int *czesto){
	char in,c,temp[20]={0};
	int i,j=0,k=0,lim=0;
	rewind(pin);
	for(i=0;i<128;i++){
		if(czesto[i]){
			lim+=(czesto[i]*strlen(kod[i]));
		}
	}
	fprintf(pout,"%04d\n",lim);
	
	for(i=0; i<128; i++){
		if(kod[i]!=NULL){
			fprintf(pout,"%c%s",(char)czesto[i],kod[i]);
		}
	}
	fprintf(pout,"\n");
	printf("Zakodowane:\n");
	for(i=0;i<lim;i++){
		if(temp[j]=='\0'){
			in=fgetc(pin);
			strcpy(temp,kod[in]);
			printf("%s",kod[in]); //uwaga tu wypisuje na linie kod-----------------------------------
			j=0;
		}
		if(temp[j]=='1'){
			c=c|(1<<(7-k));
		}
		else if(temp[j]=='0'){
			c=c|(0<<(7-k));
		}
		else{
			printf("ERROR: Błąd w pliku wejściowym. Kompresja niemożliwa");
		}
		k++;
		j++;
		if(((i+1)%8==0)||(i==lim-1)){
			k=0;
			fputc(c,pout);
			c=0;
		}
	}
	putchar('\n');
}


//-------------------------------------------------------------------tu było wypisz


int main(int argc, char* argv[]){
	FILE *pin, *pout;//plik in (pin), plik out (pout)
	char nazwaPliku[128]={0};
	unsigned int czesto[128]={0},i;
	
	if(argc==2){
		strcpy(nazwaPliku,argv[1]);
	}
	else if(argc==1){
		printf("tu będzie help\n");//------------------------------------------------
		return 0;
	}
	if(strlen(nazwaPliku)>=128){
		printf("Za długa nazwa pliku (max 128 znaków)\n");
		return 0;
	}
	if((pin=fopen(nazwaPliku,"r"))==NULL){
		printf("Błąd otwarcia pliku\n");
		return 0;
	}
	
	przetworzPlik(pin,czesto);
	
	//tu pisanie
	//wypisz(czesto);
	//
	
	strcat(nazwaPliku,"huff");
	pout=fopen(nazwaPliku,"w");
	koduj(pin,pout,czesto);
	fclose(pin);
	fclose(pout);
	return 0;
}
