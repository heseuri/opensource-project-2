
#include <stdio.h>
#include <signal.h>

void handler(int sig)
{
    printf("시그널 번호: %d\n", sig);
    printf("SIGINT 시그널을 받았습니다.\n");
}

int main()
{
    signal(SIGINT, handler);

    printf("시그널 처리 프로그램 실행\n");

    raise(SIGINT);

    printf("프로그램 종료\n");

    return 0;
}

