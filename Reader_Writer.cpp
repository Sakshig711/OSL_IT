#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readcount = 7;
sem_t x;
sem_t Wsem;

void* reader(void* arg) 
{
    while (1) 
    {
        sem_wait(&x);
        readcount++;
        if (readcount == 1) 
        {
            sem_wait(&Wsem);
        }
        sem_post(&x);    
        printf("Hello this is reader %d\n", readcount);
        sem_wait(&x);
        readcount--;
        if (readcount == 0) 
        {
            sem_post(&Wsem);
        }
        sem_post(&x);
        sleep(1);  
    }
    return NULL;
}

void* writer(void* arg) 
{
    while (1) 
    {
        sem_wait(&Wsem);
        printf("Hello this is writer\n");
        sem_post(&Wsem);
        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t r1thread, r2thread, wthread;
    
    sem_init(&x, 0, 1);
    sem_init(&Wsem, 0, 1);

   // readcount = 0;

    pthread_create(&r1thread, NULL, reader, NULL);
    pthread_create(&r2thread, NULL, reader, NULL);
    pthread_create(&wthread, NULL, writer, NULL);

    /*pthread_join(r1thread, NULL);
    pthread_join(r2thread, NULL);*/
    pthread_join(wthread, NULL);

    sem_destroy(&x);
    sem_destroy(&Wsem);

    return 0;
}



