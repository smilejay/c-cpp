#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const* argv[])
{
    FILE *stream;
    char buf[256];
    char cmd[32]="/usr/bin/uptime";
    stream = popen(cmd, "r" );
    //将刚刚FILE* stream的数据流读取到buf中
    fread(buf, sizeof(char), sizeof(buf), stream);
    printf("cmd: %s\n", cmd);
    printf("output: %s", buf);
    pclose(stream);
    return 0;
}
