#include <stdbool.h>
#include <stdint.h>

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>
#include <ti/sysbios/knl/Task.h>

#include <apps/led_controller/led_controller.h>

#include "Board.h"

void led_toggle(uint8_t led_pin){
	// LED values - 2=RED, 4=BLUE, 8=GREEN
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7, led_pin);
	System_printf("Моргаем светодиодом\n");
	System_flush();
}


void pisiaheartBeatIdle(UArg arg0, UArg arg1){
	Task_sleep((UInt)arg0);
	GPIO_toggle(Board_LED0);
	System_printf("бля моргай СИНИЙ СУКА \n");
	System_flush();
}
