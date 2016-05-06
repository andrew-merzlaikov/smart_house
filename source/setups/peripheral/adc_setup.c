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
// ������������� � ������ ���.
//
//*****************************************************************************

void adc_init_and_run(void){
	// ������������ ���������� ������ ���.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADCx);

	// �������� ���������� ���������� ������ ��� � ���������.
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADCx)) { }

	ADCHardwareOversampleConfigure(ADCx_BASE, 4);

	// ��������� �������� ���������� ������ ���.
	ADCSequenceConfigure(ADCx_BASE, SSy, ADC_TRIGGER, 0);

	ADCSequenceStepConfigure(ADCx_BASE, SSy, 0, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADCx_BASE, SSy, 1, ADC_CTL_CH1|ADC_CTL_END);

	ADCIntClear(ADCx_BASE, SSy);

	IntEnable(INT_ADCxSSy);
	IntPrioritySet(INT_ADCxSSy, 1);

	ADCSequenceEnable(ADCx_BASE, SSy);
}
