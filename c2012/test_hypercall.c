#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <sys/ioctl.h>  
#include <linux/types.h>
#include <fcntl.h>  
#include <string.h>
#include <xenctrl.h>
#include <xen/sys/privcmd.h>

int main(int argc, char *argv[])  
{  
	int fd, ret;
	char * message;
	if (argc != 2) {
		printf("please input one parameter!\n");
		return -1;
	}
	message = (char *) malloc(sizeof(char) * (strlen(argv[1])+1));
	strcpy(message, argv[1]);
	privcmd_hypercall_t my_hypercall = {
		__HYPERVISOR_hello_hypercall,
		{(__u64)message, 0, 0, 0, 0}
	};
	fd = open("/proc/xen/privcmd", O_RDWR);
	if (fd < 0) {
		perror("can't open /proc/xen/privcmd");
		exit(1);
	} 
	else
		printf("privcmd's fd = %d\n", fd);
	ret = ioctl(fd, IOCTL_PRIVCMD_HYPERCALL, &my_hypercall);
	printf("ret = %d\n", ret);  
}
