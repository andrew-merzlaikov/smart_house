#include <stdint.h>
#include <stdbool.h>

#include <xdc/runtime/System.h>
#include "driverlib/adc.h"

#include <setups/base_setup.h>
#include <apps/led_controller/led_controller.h>

#define INDEX_BUFFER 2


uint8_t _get_led_pin_by_environment_data(void){
	return GREEN_PIN;
}

void readEnvironmentDataSWI(void){
	uint32_t pui32Buffer[INDEX_BUFFER];
	uint32_t count_sample;

	count_sample = ADCSequenceDataGet(ADCx_BASE, SSy, pui32Buffer);
	append_environment_data(pui32Buffer[0], pui32Buffer[1]);

	System_printf("Данные температуры %d \n", pui32Buffer[0]);
	System_printf("Данные света %d \n", pui32Buffer[1]);
	System_flush();

	led_toggle(_get_led_pin_by_environment_data());

	ADCProcessorTrigger(ADCx_BASE, SSy);
}

void ADC_ISR(void){
	System_printf("Хардваре приывание \n");
	System_flush();
	ADCIntClear(ADCx_BASE, SSy);
	Swi_post("readEnvironmentData");
}



