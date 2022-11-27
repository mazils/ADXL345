
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

    Serial.println(read_x_axis());
    _delay_ms(20);
  }

  return 0;
}
