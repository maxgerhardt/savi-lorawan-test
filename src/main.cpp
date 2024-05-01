/* I2C scanner
#include <Wire.h>

void setup()
{
  Wire.begin();

  delay(100);
}

void loop()
{
  volatile byte error;
  byte address;
  static int nDevices = 0;

  nDevices = 0;

  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      nDevices++;
    }
  }

  delay(5000);
}
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

float temperature, pressure, altitude, humidity;

int i = 0;

void setup()
{
  Wire.begin();
  if (!bme.begin())
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1)
      ;
  }
}

void loop()
{
  i++;
  temperature = bme.readTemperature();
  pressure = bme.readPressure() / 100.0F;
  humidity = bme.readHumidity();

  delay(2000);
}