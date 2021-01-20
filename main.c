#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
        printf(" -Dolazak na posao [D]\n -Odlazak sa posla [O]\n");
        printf("\nODABERITE OPCIJU:");
        scanf("%s",s);
        if(strcmp(s,"D")==0)
        {
            fprintf(dat,"Vrijeme dolaska na posao: %02d-%02d-%d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
            printf("\nTrenutno vrijeme uspjesno upisano u registar za radno vrijeme!\n");
        }
        else if(strcmp(s,"O")==0)
        {
            fprintf(dat,"Vrijeme odlaska sa posla: %02d-%02d-%d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
            printf("\nTrenutno vrijeme uspjesno upisano u registar za radno vrijeme!\n");
        }
    }
    else printf("Greška pri otvaranju datoteke!\n");
    fclose(dat);
}
int main()
{
    int pin;
    int pinDat;
    int flag=0;
    int n=0;
    FILE *file;
    while(n<3)
    {
        printf("Unesite PIN kod:");
        scanf("%d",&pin);
        if((file=fopen("korisnickiNalozi.txt","r")))
        {
            while((fscanf(file,"%*d %*s %*s %d",&pinDat))!=EOF)
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
                printf("Uneseni PIN kod ne postoji! Imate jos %d %s\n\n",(3-n),((3-n)>1)? "pokusaja!" : "pokusaj!" );
            }
            else break;
        }
        else
            printf("Greska pri otvaranju datoteke!\n");
    }
    fclose(file);
    return 0;
}
