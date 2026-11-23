
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

int main()
{
    DIR *dp;
    struct dirent *entry;

    mkdir("mydir", 0755);

    dp = opendir(".");

    if (dp == NULL) {
        printf("디렉토리 열기 실패\n");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);

    return 0;
}

