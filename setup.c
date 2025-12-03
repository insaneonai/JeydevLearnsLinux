#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int create_directory_if_not_exists(const char* dirName){
    struct stat st = {0};

    if (stat(dirName, &st) == -1){
        // folder doesn;t exist
        return mkdir(dirName, 0700);
    }

    return -1;
}

char * concat(const char *a , const char * b){
    int len = strlen(a) + strlen(b) + 1;
    char * result = malloc(len);
    if (!result) return NULL;

    strcpy(result, a);
    strcat(result, b);

    return result;
}

int main(){
    printf("Please enter your file Name: ");
    char rootDir[256];
    scanf("%255s", rootDir);
    char * path;
    struct stat st = {0};

    if (stat(rootDir, &st) == -1){
        // Directory does not exist, attempt to create it
        if (mkdir(rootDir, 0700) == -1) {
            perror("Failed to create root directory");
            return -1;  // If creation fails, exit
        }
    }

    path = concat(rootDir, "/src");
    if (create_directory_if_not_exists(path) == -1){
        printf("Error structuring ur learning\n.");
        return -1;
    };
    free(path);

    path = concat(rootDir, "/src/util");
    if (create_directory_if_not_exists(path) == -1){
        printf("Error structuring ur learning.");
    };
    free(path);

    path = concat(rootDir, "/src/shared");
    if (create_directory_if_not_exists(path) == -1){
        printf("Error structuring ur learning.");
    };
    free(path);


    path = concat(rootDir, "/bin");
    if (create_directory_if_not_exists(path) == -1){
        printf("Error structuring ur learning.");
    };
    free(path);

    path = concat(rootDir, "/tests");
    if (create_directory_if_not_exists(path) == -1){
        printf("Error structuring ur learning.");
    };
    free(path);

    FILE * fp;
    path = concat(rootDir, "/README.MD");

    fp = fopen(path, "w");

    if (fp == NULL){
        printf("Unable to create README.md file.");
        return 1;
    }

    fclose(fp);

    return 0;
}