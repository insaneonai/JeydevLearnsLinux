#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    if (argc != 2){
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat st;

    if (stat(argv[1], &st) == -1){
        perror("stat");
        return EXIT_FAILURE;
    }

    printf("File: %s\n", argv[1]);
    printf("Size: %lld      Blocks: %lld      IO Block: %ld\n", (long long) st.st_size, (long long) st.st_blocks, st.st_blksize);
    printf("Device: %lxh/%ldd    Inode: %ld\n", st.st_dev, st.st_dev, st.st_ino);
    printf("Access: %o\n", st.st_mode & 0777);

    return 0;
}