#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <string.h>

#define CALC_BASE 0x06
#define CNT _IO(CALC_BASE, 0x01)

int main(void)
{
	int dev;
	char buf[20];
	int result;
	dev = open("/dev/dd_char", O_RDWR);
	if(dev<0){
		printf("driver open failed!\n");
		return -1;
	}
	printf("Enter : ");
	scanf("%s", buf);
	write(dev,&buf,strlen(buf));
	ioctl(dev,CNT,NULL);
	read(dev,&result,4);
	printf("user result : %d\n", result);
	
	close(dev);
	return 0;
}
