#include<stdio.h>
#include<pthread.h>

int totalBooks = 100;

void* add_books(void *wno)
{
    totalBooks=totalBooks+20;
    printf("Librarian %d added 20 books. Total books is %d\n",*((int *)wno),totalBooks);
}
void* remove_books(void *wno)
{
    totalBooks=totalBooks-10;
    printf("Librarian %d removed 10 books. Total books present are %d\n",*((int *)wno),totalBooks);
}

void *reader(void *rno)
{
    printf("Reader %d sees that total books present are %d\n",*((int *)rno),totalBooks);
}


int main () 
{
    pthread_t librarian_threads[5],reader_threads[10];

    int actions[]= {'R','A','R','A','R'};
    int ids[10]={1,2,3,4,5,6,7,8,9,10};

    for(int i=0;i<5;i++)
    {
        pthread_create(&reader_threads[i],NULL,reader,(void *)&ids[i]);
    }
    for (int i = 0; i < 5; i++) {
        if(actions[i]='A')
        {
            pthread_create(&librarian_threads[i],NULL,add_books,(void *)&ids[i]);
        }else {
            pthread_create(&librarian_threads[i],NULL,remove_books,(void *)&ids[i]);
        }
    }

    for(int i=5;i<10;i++)
    {
        pthread_create(&reader_threads[i],NULL,reader,(void *)&ids[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(reader_threads[i],NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(librarian_threads[i],NULL);
    }


}