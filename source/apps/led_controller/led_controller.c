#include <stdbool.h>
#include <stdint.h>

#include <xdc/runtime/System.h>

#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>
#include <ti/sysbios/knl/Task.h>

#include <apps/led_controller/led_controller.h>


void ledToggle(void){
	while(1){
		// LED values - 2=RED, 4=BLUE, 8=GREEN
		if(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_4)){
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_6);
			System_printf("бля моргай ЖЕЛТЫЙ \n");
		} else if(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_6)){
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_7);
			System_printf("бля моргай КРАСНЫЙ \n");
		} else {
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_4);
			System_printf("бля моргай ЗЕЛЕНЫЙ \n");
		}
		System_flush();
		// create a delay of ~1/2sec
		Task_sleep(1001);
	}
}

void delay(void){
	 SysCtlDelay(6700000);		// creates ~500ms delay - TivaWare fxn
}
