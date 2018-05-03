#include <LCD_files/LCD.h>

//This Function is used to send commands to the LCD
void LCD_command(uint8_t command)
{
    GPIO_PORTA_DATA_R = 0;      /* 0x20 = 0, R/W = 0 */
    GPIO_PORTB_DATA_R = (command & 0xff);
    GPIO_PORTA_DATA_R = EN ;    /* pulse E */
    Delay_Us(1);   			    /* Enable pulse Width */
    GPIO_PORTA_DATA_R = 0;
    if (command < 4)
        Delay_ms(2);         /* command 1 and 2 needs up to 1.64ms */
    else
        Delay_Us(40);        /* all others 40 us */
}



void LCD_data(uint8_t data)
{
    GPIO_PORTA_DATA_R = RS ;        /* RS = 1, R/W = 0 */
    GPIO_PORTB_DATA_R = data;
    GPIO_PORTA_DATA_R = EN | RS ;   /* pulse E */
    Delay_Us(1);
    GPIO_PORTA_DATA_R = 0;
    Delay_Us(40);
}

void LCD_init(void){
    uint32_t dummy ;
    SYSCTL_RCGCGPIO_R |=0x01;       /* enable port A */
    SYSCTL_RCGCGPIO_R |= 0x02;      /* enable port B */
    dummy = SYSCTL_RCGCGPIO_R;      /* wait for stable clk */
    GPIO_PORTB_DIR_R |= 0xFF;       /* portB all output */
	GPIO_PORTA_DIR_R |= 0xE0;       /* PA5, PA6, PA7 output */
    GPIO_PORTB_DEN_R |= 0xFF;
	GPIO_PORTA_DEN_R |= 0xE0;

    Delay_ms(20);            /* initialization sequence */
    LCD_command(0x30);
    Delay_ms(5);
    LCD_command(0x30);
    Delay_Us(100);
    LCD_command(0x30);

    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x02);      /* return cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */

}
