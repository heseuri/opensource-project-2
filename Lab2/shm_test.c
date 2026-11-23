
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
    int shmid;
    char *ptr;
    pid_t pid;

    shmid = shmget(IPC_PRIVATE, 100, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    ptr = shmat(shmid, NULL, 0);

    if (ptr == (void *)-1) {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    strcpy(ptr, "Hello Shared Memory");

    pid = fork();

    if (pid < 0) {
        perror("fork");
    }
    else if (pid == 0) {
        printf("자식이 읽은 내용: %s\n", ptr);
        shmdt(ptr);
        return 0;
    }
    else {
        wait(NULL);
    }

    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

