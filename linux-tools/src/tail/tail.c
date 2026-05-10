#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define DEFAULT_LINES 10

int main(int argc, char *argv[]){
    if (argc != 2){
        perror("Usage: tail <filename> [number_of_bytes]");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1){
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    off_t pos = lseek(fd, 0, SEEK_END);
    int lines = 0;

    while (pos > 0 && lines <= DEFAULT_LINES){
        ssize_t toread = (pos >= BUFFER_SIZE) ? BUFFER_SIZE : pos;
        pos -= toread;
        lseek(fd, pos, SEEK_SET);

        ssize_t bytesRead = read(fd, buffer, toread);

        for (ssize_t i = bytesRead - 1; i >= 0; i--){
            if (buffer[i] == '\n'){
                lines++;
                if (lines > DEFAULT_LINES){
                    pos += i + 1; // move to the start of the last line
                    break;
                }
            }
        }
    }

    lseek(fd, pos, SEEK_SET);
    char output[BUFFER_SIZE*DEFAULT_LINES];
    ssize_t bytesRead = read(fd, output, BUFFER_SIZE - 1);
    output[bytesRead] = '\0';

    printf("%s", output);
    close(fd);

    return 0;
}