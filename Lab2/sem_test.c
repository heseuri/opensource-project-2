
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

int main()
{
    int semid;
    pid_t pid;
    struct sembuf op;

    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    semctl(semid, 0, SETVAL, 0);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    if (pid == 0) {
        printf("자식 프로세스 대기 중...\n");
        fflush(stdout);

        op.sem_num = 0;
        op.sem_op = -1;
        op.sem_flg = 0;

        semop(semid, &op, 1);

        printf("자식 프로세스 작업 시작\n");
        return 0;
    }
    else {
        sleep(2);

        printf("부모 프로세스가 세마포어 해제\n");
        fflush(stdout);

        op.sem_num = 0;
        op.sem_op = 1;
        op.sem_flg = 0;

        semop(semid, &op, 1);

        wait(NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}

