//program-6
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512
struct my_msg {
    long int msg_type;
    char text[MAX_TEXT];
};
void transmitter() {
    int running = 1;
    int msgID;
    struct my_msg data;
    char buffer[50];

    msgID = msgget((key_t)14534, 0666 | IPC_CREAT);

    if (msgID == -1) {
        printf("Error in creating the queue!\n");
        exit(0);
    }

    while (running) {
        printf("Enter some text: \n");
        fgets(buffer, 50, stdin);
        data.msg_type = 1;
        strcpy(data.text, buffer);

        if (msgsnd(msgID, (void*)&data, MAX_TEXT, 0) == -1) {
            printf("Message not sent!\n");
        }

        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }
}


// reciever
void reciever() {
    int running = 1;
    int msgID;
    struct my_msg data;
    long int msg_to_rec = 1;

    msgID = msgget((key_t)14534, 0666 | IPC_CREAT);

    if (msgID == -1) {
        printf("Error in accessing the queue!\n");
        exit(0);
    }

    while (running) {
        if (msgrcv(msgID, (void*)&data, MAX_TEXT, msg_to_rec, 0) == -1) {
            printf("Message not received!\n");
            exit(0);
        }
        printf("Data received: %s\n", data.text);

        if (strncmp(data.text, "end", 3) == 0) {
            running = 0;
        }
    }

    if (msgctl(msgID, IPC_RMID, 0) == -1) {
        printf("Error in deleting the message queue!\n");
        exit(0);
    }
}
int main()
{
    transmitter();
    reciever();
    return 0;
}
