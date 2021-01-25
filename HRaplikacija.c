//HR APLIKACIJA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 50
#define MAX1 100

static int prijaveNaSistem;
int moguciBrojPrijava;


typedef struct novi_nalog
{
    char korisnicko_ime[MAX],PIN[MAX];
    int brojPrijava;
} NOVI_NALOG;
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
    NOVI_NALOG nn;
    STATUS status;
    int poc_pl;
    int PIN;
} ZAPOSLENI;

typedef struct cvor
{
    struct cvor* next;
    ZAPOSLENI info;
} CVOR;

typedef struct hr_korisnik
{
    char username[MAX], PIN[MAX];
} HR_KORISNIK;

void dodaj_u_listu(CVOR **pglava, ZAPOSLENI data)
{
    CVOR *novi=(CVOR*)malloc(sizeof(CVOR));
    novi->info=data;
    novi->next=*pglava;
    *pglava=novi;
}


void brisi_listu(CVOR **pglava)
{
    while(*pglava)
    {
        CVOR* p=(*pglava)->next;
        free(*pglava);
        *pglava=p;
    }
}

void pisi_header_u_fajl(FILE *dat)
{
    fprintf(dat,
            "=============== =============== =============== ====================== =============== =============== ========== ==================================================== ============= ===== ====\n");
    fprintf(dat,
            "IME             PREZIME         MJESTO BORAVKA  D.POTPISIVANJA UGOVORA RADNI SEKTOR    RADNO MJESTO    STATUS     RADNI PERIOD(datum zaposlenja-datum raskida ugovora) MATICNI BROJ  PLATA  ID\n");
    fprintf(dat,
            "=============== =============== =============== ====================== =============== =============== ========== ==================================================== ============= ===== ====\n");
}
void InformacijeOFirmi()
{
    FILE* fp;
    char pom[MAX1];
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
int ucitavanje_iz_datoteke(CVOR** pglava)
{
    int m=0;
    char pom[500];
    char c;
    int pin;
    ZAPOSLENI r;
    FILE *fp;
    if((fp=fopen("podaci.txt","r"))!=NULL)
    {
        fgets(pom,500,fp);
        fgets(pom,500,fp);
        fgets(pom,500,fp);
        char c;
        while((fscanf(fp,"%s %s %s %d %d %d %s %s %s %d %d %d %c %d %d %d %s %d %d\n",r.ime,r.prezime,r.mjbor,&r.dpu.dan,&r.dpu.mjesec,&r.dpu.godina,r.rsektr,r.rmj,r.status.status,&r.dz.dan,&r.dz.mjesec,&r.dz.godina,&c,&r.status.prekidzpsl.dan,&r.status.prekidzpsl.mjesec,&r.status.prekidzpsl.godina,r.JMB,&r.poc_pl,&r.PIN))!=EOF)
        {
            dodaj_u_listu(pglava,r);
            m++;
        }
        printf("Trenutan broj radnika je: %d\n",m);
        fclose(fp);
        return m;
    }
    return 0;
}

void pretraga_po_imenu_prezimenu(CVOR** pglava)
{
    char ime[MAX], prezime[MAX];
    printf("Unesite ime i prezime za pretragu: ");
    scanf("%s",ime);
    scanf("%s",prezime);
    int indikator_pretrage=0;
    if(*pglava==0)
        return;
    else
    {
        CVOR* trenutni=*pglava;
        while(trenutni!=NULL)
        {
            if(strcmpi(trenutni->info.ime,ime)==0 && strcmpi(trenutni->info.prezime, prezime)==0)
            {
                indikator_pretrage=1;
                printf("Pronadjen radnik pod imenom %s %s.\n",ime, prezime);
                printf("Informacije o radniku: \n");
                printf("Radni sektor: %s\n",trenutni->info.rsektr);
                printf("Radno mjesto: %s\n",trenutni->info.rmj);
                printf("Jedinstveni maticni broj: %s\n",trenutni->info.JMB);
                printf("Plata: %d\n",trenutni->info.poc_pl);
                printf("Status: %s\n",trenutni->info.status.status);
                if(strcmp(trenutni->info.status.status,"Neaktivan")==0)
                    printf("Datum prekidanja radnog odnosa: %d.%d.%d.\n",trenutni->info.status.prekidzpsl.dan,trenutni->info.status.prekidzpsl.mjesec,trenutni->info.status.prekidzpsl.godina);
                printf("~~~~~~~~~~~~~~~~~~~~\n");

            }
            trenutni=trenutni->next;
        }
        if(indikator_pretrage!=1)
            printf("Neuspjesna pretraga!\n");
        printf("===================================\n");
    }
}

int pristup_HR_aplikaciji()
{
    int flag1=0, flag2=0;
    FILE *fp;
    NOVI_NALOG n;
    NOVI_NALOG niz[MAX];
    char kor_ime[MAX],pin_kod[MAX];
    char pind[MAX];
    int i=0;
    int flag3=0;
    printf("Moguci broj prijava: %d\n",moguciBrojPrijava);
    if((fp=fopen("HRkorisnickinalozi.txt","r"))!=NULL)
    {
        printf("Unesite korisnicko ime: ");
        scanf("%s",kor_ime);
        while(fscanf(fp,"%s %s %d\n", &n.korisnicko_ime, &n.PIN, &n.brojPrijava)!=EOF)
        {
            if(strcmp(n.korisnicko_ime,kor_ime)==0)
            {
                flag2=1;
                if(n.brojPrijava==moguciBrojPrijava)
                {
                    printf("Morate promijeniti lozinku!\nUnesite staru lozinku: ");
                    scanf("%s",pin_kod);
                    if(strcmp(pin_kod,n.PIN)==0)
                    {
                        flag1=1;
                        do
                        {
                            printf("Unesite novu lozinku: ");
                            scanf("%s",pind);
                            if(strcasecmp(pind,n.PIN)==0)
                            {
                                printf("Nova lozinka ne moze biti stara lozinka!\n");
                            }
                        }
                        while(strcasecmp(pind,n.PIN)==0);
                        strcpy(n.PIN,pind);
                        n.brojPrijava=0;
                    }
                }
                else
                {
                    printf("Unesite lozinku: ");
                    scanf("%s",pin_kod);
                    if(strcmp(pin_kod,n.PIN)==0)
                    {
                        flag1=1;
                        n.brojPrijava++;
                    }
                }
            }
            strcpy(niz[i].korisnicko_ime,n.korisnicko_ime);
            strcpy(niz[i].PIN,n.PIN);
            niz[i].brojPrijava=n.brojPrijava;
            i++;
        }
        fclose(fp);
    }
    if((fp=fopen("HRkorisnickinalozi.txt","w"))!=NULL)
    {
        for(int k=0; k<i; k++)
            fprintf(fp,"%s %s %d\n", niz[k].korisnicko_ime,niz[k].PIN,niz[k].brojPrijava);
        fclose(fp);
    }

    if(flag2==0)
    {
        printf("Neispravno korisnicko ime!!!\n");
        return -1;
    }
    if(flag1==0)
    {
        printf("Neispravna lozinka!!!\n");
        return -1;
    }
    else
    {
        printf("PRISTUP HR APLIKACIJI OMOGUCEN!\n");
        return 1;
    }
}

void dodavanje_novog_zaposlenog(int m, char licenca[])
{
    FILE *fp1,*fp2;
    char c[MAX];
    char ime[MAX],JMB[MAX],lozinka[MAX];
    int PIN;
    NOVI_NALOG k;
    int broj_bl=m;
    int flag=0;
    if((fp1=fopen("podaci.txt","a"))!=NULL)
    {
        ZAPOSLENI r;
        do
        {
            if(strcmp("bez licence",licenca)==0 && m>5)
            {
                printf("Dostigli ste limit bez licenciranog dodavanja informacija.\n");
                return;
            }
            printf("===================================\n");
            printf("Ime radnika: ");
            scanf("%s",r.ime);
            printf("Prezime radnika: ");
            scanf("%s",r.prezime);
            printf("Radno mjesto: ");
            scanf("%s",r.rmj);
            printf("Radni sektor: ");
            scanf("%s",r.rsektr);
            printf("Mjesto stalnog boravka radnika: ");
            scanf("%s",r.mjbor);
            printf("Jedinstveni maticni broj radnika: ");
            scanf("%s",r.JMB);
            printf("Datum zaposlenja[d m g]: ");
            scanf("%d %d %d",&r.dz.dan,&r.dz.mjesec,&r.dz.godina);
            printf("Datum potpisivanja ugovora[d m g]: ");
            scanf("%d %d %d",&r.dpu.dan,&r.dpu.mjesec,&r.dpu.godina);
            printf("Pocetna plata: ");
            scanf("%d",&r.poc_pl);
            strcpy(r.status.status,"Aktivan");
            r.status.prekidzpsl.dan=0;
            r.status.prekidzpsl.mjesec=0;
            r.status.prekidzpsl.godina=00;
            printf("Kreiranje korisnickog naloga->\n");
            printf("Unesite korisnicko ime zaposlenog: ");
            char username[MAX];
            scanf("%s",username);
            if((fp2=fopen("korisnickiNalozi.txt","r"))!=NULL)
            {
                while((fscanf(fp2,"%s %s %s %d\n",JMB,ime,lozinka,&PIN)!=EOF))
                {
                    if(strcasecmp(username,ime)==0)
                    {
                        do
                        {
                            printf("Uneseno korisnicko ime vec postoji! Unesite novo korisnicko ime! ");
                            scanf("%s",username);
                        }
                        while(strcasecmp(username,ime)==0);
                    }
                }
                fclose(fp2);
            }
            char lozinka[MAX];
            printf("Unesite lozinku korisnika: ");
            scanf("%s",lozinka);
            int PIN;
            int flag;
            srand(NULL);
            do
            {
                PIN=rand()%9000 +1000;
                flag=trazi_pin(PIN);
            }
            while(flag==-1);

            if((fp2=fopen("korisnickiNalozi.txt","a"))!=NULL)
            {
                fprintf(fp2,"%s %s %s %d\n",r.JMB,username,lozinka,PIN);
                fclose(fp2);
            }

            printf("Korisnicko ime i lozinka zaposlenog %s %s je:%s,%s",r.ime,r.prezime,username,lozinka);
            printf("\nZaposleni %s,%s je dodat u arhivu!\n",r.prezime, r.ime);
            printf("===================================\n");
            fprintf(fp1,"%-15s %-15s %-15s %02d %02d %02d %27s %-15s %-10s %02d %02d %04d - %02d %02d %04d %42s %5d %4d\n",r.ime,r.prezime,r.mjbor,r.dpu.dan,r.dpu.mjesec,r.dpu.godina,r.rsektr,r.rmj,r.status.status,r.dz.dan,r.dz.mjesec,r.dz.godina, r.status.prekidzpsl.dan,r.status.prekidzpsl.mjesec,r.status.prekidzpsl.godina,r.JMB,r.poc_pl,PIN);
            printf("Ukoliko zelite da prekinete dodavanje unesite KRAJ, ukoliko zelite da nastavite unesite bilo koje slovo!\n");
            scanf("%s",c);
            if(strcmp("bez licence",licenca)==0)
            {
                broj_bl++;
                if(broj_bl==5)
                {
                    printf("Dostigli ste limit bez licenciranog dodavanja informacija.\n");
                    return;
                }

            }
        }
        while(strcmp("KRAJ",c)!=0);
        printf("~~~~~~~Dodavanje radnika zavrseno!~~~~~~~");
        fclose(fp1);
    }
    else
        printf("Greska. Nije moguce otvoriti datoteku...\n");
}

int trazi_pin(int pin)
{
    FILE* fp;
    char s1[MAX], s2[MAX];
    int d;
    int flag=0;
    if((fp=fopen("korisnickiNalozi.txt","r"))!=NULL)
    {
        while(fscanf(fp,"%s %s %d\n", s1, s2, &d)!=EOF)
        {
            if(d==pin)
                flag=-1;
        }
        fclose(fp);
    }
    else
        printf("Nije moguce otvoriti datoteku!");
    if(flag==-1)
        return -1;
    else
        return 1;
}

void pregled_prijave_radnogvr(CVOR** pglava)
{

    FILE* fp;
    char ime[MAX],prezime[MAX];
    printf("Unesite podatke za pretragu!\n");
    printf("Ime: ");
    scanf("%s",ime);
    printf("Prezime: ");
    scanf("%s",prezime);
    int indikator_pretrage=0;
    if(*pglava==0)
        return;
    else
    {
        CVOR* trenutni=*pglava;
        while(trenutni!=NULL)
        {
            if(strcmpi(trenutni->info.ime,ime)==0 && strcmpi(trenutni->info.prezime, prezime)==0)
            {
                indikator_pretrage=1;
                printf("Pronadjen radnik pod imenom %s %s.\n",ime, prezime);


                char tekst[200];
                char datName[50];
                itoa(trenutni->info.PIN,datName,10);
                strcat(datName,".txt");
                if((fp=fopen(datName,"r")))
                {
                    printf("\n\nPregled radnog vremena radnika:");
                    printf("\n----------------------------------------------\n");
                    while(fgets(tekst,sizeof(tekst),fp))
                        printf("%s",tekst);
                    printf("\n----------------------------------------------\n\n");
                    fclose(fp);
                }
                else
                    printf("Greska prilikom otvaranja datoteke!Ne postoji registar ovog radnika!\nVrijeme pristupa kompaniji se upisuje u registar u aplikaciji za evidentiranje vremena!\n");
            }
            trenutni=trenutni->next;
        }
        if(indikator_pretrage!=1)
            printf("Neuspjesna pretraga!\n");
        printf("===================================\n");
    }
    return;
}
void aktivacija_deaktivacija()
{
    char ime[MAX],prezime[MAX];
    FILE* fp;
    CVOR* glava=NULL;
    DATUM dat;
    printf("Unesite ime i prezime radnika.\n");
    printf("Ime: ");
    scanf("%s",ime);
    printf("Prezime: ");
    scanf("%s",prezime);
    if(ucitavanje_iz_datoteke(&glava))
    {
        int indikator_pretrage=0;
        if(glava==0)
            return;
        else
        {
            CVOR* trenutni=glava;
            while(trenutni!=NULL)
            {
                if(strcmpi(trenutni->info.ime,ime)==0 && strcmpi(trenutni->info.prezime, prezime)==0)
                {
                    indikator_pretrage=1;
                    printf("Pronadjen radnik pod imenom %s %s.\n",ime, prezime);
                    printf("Informacije o radniku: \n");
                    printf("~~~~~~~~~~~~~~~~~~~~\n");
                    printf("Ime: %s\n",trenutni->info.ime);
                    printf("Prezime: %s\n",trenutni->info.prezime);
                    printf("Radno mjesto: %s\n", trenutni->info.rmj);
                    printf("Radni sektor: %s\n",trenutni->info.rsektr);
                    printf("Datum zaposlenja: %d.%d.%d.\n",trenutni->info.dpu.dan,trenutni->info.dpu.mjesec, trenutni->info.dpu.godina);
                    printf("Datum potpisivanja ugovora: %d.%d.%d.\n",trenutni->info.dpu.dan,trenutni->info.dpu.mjesec,trenutni->info.dpu.godina);
                    printf("Mjesto stalnog boravka: %s\n",trenutni->info.mjbor);
                    printf("JMB: %s\n",trenutni->info.JMB);
                    printf("Plata: %d\n",trenutni->info.poc_pl);
                    strcpy(trenutni->info.status.status, "Neaktivan");
                    printf("Unesite datum deaktivacije: ");
                    scanf("%d %d %d",&dat.dan,&dat.mjesec,&dat.godina);
                    trenutni->info.status.prekidzpsl.dan=dat.dan;
                    trenutni->info.status.prekidzpsl.mjesec=dat.mjesec;
                    trenutni->info.status.prekidzpsl.godina=dat.godina;
                    printf("~~~Izvrsena deaktivacija radnika!~~~");
                }
                trenutni=trenutni->next;
            }
            if(indikator_pretrage!=1)
                printf("Neuspjesna pretraga!\n");
            if((fp=fopen("podaci.txt","w"))!=NULL)
            {
                pisi_header_u_fajl(fp);
                if(glava==0)
                    return;
                else
                {
                    CVOR* trenutni=glava;
                    while(trenutni!=NULL)
                    {
                        ZAPOSLENI r=trenutni->info;
                        fprintf(fp,"%-15s %-15s %-15s %02d %02d %02d %27s %-15s %-10s %02d %02d %04d - %02d %02d %04d %42s %5d %4d\n",r.ime,r.prezime,r.mjbor,r.dpu.dan,r.dpu.mjesec,r.dpu.godina,r.rsektr,r.rmj,r.status.status,r.dz.dan,r.dz.mjesec,r.dz.godina, r.status.prekidzpsl.dan,r.status.prekidzpsl.mjesec,r.status.prekidzpsl.godina,r.JMB,r.poc_pl,r.PIN);
                        trenutni=trenutni->next;
                    }
                }
            }
            return;
        }
    }
}
void pregled_po_sektoru(CVOR** pglava)
{
    char sektor[MAX];
    int indikator_pretrage=0;
    printf("===================================\n");
    printf("Pregled radnika po sektoru.\n");
    printf("Unesite radni sektor: ");
    scanf("%s",sektor);
    if(*pglava==0)
        return;
    else
    {
        printf("PREGLED PO SEKTORU %s:\n",sektor);
        CVOR* tr=*pglava;
        while(tr!=NULL)
        {
            if(strcmpi(tr->info.rsektr,sektor)==0)
            {
                indikator_pretrage=1;
                printf("~~~~~~~~~~~~~~~~~~~~\n");
                printf("Ime: %s\n",tr->info.ime);
                printf("Prezime: %s\n",tr->info.prezime);
                printf("Radno mjesto: %s\n", tr->info.rmj);
                printf("Datum zaposlenja: %d.%d.%d.\n",tr->info.dpu.dan,tr->info.dpu.mjesec, tr->info.dpu.godina);
                printf("Datum potpisivanja ugovora: %d.%d.%d.\n",tr->info.dpu.dan,tr->info.dpu.mjesec,tr->info.dpu.godina);
                printf("Mjesto stalnog boravka: %s\n",tr->info.mjbor);
                printf("JMB: %s\n",tr->info.JMB);
                printf("Plata: %d\n",tr->info.poc_pl);
                printf("Status: %s\n",tr->info.status.status);
                if(strcmp(tr->info.status.status,"Neaktivan")==0)
                    printf("Datum prekidanja radnog odnosa: %d.%d.%d.\n",tr->info.status.prekidzpsl.dan,tr->info.status.prekidzpsl.mjesec,tr->info.status.prekidzpsl.godina);
            }
            tr=tr->next;
        }
        if(indikator_pretrage!=1)
            printf("Neuspjesna pretraga!\n");
    }
    printf("===================================\n");
}

void pregled_po_rmjestu(CVOR** pglava)
{
    char rmjesto[MAX];
    int indikator_pretrage=0;
    printf("===================================\n");
    printf("Pregled radnika po radnom mjestu.\n");
    printf("Unesite radno mjesto: ");
    scanf("%s",rmjesto);
    if(*pglava==0)
        return;
    else
    {
        printf("PREGLED PO RADNOM MJESTU %s:\n",rmjesto);
        CVOR* tr=*pglava;
        while(tr!=NULL)
        {
            if(strcmpi(tr->info.rmj,rmjesto)==0)
            {
                indikator_pretrage=1;
                printf("~~~~~~~~~~~~~~~~~~~~\n");
                printf("Ime: %s\n",tr->info.ime);
                printf("Prezime: %s\n",tr->info.prezime);
                printf("Radno mjesto: %s\n", tr->info.rmj);
                printf("Datum zaposlenja: %d.%d.%d.\n",tr->info.dpu.dan,tr->info.dpu.mjesec, tr->info.dpu.godina);
                printf("Datum potpisivanja ugovora: %d.%d.%d.\n",tr->info.dpu.dan,tr->info.dpu.mjesec,tr->info.dpu.godina);
                printf("Mjesto stalnog boravka: %s\n",tr->info.mjbor);
                printf("JMB: %s\n",tr->info.JMB);
                printf("Plata: %d\n",tr->info.poc_pl);
                printf("Status: %s\n",tr->info.status.status);
                if(strcmp(tr->info.status.status,"Neaktivan")==0)
                    printf("Datum prekidanja radnog odnosa: %d.%d.%d.\n",tr->info.status.prekidzpsl.dan,tr->info.status.prekidzpsl.mjesec,tr->info.status.prekidzpsl.godina);
            }
            tr=tr->next;
        }
        if(indikator_pretrage!=1)
            printf("Neuspjesna pretraga!\n");
    }
    printf("===================================\n");
}

void upotreba_HR_aplikacije(char licenca[])
{
    CVOR* glava=NULL;
    int m;
    m=ucitavanje_iz_datoteke(&glava);
    int i;
    char kraj[MAX];
    do
    {
        printf("===================================\n");
        printf("Izaberite opciju 1,2,3,4,5,6:\n");
        printf("1. Dodavanje novog zaposlenog.\n");
        printf("2. Pregled prijave radnog vremena radnika.\n");
        printf("3. Aktivacija/deaktivacija zaposlenog.\n");
        printf("4. Pregled svih radnika po sektoru.\n");
        printf("5. Pregled svih radnika po radnom mjestu.\n");
        printf("6. Pretraga radnika po imenu ili prezimenu.\n");
        printf("7. Informacije.\n");
        printf("===================================\n");
        printf("Vas izbor: ");
        scanf("%d",&i);
        if(i==1)
            dodavanje_novog_zaposlenog(m,licenca);
        else if(i==2)
            pregled_prijave_radnogvr(&glava);
        else if(i==3)
            aktivacija_deaktivacija();
        else if(i==4)
            pregled_po_sektoru(&glava);
        else if(i==5)
            pregled_po_rmjestu(&glava);
        else if(i==6)
            pretraga_po_imenu_prezimenu(&glava);
        else if(i==7)
            InformacijeOFirmi();
        else
            printf("NEPOZNATA OPCIJA.\n");
        printf("Ukoliko zelite da prekinete unesite KRAJ, u suprotnom unesite bilo koje slovo sa tastature! ");
        scanf("%s",kraj);
    }
    while(strcasecmp(kraj,"KRAJ")!=0);
}

int provjera_licence()
{
    char s[MAX];
    printf("Unesite alfanumericki kljuc: ");
    scanf("%s",s);
    FILE* fp;
    if((fp=fopen("Licenca.txt","r"))!=NULL)
    {
        char licenca[MAX],pom[MAX];
        fscanf(fp,"%s\n", licenca);
        if(strcmp(licenca,s)==0)
            return 1;
        else
            return -1;
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
    else printf("ERROR!");
    int indikator=0;
    FILE* fp;
    char pom1[MAX],pom2[MAX];
    if((fp=fopen("Config.txt","r"))!=NULL)
    {
        fscanf(fp,"%s %s %d\n",pom1,pom2,&moguciBrojPrijava);
        fclose(fp);
    }
    else printf("ERROR! Nemoguce otvoriti konfiguracioni fajl!\n");
    char kraj[MAX]="";
    if((provjera_licence())==1)
    {
        do
        {
            indikator=pristup_HR_aplikaciji();
            if(indikator==-1)
            {
                printf("~~~Pristup HR aplikaciji odbijen! Pokusajte ponovo!\nUkoliko zelite da odustanete ukucajte KRAJ, inace unesite bilo koje slovo sa tastature.~~~\n");
                scanf("%s",kraj);
            }
        }
        while((strcasecmp(kraj,"KRAJ"))!=0 && indikator==-1);
        if(indikator!=-1)
            upotreba_HR_aplikacije("sa licencom");
    }
    else
    {
        indikator=0;
        printf("Neispravan alfanumericki kljuc!\n");
        printf("Pristupate HR aplikaciji bez licence! Vase mogucnosti su ogranicene!\n");
        do
        {
            indikator=pristup_HR_aplikaciji();
            if(indikator==-1)
            {
                printf("~~~Pristup HR aplikaciji odbijen! Pokusajte ponovo!\nUkoliko zelite da odustanete ukucajte KRAJ, inace unesite bilo koje slovo sa tastature.~~~\n");
                scanf("%s",kraj);
            }
        }
        while((strcasecmp(kraj,"KRAJ"))!=0 && indikator==-1);
        if(indikator!=-1)
            upotreba_HR_aplikacije("bez licence");
    }
    return 0;
}

