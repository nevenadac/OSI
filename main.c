#include <stdio.h>
#include <stdlib.h>
#include<string.h>


void aktiviraj(FILE *fp, char* fname)
{
   char korisnickoIme[20];
   char hrLozinka[20];
           printf("Unesite korisnicko ime: \n");
           scanf("%s",korisnickoIme);
           strcpy(hrLozinka,fname);
          if(fp=fopen(fname,"w"))
          {
           fprintf(fp,"%s %s\n",korisnickoIme,hrLozinka);
          }
          fclose(fp);
}
void deaktiviraj(FILE *fp, char *fname)
{
    if(!remove(fname))
            printf("Uspjesna deaktivacija.\n");
          else
            printf("Ne postoji zaposleni sa navedenim PIN kodom.\n");
}
int main( )
{
   char *lozinka="admin123";
   char unos[20];
   char b;
   char fname[20];
   char korisnickoIme[20];
   char hrLozinka[20];
   FILE *fp;

   printf("Unesite lozinku: ");
   scanf("%s",unos);

   if(!strcmp(lozinka,unos))
   {

     do
     {
      printf("Za aktivaciju unesite 'A', za deaktivaciju 'D',a za izlaz '0'.\n");
      scanf("\n%c",&b);

      if(b=='A')
      {
    printf("Unesite PIN korisnika: \n");
      scanf("%s",fname);
      aktiviraj(fp,fname);
      }
      else if(b=='D')
      {
          printf("Unesite PIN kod korisnika: \n");
      scanf("%s",fname);
          deaktiviraj(fp,fname);
      }
      else if(b!='0')
        printf("Nepoznata opcija.\n");
     }while(b!='0');
     printf("KRAJ.\n");
   }
   else
    printf("Nemoguc pristup administratorskoj aplikaciji.\n");

   return 0;
}
