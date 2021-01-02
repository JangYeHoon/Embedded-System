#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define LED_BASE 0x56
#define ALL_LED_ON _IO(LED_BASE, 0x31)
#define ALL_LED_OFF _IO(LED_BASE,0x32)
#define LED_1_ON _IO(LED_BASE,0x33)
#define LED_1_OFF _IO(LED_BASE,0x34)
#define LED_2_ON _IO(LED_BASE,0x35)
#define LED_2_OFF _IO(LED_BASE,0x36)
#define LED_3_ON _IO(LED_BASE,0x37)
#define LED_3_OFF _IO(LED_BASE,0x38)
#define LED_4_ON _IO(LED_BASE,0x39)
#define LED_4_OFF _IO(LED_BASE,0x3a)

int main(void){
 int dev;
 dev = open("/dev/led_misc_driver_2", O_RDWR);
 if(dev<0){
  printf("driver open failed!\n");
  return -1;
 }

 ioctl(dev,ALL_LED_ON, NULL);
 sleep(1);
 ioctl(dev,ALL_LED_OFF,NULL);
 sleep(1);
 ioctl(dev,LED_1_ON, NULL);
 sleep(1);
 ioctl(dev,LED_1_OFF,NULL);
 sleep(1);
 ioctl(dev,LED_2_ON,NULL);
 sleep(1);
 ioctl(dev,LED_2_OFF,NULL);
 sleep(1);
 ioctl(dev,LED_3_ON,NULL);
 sleep(1);
 ioctl(dev,LED_3_OFF,NULL);
 sleep(1);
 ioctl(dev,LED_4_ON,NULL);
 sleep(1);
 ioctl(dev,LED_4_OFF,NULL);
 sleep(1);
 close(dev);
 return 0;
}
