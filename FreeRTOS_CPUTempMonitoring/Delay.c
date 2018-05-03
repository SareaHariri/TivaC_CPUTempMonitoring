
#include <Delay.h>


//Function to delay t microseconds

void Delay_Us(uint32_t t){
    SysCtlDelay(t*(SysCtlClockGet()/(3*1000000)));

}
//Function to delay t milliseconds
void Delay_ms(uint32_t t){

    SysCtlDelay(t*(SysCtlClockGet()/(3*1000)));

}
