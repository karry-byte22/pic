const int ledPin = 9;
void setup()
{
pinMode(ledPin, OUTPUT);
}
void loop()
{
// Increase brightness
for (int b = 0; b <= 255; b++)
{
analogWrite(ledPin, b);
delay(20);
}
// Decrease brightness
for (int b = 255; b >= 0; b--)
{
analogWrite(ledPin, b);
delay(20);
}
}
