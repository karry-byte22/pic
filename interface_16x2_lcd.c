#include <p18f4550.h>
#define LCD_EN LATAbits.LATA1
#define LCD_RS LATAbits.LATA0
#define LCD_PORT LATB

void lcd_delay(unsigned int time)
{
    unsigned int i,j;
for (i=0;i<time;i++)
    for (j=0;j<100;j++);
}

void sendInstruction(unsigned char com)
{
    LCD_RS = 0;
    LCD_PORT = com;
    LCD_EN = 1;
    lcd_delay(10);
    LCD_EN = 0;
    lcd_delay(10);
}

void sendData(unsigned char data)
{
    LCD_RS = 1;
    LCD_PORT = data;
    LCD_EN = 1;
    lcd_delay(10);
    LCD_EN = 0;
    lcd_delay(10);
}

void InitLCD()
{
    ADCON1 = 0x0F;
    TRISB = 0x00;
    TRISAbits.TRISA0=0;
    TRISAbits.TRISA1=0;

    sendInstruction(0x38);
    sendInstruction(0x06);
    sendInstruction(0x0C);
    sendInstruction(0x01);
    lcd_delay(20);

}

void LCD_display(unsigned int row,unsigned int pos,const unsigned char *ch)
{
    if(row==1)
        sendInstruction(0x80+pos-1);
    else
        sendInstruction(0xC0+pos-1);

    while(*ch)
        sendData(*ch++);
}
void main(void)
{
    InitLCD();

    LCD_display(1,1,"Kartik");
    LCD_display(2,1,"Welcom");

    while(1);
}
