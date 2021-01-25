#include <stdio.h>
#include <stdlib.h>
#define MAX1 100

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
    InformacijeOFirmi();
    return 0;
}
