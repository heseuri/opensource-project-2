
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

void list_dir(char *path)
{
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    char fullpath[PATH_MAX];

    dp = opendir(path);

    if (dp == NULL) {
        perror(path);
        return;
    }

    printf("\n%s:\n", path);

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;

        printf("%s  ", entry->d_name);
    }
    printf("\n");

    rewinddir(dp);

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_name[0] == '.')
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s",
                 path, entry->d_name);

        if (lstat(fullpath, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode))
            list_dir(fullpath);
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        list_dir(".");
    else
        list_dir(argv[1]);

    return 0;
}

