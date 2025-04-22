#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main (int argc, char *argv[])
{
    if(argc!=3)
    {
        printf("There should be 3 arguments");
        return 1;
    }

    int sourceFile= open(argv[1],O_RDONLY);
    if(sourceFile==-1)
    {
        printf("Error in source file");
    
    }
    int destinationFile = open (argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(destinationFile==-1)
    {
        printf("Error in destination file");
    
    }

    char buffer [50];
    int bytes;
    while((bytes=read(sourceFile,buffer,sizeof(buffer)))>0)
    {
        write(destinationFile,buffer,bytes);
    }
    close(sourceFile);
    close(destinationFile);
    return 0;
}