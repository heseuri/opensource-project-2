
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long type;
    char text[100];
};

int main()
{
    int msgid;
    struct message msg;

    msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    msg.type = 1;
    strcpy(msg.text, "Hello Message Queue");

    msgsnd(msgid, &msg, sizeof(msg.text), 0);
    printf("보낸 메시지: %s\n", msg.text);

    msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);
    printf("받은 메시지: %s\n", msg.text);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

