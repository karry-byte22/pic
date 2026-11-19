#include <p18f4550.h>
#include <stdio.h>
#define LCD_EN LATAbits.LATA1
#define LCD_RS LATAbits.LATA0
#define LCDPORT LATB
unsigned char str[16];
void lcd_delay(unsigned int time)
{
unsigned int i, j;
for(i = 0; i < time; i++)
for(j = 0; j < 100; j++);
}
void SendInstruction(unsigned char command)
{
LCD_RS = 0;
LCDPORT = command;
LCD_EN = 1;
lcd_delay(10);
LCD_EN = 0;
lcd_delay(10);
}
void SendData(unsigned char lcddata)
{
LCD_RS = 1;
LCDPORT = lcddata;
LCD_EN = 1;
lcd_delay(10);
LCD_EN = 0;
lcd_delay(10);
}
void InitLCD(void)
{
ADCON1 = 0x0F;
TRISB = 0x00;
TRISAbits.TRISA0 = 0;
TRISAbits.TRISA1 = 0;
SendInstruction(0x38);
SendInstruction(0x06);
SendInstruction(0x0C);
SendInstruction(0x01);
lcd_delay(20);
SendInstruction(0x80);
}
void LCD_display(unsigned int row, unsigned int pos,
unsigned char *ch)
{
if(row == 1)
SendInstruction(0x80 | (pos - 1));
else
SendInstruction(0xC0 | (pos - 1));
while(*ch)
SendData(*ch++);
}
void ADCInit(void)
{
TRISEbits.TRISE2 = 1;
ADCON1 = 0x0D;
// AN0-AN7 analog; VDD and VSS as references
ADCON2 = 0xAE;
// Right justified, 12 TAD acquisition,
// FOSC/64 conversion clock
}
unsigned short Read_ADC(unsigned char Ch)
{
ADCON0 = (Ch << 2) | 0x01;
lcd_delay(2);
GO_DONE = 1;
while(GO_DONE == 1);
return ADRES;
}
void main(void)
{
unsigned int adc_value;
unsigned int temp;
InitLCD();
ADCInit();
LCD_display(1, 1, "Temperature:");
while(1)
{
adc_value = Read_ADC(7);
temp = (adc_value * 500UL) / 1023UL;
sprintf((char *)str, "%u C", temp);
LCD_display(2, 1, str);
lcd_delay(5000);
}
}
