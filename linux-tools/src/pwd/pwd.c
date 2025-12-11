#include<stdio.h>
#include<unistd.h>
#include "pwd.h"
void print_working_directory(){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        write(1, cwd, strlen(cwd));
        write(1, "\n", 1);
    }
    else{
        perror("getcwd() error");
    }
}

int main(){
    print_working_directory();
    return 0;
}