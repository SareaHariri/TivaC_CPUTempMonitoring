/*
 * PORTF_Init.h
 *
 *  Created on: 3 dec 2017
 *  Sarea Al Hariri
 */

#include <tm4c123gh6pm.h>

#ifndef PORTF_INIT_H_
#define PORTF_INIT_H_

// this function doesn't enable the interrupt on the port f
void PORTF_Init(void){
    // Port f configurations
        int dummy ;
        SYSCTL_RCGCGPIO_R |= 0x020 ;
        dummy = SYSCTL_RCGC2_R ;
        GPIO_PORTF_LOCK_R = 0x4c4f434b ;
        GPIO_PORTF_CR_R = 0x01f ;
        GPIO_PORTF_DIR_R = 0xe  ;
        GPIO_PORTF_DIR_R &= ~0x11 ;
        GPIO_PORTF_PUR_R |= 0x11 ;
        GPIO_PORTF_DEN_R |= 0x1f ;

}

// Port f configurations with interrupts
void PORTFINT_Init (void){
    int dummy ;
    SYSCTL_RCGC2_R |= 0x020 ;
    dummy = SYSCTL_RCGC2_R ;
    GPIO_PORTF_LOCK_R = 0x4c4f434b ;
    GPIO_PORTF_CR_R = 0x01f ;
    GPIO_PORTF_DIR_R = 0xe  ;
    GPIO_PORTF_DIR_R &= ~0x11 ;
    GPIO_PORTF_PUR_R |= 0x11 ;
    GPIO_PORTF_DEN_R |= 0x1f ;

    // setting for interruption in the module
    GPIO_PORTF_IS_R = 0x00 ;     // edge sensitive
    GPIO_PORTF_IBE_R = 0x00 ;      // not both edges
    GPIO_PORTF_IEV_R = 0x00 ;      // falling edge interrupt
    GPIO_PORTF_ICR_R = 0x11 ;   // clear the flags at the beginning
    GPIO_PORTF_IM_R = 0x11 ; // unmask bit 4 and 1


    // priority setting
    //For those interrupts with IRQ numbers greater and or equal to 0,
    //we can find its enable register by dividing n by 32. Let a = n/32 (integer divide).
    //The enable register number will be a. We can find the bit field for that IRQ by looking the remainder,
    //b = n%32, where b = 0, 1, ... or 31. The one bit will be used to enable the interrupt.

    // priority register number = IRQ/4
    // to calculate the bits needed .. n = IRQ%4 .. the bits used is n*8 + 7 and the previous two bits
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xff0fffff)   ;      // priority is 7 means 111
    NVIC_PRI7_R |= (5<<21) ;


    // setting for interruption in the NVIC
    NVIC_EN0_R = 0x40000000 ; // enable bit 30 for IRQ 30 port f
}


#endif /* PORTF_INIT_H_ */
