#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "cat.h"

void print_file(const char* filename){
    int file;
    char ch;
    file = open(filename, O_RDONLY);
    if (file == -1){
        perror("Error opening file");
        return;
    }
    while (read(file, &ch, 1) > 0){
        write(1, &ch, 1);
    }
    write(1, "\n", 1);
    close(file);
}

void write_file(const char* filename){
    int file;
    char* buffer[256];
    file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1){
        perror("Error opening file for writing");
        return;
    }
    write(1, "Enter text to write to file (Ctrl+D to end):\n", 44);
    ssize_t bytesRead;
    while ((bytesRead = read(0, buffer, sizeof(buffer))) > 0){
        write(file, buffer, bytesRead);
    }
    close(file);
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage %s file1 [fil2...]\n", argv[0]);
        return 1;
    }

    for (int i=1; i<argc; i++){
        if (strcmp(argv[i], "-w") == 0 && i + 1 < argc){
            write_file(argv[++i]);
            continue;
        }
        printf("\n--- File: %s ---\n", argv[i]);
        print_file(argv[i]);
        printf("\n\n");
    }
}