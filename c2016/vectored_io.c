/* Each word is saved into a single buffer and with only one call to writev(),
 * all buffers are printed to the standard output.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define NUMBUFS 3

int main(int argc, char const* argv[])
{
    const char *buf1 = "Hello ";
    const char *buf2 = "Wikipedia ";
    const char *buf3 = "Community!\n";
    struct iovec bufs[NUMBUFS];

    bufs[0].iov_base = (void *) buf1;
    bufs[0].iov_len = strlen(buf1);

    bufs[1].iov_base = (void *) buf2;
    bufs[1].iov_len = strlen(buf2);

    bufs[2].iov_base = (void *) buf3;
    bufs[2].iov_len = strlen(buf3);

    if (-1 == writev(STDOUT_FILENO, bufs, NUMBUFS)) {
         perror("writev() Failed.");
         exit(EXIT_FAILURE);
    }

    return 0;
}
