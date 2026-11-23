
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(int argc, char *argv[])
{
    mqd_t send_q, recv_q;
    struct mq_attr attr = {0};
    char msg[256];
    char *send_name, *recv_name;
    pid_t pid;

    if (argc != 2) {
        printf("사용법: %s 1 또는 2\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        send_name = "/chat1";
        recv_name = "/chat2";
    }
    else if (strcmp(argv[1], "2") == 0) {
        send_name = "/chat2";
        recv_name = "/chat1";
    }
    else {
        printf("1 또는 2를 입력하세요.\n");
        return 1;
    }

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(msg);

    send_q = mq_open(send_name, O_CREAT | O_WRONLY, 0600, &attr);
    recv_q = mq_open(recv_name, O_CREAT | O_RDONLY, 0600, &attr);

    if (send_q == (mqd_t)-1 || recv_q == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        while (1) {
            ssize_t n = mq_receive(recv_q, msg, sizeof(msg), NULL);

            if (n < 0)
                break;

            msg[n < sizeof(msg) ? n : sizeof(msg) - 1] = '\0';

            if (strcmp(msg, "/quit\n") == 0) {
                printf("\n상대방이 채팅을 종료했습니다.\n");
                fflush(stdout);
                kill(getppid(), SIGTERM);
                break;
            }

            printf("\n상대방: %s", msg);
            fflush(stdout);
        }

        mq_close(send_q);
        mq_close(recv_q);
        return 0;
    }

    printf("채팅 시작! 종료하려면 /quit 입력\n");

    while (fgets(msg, sizeof(msg), stdin) != NULL) {
        if (mq_send(send_q, msg, strlen(msg) + 1, 0) == -1) {
            perror("mq_send");
            break;
        }

        if (strcmp(msg, "/quit\n") == 0)
            break;
    }

    kill(pid, SIGTERM);
    waitpid(pid, NULL, 0);

    mq_close(send_q);
    mq_close(recv_q);

    return 0;
}

