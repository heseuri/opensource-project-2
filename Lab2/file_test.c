
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[100];

    fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        printf("파일 열기 실패\n");
        return 1;
    }

    write(fd, "Hello Linux\n", 12);
    close(fd);

    fd = open("test.txt", O_RDONLY);

    int n = read(fd, buf, sizeof(buf) - 1);
    if (n < 0) {
        printf("파일 읽기 실패\n");
        close(fd);
        return 1;
    }
    buf[n] = '\0';

    printf("파일 내용: %s", buf);

    close(fd);
    return 0;
}

