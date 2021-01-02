#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
	int dev;
	int ret=0,data=0;

	dev = open("/dev/touch", O_WRONLY);

	while(1){
		sleep(1);
		data = ioctl(dev,0,NULL);
		if(data == 0x01)
			printf("Touch 1 pushed!\n");
		else if(data == 0x02)
			printf("Touch 2 pushed!\n");
	}

	close(dev);

	return 0;
}
