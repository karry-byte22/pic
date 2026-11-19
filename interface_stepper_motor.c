#include <p18f4550.h>
#define _XTAL_FREQ 20000000

void main(void)
{
    unsigned int i;
    unsigned char sequence[4] = {0x09, 0x03, 0x06, 0x0C};

    TRISD = 0x00;
    PORTD = 0x00;

    while(1)
    {
        // Clockwise rotation
        for(i = 0; i < 200; i++)
        {
            PORTD = sequence[i % 4];
            __delay_ms(10);
        }

        __delay_ms(500);

        // Anticlockwise rotation
        for(i = 0; i < 200; i++)
        {
            PORTD = sequence[3 - (i % 4)];
            __delay_ms(10);
        }

        PORTD = 0x00;
        __delay_ms(500);
    }
}
