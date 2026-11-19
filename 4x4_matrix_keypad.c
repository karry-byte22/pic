#include <p18f4550.h>
#define LCD_EN LATAbits.LATA1
#define LCD_RS LATAbits.LATA0
#define LCDPORT LATB
const unsigned char KeyLookupTbl[16] = {
'1', '4', '7', '*',
'2', '5', '8', '0',
'3', '6', '9', '#',
'A', 'B', 'C', 'D'
};
void lcd_delay(unsigned int time)
{
unsigned int i, j;
for(i = 0; i < time; i++)
for(j = 0; j < 50; j++);
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
unsigned char ReadKey(void)
{
unsigned char i, row, col, key;
while(1)
{
key = 0;
for(i = 0x01; i < 0x10; i <<= 1)
{
LATD = 0xFF;
LATD &= ~i;
lcd_delay(2);
row = (PORTD >> 4) & 0x0F;
for(col = 0x01; col < 0x10; col <<= 1)
{
if((row & col) == 0)
{
while((PORTD & 0xF0) != 0xF0);
return KeyLookupTbl[key];
}
key++;
}
}
}
}
void main(void)
{
unsigned char Key;
unsigned char *string1 = "Key Pressed = ";
ADCON1 = 0x0F;
TRISD = 0xF0;
LATD = 0xFF;
InitLCD();
SendInstruction(0x80);
while(*string1)
{
SendData(*string1++);
}
while(1)
{
Key = ReadKey();
SendInstruction(0xC0);
SendData(Key);
lcd_delay(100);
}
}
