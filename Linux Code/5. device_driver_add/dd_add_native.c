#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <time.h>

#define CALC_BASE 0x06
#define ADD _IO(CALC_BASE, 0x01)

int main(void)
{
	int dev;
	int buf[2];
	int result = 0;
	dev = open("/dev/dd_add", O_RDWR);
	if(dev<0){
		printf("driver open failed!\n");
		return -1;
	}
	srand(time(NULL));
	for (int i = 0; i < 2; i++)
		buf[i] = rand() % 10;
	printf("user write buf : %d, %d\n", buf[0], buf[1]);
	write(dev,&buf,8);
	ioctl(dev,ADD,NULL);
	read(dev,&result,4);
	printf("user result : %d\n", result);
	
	close(dev);
	return 0;
}
