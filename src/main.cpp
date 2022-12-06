// https://www.engineersgarage.com/adxl345-accelerometer-sensor-how-to-use/
#include <avr/io.h>
extern "C"
{
#include "spi_comm.h"
#include "adxl_345.h"
}

#include <Arduino.h>

int main()
{
  Serial.begin(9600);
  innit_adxl();

  while (1)
  {
    Serial.print(" X axis: ");
    Serial.print(read_x_axis(),3);
    Serial.print(" Y axis :");
    Serial.print(read_y_axis(),3);
    Serial.print(" Z axis :");
    Serial.print(read_z_axis(),3);
    Serial.println("");
    _delay_ms(50);
  }

  return 0;
}
