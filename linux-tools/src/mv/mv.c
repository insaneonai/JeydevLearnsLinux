#include <stdio.h>
#include "mv.h"

void moveFile(const char* source, const char* destination){
    if (rename(source, destination) == 0){
        printf("Successfully moved file %s to %s", source, destination);
    }
    else{
        printf("Error moving file");
    }
}


int main(int argc, char* argv[]){
    if (argc != 3){
        fprintf(stderr, "Usage mv file1 file2\n");
        return 1;
    }

    moveFile(argv[1], argv[2]);
}

