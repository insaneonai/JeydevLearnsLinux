#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define DEFAULT_LINES 10

int main(int argc, char *argv[]){
    if (argc != 2){
        perror("Usage: head <filename> [number_of_bytes]");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1){
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];

    // read first DEFAULT_LINES lines
    ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE - 1);

    if (bytesRead == -1){
        perror("Error reading file");
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0';
    // print only the first DEFAULT_LINES lines
    int lines = 0;
    for (ssize_t i = 0; i < bytesRead; i++){
        if (buffer[i] == '\n'){
            lines++;
            if (lines == DEFAULT_LINES){
                buffer[i + 1] = '\0'; // terminate the string after the last line
                break;
            }
        }
    }
    printf("%s", buffer);
    close(fd);
    return 0;
}