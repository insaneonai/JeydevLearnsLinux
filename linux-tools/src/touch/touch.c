// Update the access and modification times of each FILE to the current time.
// Create FILE if it does not exist.  A FILE argument of `-' is handled

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <utime.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        perror("Usage: touch <file>", NULL);
        return EXIT_FAILURE;
    }

    struct stat st;

    if (stat(argv[1], &st) == -1){
        int fd = open(argv[1], O_CREAT | O_WRONLY, 0666);
        if (fd == -1){
            perror("open");
            return EXIT_FAILURE;
        }
    }

    if (utime(argv[1], NULL) == -1){
        perror("utime");
        return EXIT_FAILURE;
    }
}