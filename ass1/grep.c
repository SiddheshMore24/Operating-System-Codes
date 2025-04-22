#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("Only 3 arg");
        return 1;
    }

    const char* pattern = argv[1];
    const char* filename = argv[2];
    char line[500];

    FILE *fp = fopen(filename,"r");

    if(fp==NULL)
    {
        printf("Error in opening file");
        return 1;
    }

    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        char *match = strstr(line,pattern);
        if(match)
        {
            printf("Yes it matches");

        }else 
        {
            printf("No it not matches");
        }
    }

    return 0;

}