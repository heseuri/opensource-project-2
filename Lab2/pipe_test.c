
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buf[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(fd[1]);

        int n = read(fd[0], buf, sizeof(buf) - 1);
        if (n < 0) {
            perror("read");
            close(fd[0]);
            return 1;
        }

        buf[n] = '\0';
        printf("자식이 받은 메시지: %s\n", buf);

        close(fd[0]);
    }
    else {
        close(fd[0]);

        char msg[] = "Hello from parent";
        write(fd[1], msg, strlen(msg));

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}

