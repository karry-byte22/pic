#include <p18f4550.h>

#define _XTAL_FREQ 20000000

void main(void)
{
    unsigned char i;

    TRISB = 0x00;
    LATB = 0x00;

    while(1)
    {
        // BLINKING LEDS
        LATB = 0xFF;
        __delay_ms(500);

        LATB = 0x00;
        __delay_ms(500);

        // ALTERNATE BLINKING
        LATB = 0x55;
        __delay_ms(500);

        LATB = 0xAA;
        __delay_ms(500);

        // BLINK FROM RB0 TO RB7
        for(i = 0; i < 8; i++)
        {
            LATB = (1 << i);
            __delay_ms(500);
        }

        // BLINK FROM RB7 TO RB0
        for(i = 7; i > 0; i--)
        {
            LATB = (1 << (i - 1));
            __delay_ms(500);
        }

        LATB = 0x00;
        __delay_ms(500);
    }
}
