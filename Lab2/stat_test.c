
#include <stdio.h>
#include <sys/stat.h>

int main()
{
    struct stat st;

    if (stat("test.txt", &st) == -1) {
        printf("파일 정보 확인 실패\n");
        return 1;
    }

    printf("파일 크기: %ld byte\n", (long)st.st_size);
    printf("파일 권한: %o\n", st.st_mode & 0777);
    printf("파일 inode 번호: %lu\n", (unsigned long)st.st_ino);

    return 0;
}

