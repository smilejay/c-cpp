/*  socket_qemu_monitor_clinet.c
 *  Connect to remote QEMU monitor socket and sending a command to the monitor.
 *  author: Jay <smile665@gmail.com>
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char *cmd = "info kvm\n";
	char output[200];

	/*  Create a socket for the client.  */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("10.1.77.82");
	address.sin_port = htons(4444);
	len = sizeof(address);

	/*  Now connect our socket to the server's socket.  */
	result = connect(sockfd, (struct sockaddr *)&address, len);

	if(result == -1) {
		perror("oops: socket connetion failed.");
		exit(1);
	}

	/*  We can now read/write via sockfd.  */
	printf("sending command '%s' to remote qemu monitor\n", cmd);
	write(sockfd, cmd, strlen(cmd));
	read(sockfd, output, sizeof(output));
	printf("output from qemu monitor: %s\n", output);
	read(sockfd, output, sizeof(output));
	printf("output from qemu monitor: %s\n", output);
	close(sockfd);
	exit(0);
}
