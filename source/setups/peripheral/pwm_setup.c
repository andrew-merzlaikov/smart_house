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

	volatile uint32_t ui32PWMClock; 	//Частота тактового генератора ШИМ
	volatile uint32_t ui32Load; 		//Количестов тактов тактового генератора ШИМ за период
	volatile uint32_t ui32DutyCycle;	//Скважность импульсов ШИМ

	//Для тактирования ШИМ-генератора используется сигнал
	//системного тактового генератора с коэффициентом деления 1.
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

	//Тактирование периферии. Используется модуль ШИМ PWM0
	//(см. документацию на контроллер). Для вывода сигнала ШИМ
	//используются пины порта B.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	// На порт B (пин 6) выводится сигнал первого канала модуля PWM0
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_0);

	GPIOPinConfigure(GPIO_PB6_M0PWM0);

	//На порт B (пин 7) выводится сигнал третьего канала модуля PWM0
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_1);

	GPIOPinConfigure(GPIO_PB7_M0PWM1);

	//На порт B (пин 4) выводится сигнал четвёртого канала модуля PWM0
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_2);

	GPIOPinConfigure(GPIO_PB4_M0PWM2);

//	ui32PWMClock = SysCtlClockGet();
	ui32PWMClock = CPU_CLOCK;

	ui32Load = ui32PWMClock / PWM_FREQUENCY;

	ui32DutyCycle = ui32Load/2;

	//Установка счетчиков ШИМ первого и второго генератора в режим
	//убывающего счёта. Режим синхронизации - локальный, обновление
	//компараторов выполняется при обнулении счетчиков.
	PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);

	PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN|
			PWM_GEN_MODE_GEN_SYNC_LOCAL);

	//Установка периода ШИМ для первого и второго генератора
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load);

	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ui32Load);

	//Установка начальной скважности ШИМ 50%
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui32DutyCycle);

	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, ui32DutyCycle);

	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, ui32DutyCycle);

	//Разрешение вывода сигнала с генератора на линии портов.
	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);

	PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);

	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);

	//Запуск первого и второго генератора.
	PWMGenEnable(PWM1_BASE, PWM_GEN_0);

	PWMGenEnable(PWM1_BASE, PWM_GEN_1);

	//Синхронный сброс счётчиков.
	PWMSyncTimeBase(PWM1_BASE, PWM_GEN_0_BIT|PWM_GEN_1_BIT);
}
