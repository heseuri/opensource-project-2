
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork 실패");
        return 1;
    }

    if (pid == 0) {
        printf("자식 프로세스 실행\n");
        exit(5);
    }
    else {
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            printf("자식 종료값: %d\n", WEXITSTATUS(status));
    }

    return 0;
}

