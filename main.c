#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 100

void InformacijeOFirmi()
{
    FILE* fp;
    char pom[MAX];
    printf("\n");
    if((fp=fopen("Config.txt","r"))!=NULL)
    {
        fgets(pom,100,fp);
        fgets(pom,100,fp);
        while(fgets(pom,100,fp))
        {
            printf("%s",pom);
        }
        fclose(fp);
    }
    printf("\n\n");
}

void aplikacijaZaEvidentiranjeVremena(int pin)
{
    FILE *dat;
    char osoba[25];
    char s[3];
    itoa(pin,osoba,10);
    strcat(osoba,".txt");
    if((dat=fopen(osoba,"a")))
    {
        time_t t = time(0);
        struct tm tm = *localtime(&t);
        printf("\nOpcije:\n");
        printf(" -Dolazak na posao [D]\n -Odlazak sa posla [O]\n -Informacije o kompaniji [I]\n");
        printf("\nODABERITE OPCIJU:");
        scanf("%s",s);
        if((strcmp(s,"D"))==0)
        {
            fprintf(dat,"Vrijeme dolaska na posao: %02d-%02d-%d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
            printf("\nTrenutno vrijeme uspjesno upisano u registar radnika!\n");
        }
        else if((strcmp(s,"O"))==0)
        {
            fprintf(dat,"Vrijeme odlaska sa posla: %02d-%02d-%d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
            printf("\nTrenutno vrijeme uspjesno upisano u registar radnika!\n");
        }
        else if((strcmp(s,"I"))==0)
            InformacijeOFirmi();
    }
    else printf("Greška pri otvaranju registra radnika!\n");
    fclose(dat);
}
int main()
{
    FILE* firma;
    char imefirme[MAX],pom[MAX];

    if((firma=fopen("Config.txt","r"))!=NULL)
    {
        fgets(pom,100,firma);
        fgets(imefirme,100,firma);
        printf("%s\n",imefirme);
        fclose(firma);
    }
    else printf("ERROR! Ne postoji konfiguraciona datoteka!");


    int pin;
    int pinDat;
    int flag=0;
    int n=0;
    FILE *file;
    while(n<10)
    {
        printf("Unesite PIN kod:");
        scanf("%d",&pin);
        if((file=fopen("korisnickiNalozi.txt","r")))
        {
            while((fscanf(file,"%*s %*s %*s %d %*d",&pinDat))!=EOF)
            {
                if(pin==pinDat)
                {
                    flag=1;
                    aplikacijaZaEvidentiranjeVremena(pin);
                }
            }
            if(flag==0)
            {
                n++;
                printf("Uneseni PIN kod ne postoji!\n\n");
                if(n==10)
                    printf("Iskoristili ste sve pokusaje!\nPonovo pokrenite aplikaciju!\n");
            }
            else break;
        }
        else
            printf("Greska pri otvaranju datoteke korisnickiNalozi.txt!\nKorisnicki nalozi se kreiraju u HR aplikaciji!\n");
    }
    fclose(file);
    return 0;
}
