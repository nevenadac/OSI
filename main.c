#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void aplikacijaZaEvidentiranjeVremena()
{
    int pin;
    printf("Unesite PIN kod:");
    scanf("%d",&pin);
    FILE *dat;
    char osoba[25];
    char s[6];
    itoa(pin,osoba,10);
    strcat(osoba,".txt");
    if((dat=fopen(osoba,"a")))
    {
        time_t t = time(0);
        struct tm tm = *localtime(&t);
        while(1)
        {
            printf("Dolazak na posao [D], odlazak sa posla [O] ili nazad[N]:");
            scanf("%s",s);
            if(strcmp(s,"D")==0)
            {
                fprintf(dat,"Vrijeme dolaska na posao: %02d-%02d-%d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
                printf("Trenutno vrijeme uspjesno upisano u registar za radno vrijeme!");
                break;
            }
            else if(strcmp(s,"O")==0)
            {
                fprintf(dat,"Vrijeme odlaska sa posla: %02d-%02d-%d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
                printf("Trenutno vrijeme uspjesno upisano u registar za radno vrijeme!");
                break;
            }
            else if(strcmp(s,"N")==0)
                break;
        }
    }
    else printf("Greška pri otvaranju datoteke!");
}
int main()
{
    aplikacijaZaEvidentiranjeVremena();
    printf("Da li imate licencu:");
    return 0;
}
