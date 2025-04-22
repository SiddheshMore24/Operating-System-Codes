#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t wrt;
pthread_mutex_t mutex;
int totalBooks=100;
int numReaders=0;

void *add_books(void *wno){
    int add = 20;
    sem_wait(&wrt);
    totalBooks+=add;
    printf("Librarian %d added %d books and now total books are %d :\n",*((int *)wno),add,totalBooks);
    sem_post(&wrt);
}
void *remove_books(void *wno)
{
    int removed= 10;
    sem_wait(&wrt);
    totalBooks-=removed;
    printf("Librarian %d removed %d and now total books are %d :\n",*((int *)wno),removed,totalBooks);
    sem_post(&wrt);
}

void *reader(void *rno)
{
    pthread_mutex_lock(&mutex);
    numReaders++;
    if(numReaders==1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d sees that there are %d books \n",*((int*)rno),totalBooks);

    pthread_mutex_lock(&mutex);
    numReaders--;
    if(numReaders==0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

int main () 
{
    pthread_t librarian_threads[5],reader_threads[10];
    int ids[10]={1,2,3,4,5,6,7,8,9,10};
    int actions[]={'R','A','R','A','R'};
    pthread_mutex_init(&mutex,NULL);
    sem_init(&wrt,0,1);

    for (int i=0;i<5;i++)
    {
        pthread_create(&reader_threads[i],NULL,reader,(void *)&ids[i]);
    }
    for (int i = 0; i < 10; i++) {
        if(actions[i]=='A')
        {
            pthread_create(&librarian_threads[i],NULL,add_books,(void *)&ids[i]);
        }else {
            pthread_create(&reader_threads[i],NULL,remove_books,(void *)&ids[i]);
        }
    }
    for (int i = 5; i < 10; i++) {
        pthread_create(&reader_threads[i],NULL,reader,(void *)&ids[i]);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(reader_threads[i],NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(librarian_threads[i],NULL);
    }
    return 0;


}


