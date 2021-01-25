#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX 50
#define MAX1 100

void InformacijeOFirmi()
{
    FILE* fp;
    char pom[MAX1];
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
    printf("\n");
}

struct TIME {
   int seconds;
   int minutes;
   int hours;
};

typedef struct datum
{
    int dan, mjesec, godina;
} DATUM;

typedef struct status
{
    char status[10];
    DATUM prekidzpsl;
} STATUS;

typedef struct zaposleni
{
    char ime[MAX], prezime[MAX],rmj[MAX],rsektr[MAX], mjbor[MAX];
    DATUM dz,dpu;
    char JMB[14];
    STATUS status;
    int poc_pl;
} ZAPOSLENI;

struct TIME differenceBetweenTimePeriod(struct TIME start,struct TIME stop)
{
    struct TIME diff;
    while (stop.seconds > start.seconds)
    {
        --start.minutes;
        start.seconds += 60;
    }
    diff.seconds = start.seconds - stop.seconds;
    while (stop.minutes > start.minutes)
    {
        --start.hours;
        start.minutes += 60;
    }
    diff.minutes = start.minutes - stop.minutes;
    diff.hours = start.hours - stop.hours;
    return diff;
}

struct TIME addTime(struct TIME start,struct TIME stop)
{
    struct TIME pom;
    pom.seconds=start.seconds+stop.seconds;
	pom.minutes=start.minutes+stop.minutes+(pom.seconds/60);
	pom.hours=start.hours+stop.hours+(pom.minutes/60);
	pom.minutes=pom.minutes%60;
	pom.seconds=pom.seconds%60;
	return pom;
}

void korisnickaAplikacija(int pin,char *jmb)
{
    char opcija[10];
    ZAPOSLENI r;
    char pom[500];
    while(1)
    {
        printf("\nOpcije:\n");
        printf(" -Pregled licnih podataka [PODACI]\n");
        printf(" -Pregled radnog vremena [VRIJEME]\n");
        printf(" -Pregled ukupnog radnog vremena u satima po danima [UKUPNO]\n");
        printf(" -Informacije o kompaniji [INFO]\n");
        printf(" -Kraj [KRAJ]\n");
        printf("\nODABERITE OPCIJU:");
        scanf("%s",opcija);
        char c;
        if((strcmp(opcija,"PODACI")==0))
        {
            FILE *data;
            if((data=fopen("podaci.txt","r")))
            {
                fgets(pom,500,data);
                fgets(pom,500,data);
                fgets(pom,500,data);
                printf("\n\nLicni podaci:");
                printf("\n-------------------------------------------------------------------------------------------\n");

                while((fscanf(data,"%s %s %s %d %d %d %s %s %s %d %d %d %c %d %d %d %s %d %*d\n",r.ime,r.prezime,r.mjbor,&r.dpu.dan,&r.dpu.mjesec,&r.dpu.godina,r.rsektr,r.rmj,r.status.status,&r.dz.dan,&r.dz.mjesec,&r.dz.godina,&c,&r.status.prekidzpsl.dan,&r.status.prekidzpsl.mjesec,&r.status.prekidzpsl.godina,r.JMB,&r.poc_pl))!=EOF)
                    if((strcmp(r.JMB,jmb))==0)
                    {
                        printf(" IME: %s\n",r.ime);
                        printf(" PREZIME: %s\n",r.prezime);
                        printf(" MJESTO BORAVKA: %s\n",r.mjbor);
                        printf(" DATUM POTPISIVANJA UGOVORA: %02d.%02d.%02d\n",r.dpu.dan,r.dpu.mjesec,r.dpu.godina);
                        printf(" RADNI SEKTOR: %s\n",r.rsektr);
                        printf(" RADNO MJESTO: %s\n",r.rmj);
                        printf(" STATUS: %s\n",r.status.status);
                        printf(" RADNI PERIOD(datum zaposlenja-datum raskida ugovora): %02d.%02d.%02d - %02d.%02d.%02d\n",r.dz.dan,r.dz.mjesec,r.dz.godina,r.status.prekidzpsl.dan,r.status.prekidzpsl.mjesec,r.status.prekidzpsl.godina);
                        printf(" MATICNI BROJ: %s\n",r.JMB);
                        printf(" PLATA: %d",r.poc_pl);
                    }
                printf("\n-------------------------------------------------------------------------------------------\n\n");
            }
            else printf("Ne postoje podaci o radnicima!Podaci o radnicima se unose u HR aplikaciji!\n");
        }
        else if((strcmp(opcija,"VRIJEME"))==0)
        {
            FILE *time;
            char tekst[200];
            char datName[50];
            itoa(pin,datName,10);
            strcat(datName,".txt");
            if((time=fopen(datName,"r")))
            {
                printf("\n\nPregled radnog vremena radnika:");
                printf("\n----------------------------------------------\n");
                while(fgets(tekst,sizeof(tekst),time))
                    printf("%s",tekst);
                printf("\n----------------------------------------------\n\n");
            }
            else printf("Greska prilikom otvaranja datoteke!Ne postoji registar ovog radnika!\nVrijeme pristupa kompaniji se upisuje u registar u aplikaciji za evidentiranje vremena!\n");
        }
        else if((strcmp(opcija,"UKUPNO"))==0)
        {
            FILE *time;
            char flag1[8];
            char flag2[8];
            int d,mj,g,h,m,s;
            int d2,mj2,g2,h2,m2,s2;
            int d1,mj1,g1;
            char datName[20];
            struct TIME ukupno={0,0,0};
            struct TIME start, stop;
            itoa(pin,datName,10);
            strcat(datName,".txt");
            int k=1;
            if((time=fopen(datName,"r")))
            {
                printf("\n\nIZVJESTAJ O UKUPNOM RADNOM VREMENU U SATIMA PO DANIMA:");
                printf("\n------------------------------------------------------\n");
                int n=0;
                while((fscanf(time,"%s %*s %*s %*s %d-%d-%d %d:%d:%d\n",flag1,&d,&mj,&g,&h,&m,&s))!=EOF)
                {
                    fscanf(time,"%s %*s %*s %*s %d-%d-%d %d:%d:%d\n",flag2,&d2,&mj2,&g2,&h2,&m2,&s2);
                    if(n==0)
                    {
                        printf("%d-%d-%d\n",d,mj,g);
                        n=1;
                    }
                    if(k==1)
                    {
                        d1=d2;
                        mj1=mj2;
                        g1=g2;
                        k=0;
                    }
                    else if(d!=d1 || mj!=mj1 || g1!=g)
                    {
                        printf("Ukupno radno vrijeme:%dh:%dm:%ds\n\n",ukupno.hours,ukupno.minutes,ukupno.seconds);
                        ukupno.seconds=ukupno.minutes=ukupno.hours=0;
                        printf("%d-%d-%d\n",d,mj,g);
                        d1=d2;
                        mj1=mj2;
                        g1=g2;
                    }
                    start.seconds=s2;
                    start.minutes=m2;
                    start.hours=h2;
                    stop.seconds=s;
                    stop.minutes=m;
                    stop.hours=h;
                    ukupno=addTime(ukupno,differenceBetweenTimePeriod(start,stop));
                }
                 printf("Ukupno radno vrijeme:%dh:%dm:%ds",ukupno.hours,ukupno.minutes,ukupno.seconds);
                 printf("\n------------------------------------------------------\n\n");
            }
            else printf("Greska prilikom otvaranja datoteke!Ne postoji registar radnika!\n Prvo je potrebno koristiti aplikaciju za evidentiranje vremena!\n");
            fclose(time);
        }
        else if((strcmp(opcija,"INFO"))==0)
        {
            printf("\n\nKONTAKT INFORMACIJE:");
            printf("\n------------------------------------------------------");
            InformacijeOFirmi();
            printf("------------------------------------------------------\n\n");
        }
        else if((strcmp(opcija,"KRAJ"))==0)
            break;
    }
}

int main()
{
    FILE* firma;
    char imefirme[MAX1], pom[MAX1];
    if((firma=fopen("Config.txt","r"))!=NULL)
    {
        fgets(pom,100,firma);
        fgets(imefirme,100,firma);
        printf("%s\n",imefirme);
        fclose(firma);
    }
    else printf("ERROR! Ne postoji konfiguraciona datoteka!\n");

    char korisnik[50];
    char lozinka[50];
    char korisnikDat[50];
    char lozinkaDat[50];
    int pin;
    char jmb[14];
    FILE *dat;

    while(1)
    {
        printf("Unesite korisnicko ime:");
        scanf("%s",korisnik);
        printf("Unesite lozinku:");
        scanf("%s",lozinka);
        int flag1=0;
        int flag2=0;

        if((dat=fopen("korisnickiNalozi.txt","r")))
        {
            while((fscanf(dat,"%s %s %s %d\n",jmb,korisnikDat,lozinkaDat,&pin))!=EOF)
            {
                if((strcmp(korisnik,korisnikDat))==0)
                {
                    flag1=1;
                    if((strcmp(lozinka,lozinkaDat))==0)
                    {
                        korisnickaAplikacija(pin,jmb);
                        flag2=1;
                    }
                }
            }
            if(flag1==1 && flag2==1)
                break;
            else if(flag1==0)
                printf("\nUneseno korisnicko ime ne postoji!\n\n");
            else if(flag2==0)
                printf("\nNetacna lozinka!\n\n");
        }
        else printf("Greska prilikom otvaranja datoteke!Ne postoji ni jedan korisnicki nalog!\nKreiranje naloga se vrsi u HR aplikaciji!\n");
        fclose(dat);
    }
    return 0;
}
