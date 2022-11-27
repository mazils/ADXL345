#include "adxl_345.h"
#include "spi_comm.h"
#define SS PL0

void innit_adxl()
{
  DDRL |= _BV(SS);
  PORTL |= _BV(SS);
  init_spi(3, 0);
  enable_measure_mode();
}
// makes adxl go from standby mode to measuring mode
void enable_measure_mode()
{
  // innit accelerometer into measuring mode
  uint8_t adxl_innit = 0x2D;
  adxl_innit |= _BV(6); // MB to 1, multiple bits
  // slave select
  PORTL &= ~(_BV(SS));
  spi_write_byte(adxl_innit);
  uint8_t adxl_read_mode = 0x00;
  adxl_read_mode |= _BV(3);
  spi_write_byte(adxl_read_mode);
  PORTL |= _BV(SS);
}

int16_t read_x_axis()
{
  // tryin to read x axis0
  int8_t x_axis0 = 0x32;
  x_axis0 |= _BV(7); // Read set to 1
  x_axis0 |= _BV(6); // MB to 1, multiple bits

  PORTL &= ~(_BV(SS));
  spi_write_byte(x_axis0);
  int8_t x_axis0_result = spi_read_byte();
  PORTL |= _BV(SS);

  //  //tryin to read x axis1
  PORTL &= ~(_BV(SS));
  int8_t x_axis1 = 0x33;
  x_axis1 |= _BV(7); // Read set to 1
  x_axis1 |= _BV(6); // MB to 1, multiple bits
  // send address
  spi_write_byte(x_axis1);
  // read data from that address
  int8_t x_axis1_result = spi_read_byte();
  PORTL |= _BV(SS);
  // combine x1 and x0
  int16_t x_axis = (x_axis1_result << 8) | x_axis0_result;
  return x_axis;
}

uint8_t read_adxl_id()
{
  // test to get the id of ADXL
  uint8_t adxl_id = 0x00;
  adxl_id |= _BV(7); // Read set to 1
  adxl_id |= _BV(6); // MB to 1, multiple bits
  PORTL &= ~(_BV(SS));
  spi_write_byte(adxl_id);
  adxl_id = spi_read_byte();
  PORTL |= _BV(SS);
  return adxl_id;
}
