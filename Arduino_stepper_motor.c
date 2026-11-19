#include <Stepper.h>
const int stepsPerRevolution = 2048;
// Create Stepper object
// Pins connected to ULN2003 IN1, IN2, IN3, IN4
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
void setup()
{
Serial.begin(9600);
Serial.println("Stepper Motor Test");
// Set motor speed to 10 RPM
myStepper.setSpeed(10);
}
void loop()
{
Serial.println("Clockwise rotation...");
myStepper.step(stepsPerRevolution); // One full revolution clockwise
delay(1000);
Serial.println("Counterclockwise rotation...");
myStepper.step(-stepsPerRevolution); // One full revolution counterclockwise
delay(1000);
}
