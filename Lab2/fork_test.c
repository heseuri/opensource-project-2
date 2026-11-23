
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        printf("fork 실패\n");
        return 1;
    }
    else if (pid == 0) {
        printf("자식 프로세스 PID: %d\n", getpid());
        printf("부모 PID: %d\n", getppid());
    }
    else {
        wait(NULL);
        printf("부모 프로세스 PID: %d\n", getpid());
        printf("자식 프로세스 종료 확인\n");
    }

    return 0;
}

