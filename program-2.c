// program 2

// Exam - Write a C program using signal function calls as follows: 
// when CTRL C is pressed a Signal, with
// message, “Press CTRL Z to terminate” should be sent.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int signal)
{
    printf("\nPress CTRL+Z to terminate\n");
}

void sigtstp_handler(int signal)
{
    printf("\nTermination signal received. Exiting...\n");
    exit(0);
}

int main()
{
    // Set up signal handlers
    (void) signal(SIGINT, sigint_handler);
    (void) signal(SIGTSTP, sigtstp_handler);

    while(1)
    {
        printf("Running... (press CTRL+C to see the message)\n");
        sleep(2);
    }

    return 0;
}

//Exam -  demonstrate the usage of signal : when CTRL + C is pressed signal is ignored 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
   // Press Ctrl+C to ignore (SIGINT)
   signal(SIGINT, SIG_IGN); 
   while (1) {
       printf("Press Ctrl+C (ignored)...\n");
       sleep(1);
    }
   return 0;
}


// lab codes

// demonstrate the usage of signal : when CTRL + C is pressed signal is sent 
// for abrupt termination
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void my_handler(int signal)
{
    printf("Problem Encountered %d\n", signal);
}
 
int main()
{
    (void) signal(SIGINT, my_handler);
    while(1)
    {
        printf("Hello\n");
        sleep(2);
    }
}