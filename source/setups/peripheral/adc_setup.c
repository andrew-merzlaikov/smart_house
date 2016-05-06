#include <stdint.h>S
#include <stdbool.h>

#include "inc/hw_adc.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"

#include <setups/peripheral/pwm_setup.h>
//*****************************************************************************
//
// Инициализация и запуск АЦП.
//
//*****************************************************************************

void adc_init_and_run(void){
	// Тактирование выбранного модуля АЦП.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADCx);

	// Ожидание готовности выбранного модуля АЦП к настройке.
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADCx)) { }

	ADCHardwareOversampleConfigure(ADCx_BASE, 4);

	// Установка триггера выбранного буфера АЦП.
	ADCSequenceConfigure(ADCx_BASE, SSy, ADC_TRIGGER, 0);

	ADCSequenceStepConfigure(ADCx_BASE, SSy, 0, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADCx_BASE, SSy, 1, ADC_CTL_CH1|ADC_CTL_END);

	ADCIntClear(ADCx_BASE, SSy);

	IntEnable(INT_ADCxSSy);
	IntPrioritySet(INT_ADCxSSy, 1);

	ADCSequenceEnable(ADCx_BASE, SSy);
}
