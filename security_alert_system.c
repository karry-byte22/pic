#include<p18f4550.h>

void delay(void)
{
    unsigned int i;
        for (i=0;i<30000;i++);
}

void main ()
{
    signed char i;
    unsigned char key = 0;

    TRISB = 0x00;
    LATB = 0x00;

    ADCON1 = 0x0F;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;

    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;

    while(1)
    {
        if(PORTAbits.RA2 ==0)
            key =1;

        if(PORTAbits.RA3 ==0)
            key=0;

        if(key==1)
        {
            LATAbits.LATA4 = 1;
            LATAbits.LATA5 = 1;

        for (i=0;i<8;i++)
        {
            LATB = (1<<i);
            delay();
        }
}
        else
        {
            LATAbits.LA4 = 0;
            LATAbits.LA5 = 0;

            for (i=7;i>=0;i--)
            {
                LATB = (1 << i);
                delay();
            }
            LATB = 0x00;
        }
    }
}
