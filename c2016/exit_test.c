#include <stdio.h>
#include <stdlib.h>

void bye1(void)
{
    printf("bye1:...\n");
}

void bye2(const char *name)
{
    printf("bye2: %s\n", name);
}

void bye3(const char *name)
{
    printf("bye3: %s\n", name);
}

int main(int argc, char const* argv[])
{
    atexit(bye1);
    on_exit(bye2, "Jay");
    on_exit(bye3, "Jack");
    printf("output1: hello\n");
    exit(EXIT_SUCCESS);
    return 0;
}
