#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

FILE* file;
FILE* file2;

void gotoxy(int x,int y){
	COORD coordinate={x,y};
	HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console,coordinate);
}

struct record      //dichiarazione del tracciato record
{ char tiporec;
int   Matricola;
char CogNome[35];
char  Sesso;
char DataNasc[11];
char ComuneRes[25];
char Classif;
}abbonato;   //abbonato è una variabile strutturata  "Tracciato Record"

char nome_file[20];
char scelta;

void trasferimento(char classe);

int main(int argn, char* argc[]){
	strcpy(nome_file, argc[1]);
	//printf("%s", nome_file);
	printf("inserire la classificazione da utilizzare:\n c - comune\n P - provincia\n I - Italia\n E - estero\n");
	printf("scelta: ");
	do{
		gotoxy(8,5);scanf("%c", &scelta);
	}while(scelta !='C' && scelta !='P' && scelta !='I' && scelta !='E');

	trasferimento(scelta);
	
}

void trasferimento(char classe) {
	system("cls");
    record appoggio;
    int num=0;

    file = fopen(nome_file, "rb"); // Apertura in modalità lettura binaria
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
	
    // Calcolo del numero di record
    fseek(file, 0, SEEK_END);
    int numrec = ftell(file) / sizeof(record);
    rewind(file);
    
	file2 = fopen("sequenziale.txt", "w"); 
	fprintf(file2, "N Matr   Cognome/Nome comune c1 \n");
    for (int i = 0; i < numrec; i++) {
        fread(&appoggio, sizeof(record), 1, file); // Legge un record alla volta
        gotoxy(1,1);printf("Solferino");
        gotoxy(5,3);printf("ELENCO ABBONATI RELATIVI ALLA CLASSIF. C");
        gotoxy(2,5);printf("N Matr   Cognome/Nome comune c1");
        if (appoggio.Classif == classe && appoggio.tiporec == 'A') {
        	num++;
        	gotoxy(2,num+6);
            printf("%2d | %2d | %2s | %2s | %2c", num,
                   appoggio.Matricola,
                   appoggio.CogNome,
                   appoggio.ComuneRes,
                   appoggio.Classif);
            //stampa file sequenziale
            fprintf(file2, "%d %d %s %s %c\n", num,
                   appoggio.Matricola,
                   appoggio.CogNome,
                   appoggio.ComuneRes,
                   appoggio.Classif);
        }
    }

    _fcloseall();
}


