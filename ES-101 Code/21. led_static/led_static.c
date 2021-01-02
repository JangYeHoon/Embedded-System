#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "led_static.h"

int dev=0;

void led_on(void){
	int buf[4]={1,1,1,1};
	dev = open("/dev/led_misc_driver",O_RDWR);
	if(dev<0){
		printf("driver open failed\n");
	}else{
		write(dev,&buf,4);
	}
}

void led_off(void){
	int buf[4]={0,0,0,0};
	write(dev,&buf,4);
	close(dev);
}


