// increment and decrement shared counter using mutex

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex;

void *increment()
{
    pthread_mutex_lock(&mutex);
    while(count < 10) 
    {
        count++;
        printf("Incremented Count: %d\n", count);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit("Increment thread executed successfully!\n");
}

void *decrement()
{
    pthread_mutex_lock(&mutex);
    while(count > 0) 
    {
        count--;
        printf("Decremented Count: %d\n", count);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit("Decrement thread executed successfully!\n");
}

int main() 
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t ithread, dthread;
    void *thread_res;

    pthread_create(&ithread, NULL, increment, NULL);
    pthread_create(&dthread, NULL, decrement, NULL)
    
    pthread_join(ithread, &thread_res);
    printf("Increment thread joined, %s", (char *)thread_res);

    pthread_join(dthread, &thread_res);
    printf("Decrement thread joined, %s", (char *)thread_res);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
