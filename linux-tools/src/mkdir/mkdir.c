#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "mkdir.h"

void makedir(const char *dirname, mode_t mode) {
    if (mkdir(dirname, mode) == -1) {
        perror("Error creating directory");
    } else {
        printf("Directory %s created successfully\n", dirname);
    }
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr, "Usage: mkdir directory_name [-m mode]\n");
        return 1;
    }

    // Get the mode from the command line arguments, default to 0755 if not provided after -m
    mode_t mode = 0755; // Default permissions
    if (argc >=4 && strcmp(argv[2], "-m") == 0){
        mode = strtoul(argv[3], NULL, 8);
    }

    mkdir(argv[1], mode);
}