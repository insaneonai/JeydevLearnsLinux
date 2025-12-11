#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "echo.h"
void echo(const char* message){
    write(1, message, strlen(message));
    write(1, "\n", 1);
}

int main(int argc, char* argv[]){
    if (argc < 2){
        const char* usage = "Usage: echo message1 [message2 ...]\n";
        write(1, usage, strlen(usage));
        return 1;
    }
    for (int i=1; i<argc; i++){
        echo(argv[i]);
    }
    return 0;
}