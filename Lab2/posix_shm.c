
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    int fd;
    char *ptr;
    pid_t pid;

    fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);

    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    if (ftruncate(fd, 100) == -1) {
        perror("ftruncate");
        close(fd);
        shm_unlink("/myshm");
        return 1;
    }

    ptr = mmap(NULL, 100, PROT_READ | PROT_WRITE,
               MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        shm_unlink("/myshm");
        return 1;
    }

    strcpy(ptr, "Hello POSIX Shared Memory");

    pid = fork();

    if (pid < 0) {
        perror("fork");
    }
    else if (pid == 0) {
        printf("자식이 읽은 내용: %s\n", ptr);
        munmap(ptr, 100);
        close(fd);
        return 0;
    }
    else {
        wait(NULL);
    }

    munmap(ptr, 100);
    close(fd);
    shm_unlink("/myshm");

    return 0;
}

