#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
void handler(int sig)
{    const char msg[] = "자식이 SIGUSR1을 받았습니다.\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}int main()
{    pid_t pid;
    // 자식에게 상속될 시그널 처리 함수 등록
    signal(SIGUSR1, handler);
    pid = fork();
    if (pid < 0) {
        perror("fork 실패");
        return 1;
    }
    else if (pid == 0) {
        printf("자식 프로세스 대기 중\n");
        fflush(stdout);
        pause();
    }
    else {
        sleep(1);
        printf("부모가 시그널 전송\n");
        fflush(stdout);
        kill(pid, SIGUSR1);
        wait(NULL);
    }
    return 0;
}
