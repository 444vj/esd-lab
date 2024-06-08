// program 1
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
// creation of processes using fork
int main()
{
    fork();
    fork();
    fork();
    printf("Hello\n");
    return 0;
}

// to demonstrate the usage of fork & wait
int main(){
    //parent process
    printf("I am parent process with pid = %d\n", (int)getpid())
    // child process
    pid_t pid = fork();
    printf("fork returned value: %d\n", (int) pid);

    if(pid < 0){
        printf("Fork Failed!");
    }
    if (pid == 0){
        printf("Child Process PID = %d\n", (int) getpid());
        printf("Child Process Exiting\n");
        exit(0);
    }
    printf("Parent process waiting for Child to terminate!\n");
    wait(NULL);
    printf("Parent process exiting!\n");
    return 0;
}

// fork example
void fork_example()
{
    int x = 1;
    if(fork() == 0){
        printf("Child has x = %d\n", ++x);
    }
    else{
        printf("Parent has x = %d\n", --x)
    }
}

int main()
{
    fork_example();
    return 0;
}


// extra

// Write a C program to demonstrate usage of fork with child and parent process ID 
// is printed and parent waits for child process to terminate.

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) 
    {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) 
    {
        // Child process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        // Perform some task in child process (e.g., sleep for a few seconds)
        sleep(2);
        printf("Child Process: Terminating\n");
        exit(0);
    } 
    else 
    {
        // Parent process
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
        // Wait for the child process to terminate
        wait(NULL);
        printf("Parent Process: Child terminated\n");
    }

    return 0;
}
