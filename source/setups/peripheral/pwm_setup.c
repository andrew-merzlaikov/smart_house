#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"

#include "pwm_setup.h"

void pwm_init_and_run(void){

	volatile uint32_t ui32PWMClock; 	//������� ��������� ���������� ���
	volatile uint32_t ui32Load; 		//���������� ������ ��������� ���������� ��� �� ������
	volatile uint32_t ui32DutyCycle;	//���������� ��������� ���

	//��� ������������ ���-���������� ������������ ������
	//���������� ��������� ���������� � ������������� ������� 1.
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

	//������������ ���������. ������������ ������ ��� PWM0
	//(��. ������������ �� ����������). ��� ������ ������� ���
	//������������ ���� ����� B.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	// �� ���� B (��� 6) ��������� ������ ������� ������ ������ PWM0
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_0);

	GPIOPinConfigure(GPIO_PB6_M0PWM0);

	//�� ���� B (��� 7) ��������� ������ �������� ������ ������ PWM0
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_1);

	GPIOPinConfigure(GPIO_PB7_M0PWM1);

	//�� ���� B (��� 4) ��������� ������ ��������� ������ ������ PWM0
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_2);

	GPIOPinConfigure(GPIO_PB4_M0PWM2);

//	ui32PWMClock = SysCtlClockGet();
	ui32PWMClock = CPU_CLOCK;

	ui32Load = ui32PWMClock / PWM_FREQUENCY;

	ui32DutyCycle = ui32Load/2;

	//��������� ��������� ��� ������� � ������� ���������� � �����
	//���������� �����. ����� ������������� - ���������, ����������
	//������������ ����������� ��� ��������� ���������.
	PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);

	PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN|
			PWM_GEN_MODE_GEN_SYNC_LOCAL);

	//��������� ������� ��� ��� ������� � ������� ����������
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load);

	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ui32Load);

	//��������� ��������� ���������� ��� 50%
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui32DutyCycle);

	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, ui32DutyCycle);

	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, ui32DutyCycle);

	//���������� ������ ������� � ���������� �� ����� ������.
	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);

	PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);

	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);

	//������ ������� � ������� ����������.
	PWMGenEnable(PWM1_BASE, PWM_GEN_0);

	PWMGenEnable(PWM1_BASE, PWM_GEN_1);

	//���������� ����� ���������.
	PWMSyncTimeBase(PWM1_BASE, PWM_GEN_0_BIT|PWM_GEN_1_BIT);
}
