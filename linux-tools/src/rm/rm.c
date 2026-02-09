#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "rm.h"

void removeFile(const char *filename){
    // Try opening the file to check if it exists
    int fd = open(filename, O_RDWR);

    if (fd == -1){
        perror("Error locating file");
        return;
    }

    // Truncate the file to zero bytes to prevent data recovery
    if (ftruncate(fd, 0) == -1){
        perror("Error performing clean removal");
        close(fd);
        return;
    }

    // Close the file descriptor before unlinking
    close(fd);

    // Unlink the file to remove it from the filesystem

    if (remove(filename) == 0){
        printf("Successfully removed file %s\n", filename);
    }
    else{
        perror("Error removing file");
    }

}


int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Usage rm file\n");
        return 1;
    }

    // Check if the given is a directory and print an error message if it is
    struct stat stbuf = {0};

    if (stat(argv[1], &stbuf) != 0){
        perror("Error locating file");
        return 1;
    }

    if (S_ISDIR(stbuf.st_mode)){
        fprintf(stderr, "Error: %s is a directory\n", argv[1]);
        return 1;
    }

    // We should do a clean removal of the file here, but for now we will just print the filename
    // remove calls -> unlink but no true deletion.
    // Overwrite the file or truncate it to zero bytes before unlinking to prevent data recovery.

    printf("Removing file: %s\n", argv[1]);

    removeFile(argv[1]);

    return 0;
}