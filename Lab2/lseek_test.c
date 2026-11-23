
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[10];

    // 파일 생성 후 읽기/쓰기 모드로 열기
    fd = open("seek.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (fd < 0) {
        printf("파일 열기 실패\n");
        return 1;
    }

    // 파일에 문자열 저장
    write(fd, "ABCDEFGHIJ", 10);

    // 파일 위치를 처음에서 5바이트 떨어진 곳으로 이동
    lseek(fd, 5, SEEK_SET);

    // 현재 위치부터 3바이트 읽기
    int n = read(fd, buf, 3);
    if (n < 0) {
        printf("파일 읽기 실패\n");
        close(fd);
        return 1;
    }
    buf[n] = '\0';

    printf("읽은 내용: %s\n", buf);

    close(fd);

    return 0;
}

