#include <stdio.h>
#include "led_static.h"

int main(void){
	int i;
	for(i=0;i<10;i++){
		led_on();
		sleep(1);
		led_off();
		sleep(1);
	}
	return 0;
}

