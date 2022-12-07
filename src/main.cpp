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
  struct adxl_345 axes;
  
  
  while (1)
  {
    read_x_y_z(&axes);
    
    Serial.print(" X axis: ");
    Serial.print(axes.x_axis,3);
    Serial.print(" Y axis :");
    Serial.print(axes.y_axis,3);
    Serial.print(" Z axis :");
    Serial.print(axes.z_axis,3);
    Serial.println("");
    _delay_ms(50);
  }

  return 0;
}
