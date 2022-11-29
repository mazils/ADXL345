
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
    Serial.println("X axis");
    Serial.println(read_x_axis());
    // Serial.println("Y axis");
    // Serial.println(read_y_axis());
    _delay_ms(100);
  }

  return 0;
}
