
#include <stdio.h>
#include <unistd.h>

int main()
{
    // 파일 존재 여부 확인
    if (access("test.txt", F_OK) == 0)
        printf("파일이 존재합니다.\n");
    else
        printf("파일이 존재하지 않습니다.\n");

    // 읽기 권한 확인
    if (access("test.txt", R_OK) == 0)
        printf("읽기 가능합니다.\n");
    else
        printf("읽기 불가능합니다.\n");

    // 쓰기 권한 확인
    if (access("test.txt", W_OK) == 0)
        printf("쓰기 가능합니다.\n");
    else
        printf("쓰기 불가능합니다.\n");

    // 실행 권한 확인
    if (access("test.txt", X_OK) == 0)
        printf("실행 가능합니다.\n");
    else
        printf("실행 불가능합니다.\n");

    return 0;
}

