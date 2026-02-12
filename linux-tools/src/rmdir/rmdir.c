#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <sys/stat.h> 
#include <dirent.h> 
#include "rmdir.h"

int deleteRecursive(const char* path)
{ 
    struct stat stbuf = {0}; 
    if (stat(path, &stbuf) != 0){
         perror("Error locating file"); return -1; }
    if (!S_ISDIR(stbuf.st_mode)){ 
        // remove the file

        if (unlink(path) != 0){
            perror("Error removing file");
            return -1;
        }

        return 0;
    } 
    else{
        DIR *dir = opendir(path);

        struct dirent *folder;

        while (folder = readdir(dir)){
            if (strcmp(folder->d_name, ".") == 0 || strcmp(folder->d_name, "..") == 0){
                continue;
            }

            char newPath[1024];
            snprintf(newPath, sizeof(newPath), "%s/%s", path, folder->d_name);
            if (deleteRecursive(newPath) != 0){
                closedir(dir);
                return -1;
            }
        }

        closedir(dir);

        if (rmdir(path) != 0){
            perror("Error removing directory"); 
            return -1; 
        } 
        
        return 0;
    }
}


void removedir(const char *dirname){
    if (deleteRecursive(dirname) == 0){
        printf("Successfully removed directory %s\n", dirname); 
    }
    else {
        fprintf(stderr, "Failed to remove directory %s\n", dirname);
    }

}

int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Usage: rmdir directory_name\n");
        return 1;
    }

removedir(argv[1]); return 0;
}
