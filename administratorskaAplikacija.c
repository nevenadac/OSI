#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct info
{
    char korisnickoIme[20];
    char hrLozinka[20];
    int brojPr;
} INFO;

typedef struct nalog
{
    char JMB[14];
    char korisnickoIme[20];
    char lozinka[20];
    int pin;
    int brojPr;
} KNALOG;

typedef struct cvor1
{
    struct cvor1* next;
    KNALOG info;
} CVOR1;

typedef struct cvor
{
    struct cvor* next;
    INFO info;
} CVOR;

void pisi(CVOR *glava, FILE *fp)
{
    while (glava)
    {
        fprintf(fp, "%s %s %d\n", glava->info.korisnickoIme,glava->info.hrLozinka,glava->info.brojPr);
        glava = glava->next;
    }
}

void pisi2(CVOR1 *glava, FILE *fp)
{
    while (glava)
    {
        fprintf(fp, "%s %s %s %d %d\n", glava->info.JMB,glava->info.korisnickoIme,glava->info.lozinka,glava->info.pin,glava->info.brojPr);
        glava = glava->next;
    }
}


int provjeri_kor_ime(char kor_ime[])
{
    FILE* fp;
    char username[20],pom2[20];
    int d;
    int flag=0;
    if((fp=fopen("HRkorisnickinalozi.txt","r"))!=NULL)
    {
        while((fscanf(fp,"%s %s %d\n",username,pom2,&d))!=EOF)
        {
            if(strcasecmp(username,kor_ime)==0)
                flag=1;
        }
        fclose(fp);
    }
    else
        printf("ERROR! Ne postoji datoteka sa HR nalozima.\n");
    if(flag==1)
        return 1;
    else
        return 0;
}


void aktiviraj(FILE *fp)
{
    char ime[20];
    char hrLozinka[20];
    int br=0;
    printf("\nUnesite korisnicko ime:");
    scanf("%s",ime);
    int flag1=0;
    do
    {
        flag1=provjeri_kor_ime(ime);
        if(flag1==1)
        {
            printf("Uneseno korisnicko ime vec postoji! Unesite novo korisnicko ime! ");
            scanf("%s",ime);
        }
    }
    while(flag1==1);

    //printf("Unesite lozinku:");
    //scanf("%s",hrLozinka);
    while(1)
    {
        printf("Unesite lozinku:");
        scanf("%s",hrLozinka);
        if((strlen(hrLozinka))>5)
            break;
        else
            printf("Lozinka mora imati minimalno 6 znakova!\n");
    }

    if((fp=fopen("HRkorisnickinalozi.txt","a")))
    {
        fprintf(fp,"%s %s %d\n",ime,hrLozinka,br);
        printf("\nHR nalog uspjesno kreiran!\n");
    }
    else
        printf("Greska prilikom otvaranja datoteke sa HR nalozima!\n");
    fclose(fp);
}

CVOR* dodaj_u_listu(CVOR **pglava,INFO data)
{
    CVOR *novi=(CVOR*)malloc(sizeof(CVOR));
    novi->info=data;
    novi->next=*pglava;
    *pglava=novi;
    return novi;
}

CVOR1* dodaj_u_listu1(CVOR1 **pglava,KNALOG data)
{
    CVOR1 *novi=(CVOR1*)malloc(sizeof(CVOR1));
    novi->info=data;
    novi->next=*pglava;
    *pglava=novi;
    return novi;
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

void brisi_listu1(CVOR1 **pglava)
{
    while(*pglava)
    {
        CVOR1* p=(*pglava)->next;
        free(*pglava);
        *pglava=p;
    }
}

void deleteNode(CVOR **head_ref,char * key)
{
    CVOR* temp = *head_ref, *prev;
    if (temp != NULL && strcmp(temp->info.korisnickoIme,key)==0)
    {
        *head_ref = temp->next;
        free(temp);
        printf("\nHR nalog je uspjesno deaktiviran!\n");
        return;
    }
    while (temp != NULL && strcmp(temp->info.korisnickoIme,key))
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\nUneseno korisnicko ime ne postoji!\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("\nHR nalog je uspjesno deaktiviran!\n");
}

void deleteNode1(CVOR1 **head_ref,char * key)
{
    CVOR1* temp = *head_ref, *prev;
    if (temp != NULL && strcmp(temp->info.korisnickoIme,key)==0)
    {
        *head_ref = temp->next;
        free(temp);
        printf("\nKorisnicki nalog je uspjesno deaktiviran!\n");
        return;
    }
    while (temp != NULL && strcmp(temp->info.korisnickoIme,key))
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\nUneseno korisnicko ime ne postoji!\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("\nKorisnicki nalog je uspjesno deaktiviran!\n");
}

void deaktivacijaHrNaloga()
{
    char korIme[25];
    INFO nalogDat;
    CVOR *head=NULL;
    printf("\nUnesite korisnicko ime radnika ciji HR nalog zelite da deaktivirate:");
    scanf("%s",korIme);
    FILE* nalozi;
    if((nalozi=fopen("HRkorisnickinalozi.txt","r")))
    {
        while((fscanf(nalozi,"%s %s %d\n",nalogDat.korisnickoIme,nalogDat.hrLozinka,&nalogDat.brojPr))!=EOF)
            dodaj_u_listu(&head,nalogDat);
    }
    fclose(nalozi);
    deleteNode(&head,korIme);
    if((nalozi=fopen("HRkorisnickinalozi.txt","w")))
        pisi(head,nalozi);
    fclose(nalozi);
    brisi_listu(&head);
}

void deaktivacijaKorisnickihNaloga()
{
    char korIme[25];
    KNALOG nalogDat;
    CVOR1 *head=NULL;
    printf("Unesite korisnicko ime radnika ciji korisnicki nalog zelite da deaktivirate:");
    scanf("%s",korIme);
    FILE* nalozi;
    if((nalozi=fopen("korisnickiNalozi.txt","r")))
    {
        while((fscanf(nalozi,"%s %s %s %d %d\n",nalogDat.JMB,nalogDat.korisnickoIme,nalogDat.lozinka,&nalogDat.pin,&nalogDat.brojPr))!=EOF)
            dodaj_u_listu1(&head,nalogDat);
        fclose(nalozi);
    }
    else
        printf("Ne postoji datoteka sa korisnickim nalozima.\n");
    deleteNode1(&head,korIme);
    if((nalozi=fopen("korisnickiNalozi.txt","w")))
    {
        pisi2(head,nalozi);
        fclose(nalozi);
    }
    brisi_listu1(&head);
}

int broj_korisnika(FILE *fp,int m,INFO info)
{
    if((fp=fopen("HRkorisnickinalozi.txt","r")))
    {
        while(fscanf(fp,"%s %s %d\n",info.korisnickoIme,info.hrLozinka,&info.brojPr)!=EOF)
            m++;
    }
    return m;
}

int main(int argc, char*argv[])
{
    char *lozinka="alfanumkey123";
    char unos[20];
    char pin[20];
    char lozinka_admin[20];
    char b;
    FILE *fp;
    INFO info;
    int broj,m=0;
    char s[100];
    if((fp=fopen("Config.txt","r")))
    {
        fgets(s,100,fp);
        fgets(s,100,fp);
        printf("%s\n",s);
        fclose(fp);
    }
    else
        printf("ERROR! Ne postoji konfiguracioni fajl!\n");
    if((fp=fopen("admin.txt","r"))!=NULL)
    {
        printf("Unesite administratorsku lozinku:");
        scanf("%s",pin);

        fscanf(fp,"%s",s);
        if(strcmp(s,pin)==0)
        {
            printf("Da li posjedujete licencu?\n");
            printf("Ako imate unesite '1', inace unesite '2':");
            scanf("%d",&broj);
            if(broj==1)
            {
                printf("Unesite alfanumericki kljuc:");
                scanf("%s",unos);
                if(!strcmp(lozinka,unos)==0)
                    do
                    {
                        printf("Neispravna lozinka! Ukoliko ne zelite da nastavite unesite KRAJ, inace unesite ponovo lozinku! ");
                        scanf("%s",unos);
                    }
                    while(strcmp(lozinka,unos)!=0 && strcasecmp(unos,"KRAJ")!=0);
                if(strcasecmp(unos,"KRAJ")!=0)
                {
                    do
                    {
                        printf("\nOpcije:\n");
                        printf(" -Aktivacija HR naloga 'A'\n");
                        printf(" -Deaktivacija HR naloga 'D'\n");
                        printf(" -Deaktivacija naloga za korisnicku aplikaciju 'K'\n");
                        printf(" -Informacije o kompaniji 'I'\n");
                        printf(" -Kraj '0'\n");
                        printf("\nODABERITE OPCIJU:");
                        scanf("\n%c",&b);
                        if(b=='A')
                        {
                            aktiviraj(fp);
                        }
                        else if(b=='D')
                        {
                            deaktivacijaHrNaloga();
                        }
                        else if(b=='K')
                        {
                            deaktivacijaKorisnickihNaloga();
                        }
                        else if(b=='I')
                        {
                            printf("\n\nKONTAKT INFORMACIJE:");
                            printf("\n------------------------------------------------------\n");
                            if((fp=fopen("Config.txt","r")))
                            {
                                fgets(s,100,fp);
                                fgets(s,100,fp);
                                while(fgets(s,100,fp))
                                {
                                    printf("%s",s);
                                }
                                fclose(fp);
                            }
                            else
                                printf("Greska prilikom otvaranja konfiguracionog fajla!\n");
                            printf("\n------------------------------------------------------\n\n");
                        }
                        else if(b!='0')
                            printf("Nepoznata opcija.\n");
                    }
                    while(b!='0');
                }
            }
                else if(broj==2)
                {

                    do
                    {
                        //printf("\nZa aktivaciju unesite 'A',za deaktivaciju 'D',za ispis informacija 'I',a za kraj '0':\n");
                        printf("\nOpcije:");
                        printf("\n -Aktivacija HR naloga 'A'\n -Deaktivacija HR naloga 'D'\n -Deaktivacija naloga za korisnicku aplikaciju 'K'\n -Informacije o kompaniji 'I'\n -Kraj '0'\n");
                        printf("ODABERITE OPCIJU:");
                        scanf("\n%c",&b);
                        if(b=='A')
                        {
                            int i=broj_korisnika(fp,m,info);
                            if(i>=3)
                                printf("Nemoguce dodati kosinika zbog ogranicenja.\n");
                            else
                                aktiviraj(fp);
                        }
                        else if(b=='D')
                        {

                            deaktivacijaHrNaloga();
                        }
                        else if(b=='K')
                        {
                            deaktivacijaKorisnickihNaloga();
                        }
                        else if(b=='I')
                        {
                            printf("\n\nKONTAKT INFORMACIJE:");
                            printf("\n------------------------------------------------------\n");
                            if((fp=fopen("Config.txt","r")))
                            {
                                fgets(s,100,fp);
                                fgets(s,100,fp);
                                while(fgets(s,100,fp))
                                {
                                    printf("%s",s);
                                }
                                fclose(fp);
                            }
                            else
                                printf("Greska prilikom otvaranja konfiguracionog fajla!\n");
                            printf("\n------------------------------------------------------\n\n");
                        }
                        else if(b!='0')
                            printf("Nepoznata opcija.\n");
                    }
                    while(b!='0');
                }
                else
                    printf("Greska.\n");
            printf("\nKraj.\n");
        }
    else
        printf("ERROR! Neispravna lozinka! Pristup administratorskoj aplikaciji odbijen! Pokrenite program ponovo za novi pokusaj.\n");
    fclose(fp);
}
else
    printf("Ne postoji datoteka admin.txt!\n");
return 0;
}
