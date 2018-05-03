/*
*   Description:
*   this example is about using ADC for monitoring the CPU
*   temperature sensor and using the NOKIA5110 graphics
*   LCD to display.
*
*   FreeRTOS is used together with TivaWare library for the
*   TM4C123 MCU from TI.
*
*        ******************************
*        * WIRING:                    *
*        * LAUCHPAD-NOKIA5110         *
*        *   PA7----RST               *
*        *   PA6----DC                *
*        *   PA5----DIN               *
*        *   PA3----CE                *
*        *   PA2----CLK               *
*        *   VCC----VCC               *
*        *   GND----GND               *
*        ******************************
         Sarea Al Hariri
         3-5-2018
         ******************************
***************************************

 */
#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_gpio.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"
#include "driverlib/timer.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/pwm.h"
#include "driverlib/ssi.h"
#include "driverlib/systick.h"
#include <string.h>
#include <tm4c123gh6pm.h>
#include <InitConsole.h>
#include <uartstdio.h>
#include <delay.h>
#include <FreeRtos_files/FreeRTOS.h>
#include <FreeRtos_files/task.h>
#include <FreeRtos_files/queue.h>
#include <AppTasks.h>
#include <PORTF_Init.h>
#include <Nokia5110.h>

#define GetTempPri          1
#define LCDWritePri         2
#define TempQlength         1

xQueueHandle TempQHandle ;
xTaskHandle GetTempHandle;
xTaskHandle LCDWriteHandle;

void ADC_Init(void);


int main(){
    Nokia5110_Init();
    Nokia5110_Clear();
    Nokia5110_OutString("Testing");
    Nokia5110_Clear();

	InitConsole() ;
	PORTF_Init() ;
	ADC_Init();

#ifdef LCD_USED
	LCD_init() ;
#endif

	Nokia5110_OutString("Testing");
	Nokia5110_Clear();


	TempQHandle = xQueueCreate(TempQlength, sizeof(uint32_t));
	xTaskCreate(&GetTemp, "Task 1",
	            configMINIMAL_STACK_SIZE, NULL,
	            GetTempPri, &GetTempHandle);
    xTaskCreate(&LCDWrite, "Task 2",
                configMINIMAL_STACK_SIZE, NULL,
                LCDWritePri, &LCDWriteHandle);



    vTaskStartScheduler() ;


}

/* The application Hook callback */
void vApplicationIdleHook( void ){
    GPIO_PORTF_DATA_R ^= 0x0e;
}


void ADC_Init(void) {

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0) ;
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) ;

    // adc0, sampleseq 3, processor triggering, higher priority
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0) ;

    // use temp sensor, enable int on adc level NOT to cpu, end sequence
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE|ADC_CTL_TS|ADC_CTL_END) ;

    // enable the sequencer
    ADCSequenceEnable(ADC0_BASE, 3) ;

    // clear int at the beginning
    ADCIntClear(ADC0_BASE, 3) ;
}
