
#include <stdio.h>
#include <sys/stat.h>

int main()
{
    struct stat st;

    // 심볼릭 링크 자체의 정보 확인
    if (lstat("link.txt", &st) == -1) {
        printf("파일 정보 확인 실패\n");
        return 1;
    }

    printf("파일 크기: %ld byte\n", (long)st.st_size);
    printf("inode 번호: %lu\n", (unsigned long)st.st_ino);

    // 파일이 심볼릭 링크인지 확인
    if (S_ISLNK(st.st_mode)) {
        printf("심볼릭 링크 파일입니다.\n");
    }
    else {
        printf("일반 파일입니다.\n");
    }

    return 0;
}

