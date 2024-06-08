// program 2


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


// demonstrate the usage of signal : when CTRL + C is pressed signal is ignored 
int main()
{
    (void) signal(SIGINT, SIG_IGN);
    while(1)
    {
        printf("%d\n", getpid());
        sleep(1);
    }
}