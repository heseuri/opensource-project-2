
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    const char msg[] = "알람 시그널 발생!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main()
{
    struct sigaction sa = {0};

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    printf("3초 후 알람이 발생합니다.\n");
    fflush(stdout);

    alarm(3);
    pause();

    printf("프로그램 종료\n");

    return 0;
}

