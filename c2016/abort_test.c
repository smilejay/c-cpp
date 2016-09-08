#include <stdio.h>
#include <stdlib.h>

/* The abort() function causes abnormal program termination to occur,
 * unless the signal SIGABRT is being caught and the signal handler does
 * not return.
 *
 * The abort() function never returns.
 */

int main(int argc, char const* argv[])
{
    printf("output1: hello\n");
    abort();
    printf("output2: never see this line\n");
    return 0;
}
