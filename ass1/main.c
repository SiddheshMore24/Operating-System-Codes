#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


int main ()
{
    int choice;

    printf("You are in parent process \n");
    printf("pid: %d\n",getpid());
    printf("ppid: %d\n",getppid());
 
    do{

        printf("Enter your choice : 1 for grep and 2 for cp and 3 for exit :");

        scanf("%d",&choice);

        if(choice==1 || choice==2)
        {
            pid_t pid = fork();

            if(pid==0)
            {
                printf("You are in child process\n");
                printf("pid: %d\n",getpid());
                printf("ppid: %d\n",getppid());
                if(choice==1)
                {
                    char f[100];
                    char p[100];
    
                    printf("enter file name : ");
                    scanf("%s",f);
                    printf("enter pattern : ");
                    scanf("%s",p);
                    execlp("./grep","grep",p,f,NULL);
                }else if(choice ==2)
                {
                    char source[100];
                    char destination[100];
    
                    printf("Enter source file: ");
                    scanf("%s",source);
                    printf("Enter destination file: ");
                    scanf("%s",destination);
    
                    execlp("./cp","cp",source,destination,NULL);
    
                }
                perror("execlp failed");
                exit(1);

            }else if(pid>0)
            {
                wait(NULL);
            }else 
            {
                perror("failed");
            }
           
        }else{
            printf("Thank You!! Tata");

            break;
        }
    }while(choice!=3);

    return 0;

    
}