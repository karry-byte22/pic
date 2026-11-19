#include <DHT.h>
// Define the sensor pin and type
#define DHTPIN 2
#define DHTTYPE DHT11
// Create DHT object
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
Serial.begin(9600);
Serial.println("DHT11 Sensor Reading Started...");
dht.begin();
}
void loop()
{
// Wait between measurements
delay(2000);
// Read humidity and temperature
float h = dht.readHumidity();
float t = dht.readTemperature(); // Celsius
float tF = dht.readTemperature(true); // Fahrenheit
// Check if readings failed
if (isnan(h) || isnan(t) || isnan(tF))
{
Serial.println("Failed to read from DHT sensor! Check wiring.");
return;
}
// Print readings
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" °C\t");
Serial.print("Temperature: ");
Serial.print(tF);
Serial.println(" °F");
}
