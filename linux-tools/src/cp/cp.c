#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cp.h"

int isDirectory(const char* src){
    struct stat stbuf = {0};

    if (stat(src, &stbuf) != 0){
        return 0;
    }

    return S_ISDIR(stbuf.st_mode);
}

void copyFile(const char* src, const char* dst){
    // check if dst is directory
    if (!isDirectory(dst)){
        int dstfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC);
        int srcfd = open(src, O_RDONLY);

        if (srcfd == -1 ){
            perror("open source file");
            return;
        }

        if (dstfd == -1 ){
            perror("open dst file");
            return;
        }

        char buffer[1024];

        ssize_t bytesread;

        while ((bytesread = read(srcfd, buffer, sizeof(buffer))) > 0){
            if (write(dstfd, buffer, bytesread) != bytesread) {
                perror("write");
                break;
            }
        }

        close(srcfd);
        close(dstfd);
    }
}

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("Usage cp file1 [file2...] dest\n");
        return 1;
    }

    char* destination = argv[argc - 1];

    copyFile(argv[1], destination);

}