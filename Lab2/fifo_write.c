
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
    int fd;
    char msg[] = "Hello FIFO";

    mkfifo("myfifo", 0666);

    fd = open("myfifo", O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, msg, strlen(msg) + 1);
    printf("메시지 전송: %s\n", msg);

    close(fd);

    return 0;
}

