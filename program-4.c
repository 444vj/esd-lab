//program-4
//One thread reads the input from the keyboard and another thread converts to upper case. 
//This is done until Stop‟ is pressed. Use concept of semaphore, so that multiple printing is avoided.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 1024

sem_t sem;
char buffer[BUFFER_SIZE];

void *read_thread(void *arg)
{
    while(strncmp("stop",buffer,4) != 0)
    {
        printf("Enter text:  ");
        fgets(buffer, BUFFER_SIZE, stdin);
        sem_post(&sem);
        sleep(2);
    }
    pthread_exit("read_thread exit successful");
}


void *convert_thread()
{
    int i;
    sem_wait(&sem);
    while(strncmp("stop", buffer, 4) != 0)
    {
        printf("Converted text:  ");
        for(i=0; i<strlen(buffer); i++)
        {
            printf("%c", toupper(buffer[i]));
        }
        sem_wait(&sem);
    }
    pthread_exit("convert_thread exit successful");
}


int main()
{
    int result;
    pthread_t rthread, cthread;
    void *thread_result;
    sem_init(&sem, 0, 1);

    printf("Enter text, the program will convert it into upper case, \n To stop enter 'stop' \n");

    pthread_create(&cthread, NULL, convert_thread, NULL);
    pthread_create(&rthread, NULL, read_thread, NULL);

    pthread_join(rthread, &thread_result);
    printf("read_thread joined, %s\n", (char *)thread_result);

    pthread_join(cthread, &thread_result);
    printf("convert_thread joined, %s\n", (char *)thread_result);

    sem_destroy(&sem);
    exit(0);
}
