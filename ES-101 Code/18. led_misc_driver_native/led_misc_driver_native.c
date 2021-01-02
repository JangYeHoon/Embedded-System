#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
 int dev, i;
 char buf[4]={0,0,0,0};
 dev = open("/dev/led_misc_driver", O_RDWR);
 if(dev<0){
  printf("driver open failed!\n");
  return -1;
 }
 for(i=0;i<4;i++){
  buf[i]=1;
  write(dev,&buf, 4);
  sleep(1);
 }
 close(dev);
 return 0;
}
