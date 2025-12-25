#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

void readDirectory(const char *dirname) {
    DIR *dir;
    struct dirent *dp;
    struct stat st;
    char path[1024];

    dir = opendir(dirname);
    if (!dir) {
        perror(dirname);
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        if (dp->d_name[0] == '.')
            continue;

        snprintf(path, sizeof(path), "%s/%s", dirname, dp->d_name);

        if (stat(path, &st) == -1) {
            perror(path);
            continue;
        }

        char type = S_ISDIR(st.st_mode) ? 'd' : '-';

        printf("%c%o %ld %ld %s\n",
               type,
               st.st_mode & 0777,
               st.st_nlink,
               st.st_size,
               dp->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        readDirectory(".");
    } else {
        readDirectory(argv[1]);
    }
    return 0;
}
