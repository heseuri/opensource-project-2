
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    struct stat st;
    char *src, *dest;
    size_t size;

    if (argc != 3) {
        printf("사용법: %s 원본파일 복사파일\n", argv[0]);
        return 1;
    }

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        perror("원본 파일 열기 실패");
        return 1;
    }

    if (fstat(fd1, &st) == -1) {
        perror("파일 정보 확인 실패");
        close(fd1);
        return 1;
    }

    if (!S_ISREG(st.st_mode)) {
        printf("일반 파일만 복사할 수 있습니다.\n");
        close(fd1);
        return 1;
    }

    size = st.st_size;

    fd2 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd2 < 0) {
        perror("복사 파일 생성 실패");
        close(fd1);
        return 1;
    }

    if (ftruncate(fd2, size) == -1) {
        perror("파일 크기 설정 실패");
        close(fd1);
        close(fd2);
        return 1;
    }

    if (size == 0) {
        printf("빈 파일 복사 완료\n");
        close(fd1);
        close(fd2);
        return 0;
    }

    src = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd1, 0);
    if (src == MAP_FAILED) {
        perror("원본 mmap 실패");
        close(fd1);
        close(fd2);
        return 1;
    }

    dest = mmap(NULL, size, PROT_READ | PROT_WRITE,
                MAP_SHARED, fd2, 0);

    if (dest == MAP_FAILED) {
        perror("복사 파일 mmap 실패");
        munmap(src, size);
        close(fd1);
        close(fd2);
        return 1;
    }

    memcpy(dest, src, size);

    munmap(src, size);
    munmap(dest, size);

    close(fd1);
    close(fd2);

    printf("파일 복사 완료: %s -> %s\n", argv[1], argv[2]);

    return 0;
}

