#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{
    int fd, len;
    char *buf;
    if (argc < 2) {
        printf("Please use an existing file as the argument.\n");
        return 1;
    }
    if ((fd = open(argv[1], O_RDWR)) < 0) {
        char temp_buf[30];
        sprintf(temp_buf, "Failed to open file: %s\n", argv[1]);
        perror(temp_buf);
        return -1;
    }
    len = lseek(fd, 0, SEEK_END);
    buf = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED) {
        perror("mmap error.\n");
        close(fd);
        return -1;
    }
    close(fd);
    printf("length of %s is %ld\n", argv[1], strlen(buf));
    printf("content of %s is:\n%s\n", argv[1], buf);
    buf[0] = 'A';
    printf("content of %s is:\n%s\n", argv[1], buf);
    memset(buf, 0, strlen(buf));
    sprintf(buf, "The new text.");
    printf("content of %s is:\n%s\n", argv[1], buf);
    munmap(buf, len);
    return 0;
}
