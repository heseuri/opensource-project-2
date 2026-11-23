
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[100];

    fd = open("myfifo", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int n = read(fd, buf, sizeof(buf) - 1);
    if (n < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    buf[n] = '\0';
    printf("받은 메시지: %s\n", buf);

    close(fd);

    return 0;
}

