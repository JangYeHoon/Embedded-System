#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
 int dev, i;
 char buf[4];
 dev = open("/dev/switch_driver", O_RDWR);
 if(dev<0){
  printf("driver open failed!\n");
  return -1;
 }

 for(i=0;i<20;i++){
  read(dev,&buf, 4);
  printf("sw1:%d, sw2:%d, sw3:%d, sw4:%d\n", buf[0], buf[1], buf[2], buf[3]);
  sleep(1);
 }
 close(dev);
 return 0;
}
