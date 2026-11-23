
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("현재 프로세스 PID: %d\n", getpid());
    printf("부모 프로세스 PPID: %d\n", getppid());

    return 0;
}

