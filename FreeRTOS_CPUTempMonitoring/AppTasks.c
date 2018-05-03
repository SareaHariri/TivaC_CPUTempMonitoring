/*
 * AppTasks.c
 *
 * Author: Sarea Al Hariri
 */
#include <AppTasks.h>
#include <FreeRtos_files/queue.h>

#ifdef LCD_USED
typedef char byte ;
#endif

extern xQueueHandle TempQHandle ;

void GetTemp(void* PtoVoid){
    uint32_t adcValue = 0 ;
    TickType_t TimeRef = xTaskGetTickCount() ;      /* get the reference point */
    const TickType_t GetTempDelay = 200u ;          /* 1 second */
    while(1){
           ADCProcessorTrigger(ADC0_BASE, 3) ;
           while(!ADCIntStatus(ADC0_BASE, 3, false)) ;
           ADCSequenceDataGet(ADC0_BASE, 3, &adcValue) ;
           adcValue = (uint32_t)(147.5 - ((75.0*3.3 *(float)adcValue)) / 4096.0);
           xQueueSend(TempQHandle,(void*)&adcValue, 1000 ) ;

           vTaskDelayUntil(&TimeRef, GetTempDelay) ;

       }
}

void LCDWrite(void* PtoVoid){
    uint32_t TempValue = 0;
    xQueueReceive(TempQHandle, (void*)&TempValue, portMAX_DELAY);
    TickType_t TimeRef = xTaskGetTickCount() ;        /* get the reference point */
    const TickType_t LCDWriteDelay = 200u ;           /* 1 second */

#ifdef LCD_USED
    uint8_t i = 0u ;
    byte Data[3];
#endif

    while(1){
        xQueueReceive(TempQHandle, (void*)&TempValue, portMAX_DELAY);
        UARTprintf("temperature: %d \n\n", TempValue) ;
        Nokia5110_Clear();
        Nokia5110_OutString("TEMP =");
        Nokia5110_OutUDec(TempValue);

#ifdef LCD_USED
        itoa(TempValue, Data, 10);
        while(i < 3){
        LCD_data(Data[i++]);
        }
#endif

        vTaskDelayUntil(&TimeRef, LCDWriteDelay) ;
    }
}

/* Implementation of itoa() */
static char* itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if ((num < 0) && (base == 10))
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

static void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap((str+start), (str+end));
        start++;
        end--;
    }
}

static void swap(char *s1, char *s2){
    char temp ;
    temp = *s1 ;
    *s1 = *s2 ;
    *s2 = temp ;
}
