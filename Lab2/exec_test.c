
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("ls 명령어 실행 전\n");
    fflush(stdout);

    execlp("ls", "ls", "-l", NULL);

    perror("execlp 실패");

    return 1;
}

