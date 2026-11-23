
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
    int send_fd, recv_fd;
    char msg[256];
    fd_set readfds;

    if (argc != 2) {
        printf("사용법: %s 1 또는 2\n", argv[0]);
        return 1;
    }

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    if (strcmp(argv[1], "1") == 0) {
        send_fd = open("fifo1", O_RDWR);
        recv_fd = open("fifo2", O_RDWR);
    }
    else if (strcmp(argv[1], "2") == 0) {
        send_fd = open("fifo2", O_RDWR);
        recv_fd = open("fifo1", O_RDWR);
    }
    else {
        printf("1 또는 2를 입력하세요.\n");
        return 1;
    }

    if (send_fd < 0 || recv_fd < 0) {
        perror("FIFO 열기 실패");
        return 1;
    }

    printf("채팅 시작! 종료하려면 /quit 입력\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(recv_fd, &readfds);

        int maxfd = recv_fd > 0 ? recv_fd : 0;

        if (select(maxfd + 1, &readfds, NULL, NULL, NULL) < 0)
            break;

        if (FD_ISSET(0, &readfds)) {
            if (fgets(msg, sizeof(msg), stdin) == NULL)
                break;

            write(send_fd, msg, strlen(msg));

            if (strcmp(msg, "/quit\n") == 0)
                break;
        }

        if (FD_ISSET(recv_fd, &readfds)) {
            int n = read(recv_fd, msg, sizeof(msg) - 1);

            if (n > 0) {
                msg[n] = '\0';

                if (strcmp(msg, "/quit\n") == 0) {
                    printf("상대방이 채팅을 종료했습니다.\n");
                    break;
                }

                printf("상대방: %s", msg);
                fflush(stdout);
            }
        }
    }

    close(send_fd);
    close(recv_fd);

    return 0;
}

