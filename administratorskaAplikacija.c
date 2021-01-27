#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct info
{
    char korisnickoIme[20];
    char hrLozinka[20];
} INFO;

typedef struct cvor
{
    struct cvor* next;
    INFO info;
} CVOR;

void pisi(CVOR *glava, FILE *fp)
{
    while (glava)
    {
        fprintf(fp, "%s %s\n", glava->info.korisnickoIme,glava->info.hrLozinka);
        glava = glava->next;
    }
}

void aktiviraj(FILE *fp)
{
    char korisnickoIme[20];
    char ime[20];
    char hrLozinka[20];
    printf("\nUnesite korisnicko ime:");
    scanf("%s",ime);
    if((fp=fopen("HRkorisnickinalozi.txt","r"))!=NULL)
    {
        while((fscanf(fp,"%s %s\n",korisnickoIme,hrLozinka)!=EOF))
        {
            if(strcasecmp(korisnickoIme,ime)==0)
            {
                do
                {
                    printf("Uneseno korisnicko ime vec postoji!\nUnesite novo korisnicko ime:");
                    scanf("%s",ime);
                }
                while(strcasecmp(korisnickoIme,ime)==0);
            }
        }
        fclose(fp);
    }

    printf("Unesite lozinku:");
    scanf("%s",hrLozinka);
    if((fp=fopen("HRkorisnickinalozi.txt","a")))
    {
        fprintf(fp,"%s %s\n",ime,hrLozinka);
        printf("\nHR nalog uspjesno kreiran!\n");
    }
    else printf("Greska prilikom otvaranja datoteke sa HR nalozima!\n");
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

void brisi_listu(CVOR **pglava)
{
    while(*pglava)
    {
        CVOR* p=(*pglava)->next;
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
        printf("\nNalog je uspjesno deaktiviran!\n");
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
    printf("\nNalog je uspjesno deaktiviran!\n");
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
        while((fscanf(nalozi,"%s %s\n",nalogDat.korisnickoIme,nalogDat.hrLozinka))!=EOF)
            dodaj_u_listu(&head,nalogDat);
    }
    fclose(nalozi);
    deleteNode(&head,korIme);
    if((nalozi=fopen("HRkorisnickinalozi.txt","w")))
        pisi(head,nalozi);
    fclose(nalozi);
    brisi_listu(&head);
}


int broj_korisnika(FILE *fp,int m,INFO info)
{
    if((fp=fopen("HRkorisnickinalozi.txt","r")))
    {
        while(fscanf(fp,"%s %s",info.korisnickoIme,info.hrLozinka)!=EOF)
            m++;
    }
    return m;
}

int main(int argc, char*argv[])
{
    char *lozinka="admin123";
    char unos[20];
    char pin[10];
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
    printf("Unesite administratorsku lozinku: \n");
    scanf("%s",pin);
    if((fp=fopen("admin.txt","r")))
    {
        fgets(s,100,fp);
        if(!strcmp(s,pin))
        {
            printf("Da li posjedujete licencu?\n");
            printf("Ako imate unesite '1', inace unesite '2':\n");
            scanf("%d",&broj);
            if(broj==1)
            {
                do
                {
                    printf("Unesite alfanumericki kljuc:\n");
                    scanf("%s",unos);
                }
                while(!strcmp(lozinka,unos)==0);
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
                        //deaktivacijaKorisnickihNaloga();
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
                        else printf("Greska prilikom otvaranja konfiguracionog fajla!\n");
                        printf("\n------------------------------------------------------\n\n");
                    }
                    else if(b!='0')
                        printf("Nepoznata opcija.\n");
                }
                while(b!='0');


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
                        //deaktivacijaKorisnickihNaloga();
                    }
                    else if(b=='I')
                    {
                        printf("\n\nKONTAKT INFORMACIJE:");
                        printf("\n------------------------------------------------------");
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
                        else printf("Greska prilikom otvaranja konfiguracionog fajla!\n");
                        printf("------------------------------------------------------\n\n");
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
            printf("Nemoguc pristup administratorskoj aplikaciji.\n");

    }
    return 0;
}
