
#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
    char *sentence[] = {
        "Hello Linux",
        "I am studying C programming",
        "Linux is an open source operating system",
        "Practice makes perfect",
        "Welcome to the Linux world"
    };

    char input[200];
    int wrong = 0;
    int total = 0;
    int i, j;
    int len1, len2;
    double sec, cpm;
    time_t start, end;

    printf("===== 타자 연습 프로그램 =====\n");
    printf("다음 문장을 그대로 입력하세요.\n\n");

    time(&start);

    for (i = 0; i < 5; i++) {
        printf("%d번: %s\n", i + 1, sentence[i]);
        printf("입력: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            return 1;

        input[strcspn(input, "\n")] = '\0';

        len1 = strlen(sentence[i]);
        len2 = strlen(input);

        // 입력한 문자열과 원본 문자열 비교
        for (j = 0; j < len1 && j < len2; j++) {
            if (sentence[i][j] != input[j])
                wrong++;
        }

        // 글자 수가 다른 경우도 오타로 계산
        if (len1 > len2)
            wrong += len1 - len2;
        else
            wrong += len2 - len1;

        total += len2;
        printf("\n");
    }

    time(&end);

    sec = difftime(end, start);

    if (sec == 0)
        sec = 1;

    cpm = total * 60.0 / sec;

    printf("===== 연습 결과 =====\n");
    printf("총 입력 글자 수: %d\n", total);
    printf("오타 횟수: %d\n", wrong);
    printf("소요 시간: %.0f초\n", sec);
    printf("평균 분당 타자수: %.2f타\n", cpm);

    return 0;
}

