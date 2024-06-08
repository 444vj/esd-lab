//program-3

//Write a C program for : One thread reads the input from the keyboard and another thread converts to upper case. 
//This is done until "STOP" is pressed. Use concept of multithreading
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];

void *read_thread(void *arg)
{
  while (strncmp ("stop", buffer, 4) != 0)
    {
      printf ("Enter text:  ");
      fgets (buffer, BUFFER_SIZE, stdin);
      sleep (1);
    }
  pthread_exit ("read_thread exit successful");
}

void *convert_thread()
{
    int i;
    while (strncmp ("stop", buffer, 4) != 0)
    {
        sleep (1);
        printf ("Converted text:  ");
        for (i = 0; i < strlen (buffer); i++)
        {
            printf ("%c", toupper(buffer[i]));
        }
    }
    pthread_exit ("convert_thread exit successful");
}

int main ()
{
    int result;
    pthread_t rthread, cthread;
    void *thread_result;

    printf("Enter text, the program convertS it to upper case, \n To stop enter 'stop' \n");
    
    pthread_create (&rthread, NULL, read_thread, NULL);
    pthread_create (&cthread, NULL, convert_thread, NULL);

    pthread_join (rthread, &thread_result);
    printf("read_thread joined, %s\n",(char *)thread_result);
    
    pthread_join(cthread, &thread_result);
    printf ("convert_thread joined, %s\n", (char *) thread_result);
    
    return(0);
}


