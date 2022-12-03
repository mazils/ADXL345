#include "adxl_345.h"
#include "spi_comm.h"
#define SS PL0
// https://www.best-microcontroller-projects.com/adxl345.html
// TODO: set up sensasitivity options
void innit_adxl()
{
  DDRL |= _BV(SS);
  PORTL |= _BV(SS);
  init_spi(3, 0);
  // configure adxl before measuring mode enable
  enable_measure_mode();
}
// makes adxl go from standby mode to measuring mode
void enable_measure_mode()
{
  // innit accelerometer into measuring mode
  uint8_t adxl_innit_byte = 0x2D;
  adxl_innit_byte |= _BV(6); // MB to 1, multiple bits
  // slave select
  PORTL &= ~(_BV(SS));
  spi_write_byte(adxl_innit_byte);
  uint8_t adxl_read_mode_byte = 0x00;
  adxl_read_mode_byte |= _BV(3);
  spi_write_byte(adxl_read_mode_byte);
  PORTL |= _BV(SS);
}

int16_t read_x_axis_raw()
{
  // tryin to read x axis0
  int8_t x_axis_byte0 = 0x32;
  x_axis_byte0 |= _BV(7); // Read set to 1
  x_axis_byte0 |= _BV(6); // MB to 1, multiple bits

  PORTL &= ~(_BV(SS));
  spi_write_byte(x_axis_byte0);
  int8_t x_axis_0_result = spi_read_byte();
  PORTL |= _BV(SS);

  //  //tryin to read x axis1
  PORTL &= ~(_BV(SS));
  int8_t x_axis_byte_1 = 0x33;
  x_axis_byte_1 |= _BV(7); // Read set to 1
  x_axis_byte_1 |= _BV(6); // MB to 1, multiple bits
  // send address
  spi_write_byte(x_axis_byte_1);
  // read data from that address
  int8_t x_axis1_result = spi_read_byte();
  PORTL |= _BV(SS);
  // combine x1 and x0
  int16_t x_axis_raw = (int16_t)x_axis1_result << 8 | x_axis_0_result;
  return x_axis_raw;
}
int16_t read_y_axis_raw()
{
  // tryin to read y axis0
  int8_t y_axis_byte_0 = 0x34;
  y_axis_byte_0 |= _BV(7); // Read set to 1
  y_axis_byte_0 |= _BV(6); // MB to 1, multiple bits

  PORTL &= ~(_BV(SS));
  // send address
  spi_write_byte(y_axis_byte_0);
  // read from that address
  int8_t y_axis_0_result = spi_read_byte();
  PORTL |= _BV(SS);

  //  //tryin to read y axis1
  PORTL &= ~(_BV(SS));
  int8_t y_axis_byte_1 = 0x35;
  y_axis_byte_1 |= _BV(7); // Read set to 1
  y_axis_byte_1 |= _BV(6); // MB to 1, multiple bits
  // send address
  spi_write_byte(y_axis_byte_1);
  // read data from that address
  int8_t y_axis1_result = spi_read_byte();
  PORTL |= _BV(SS);
  // combine x1 and x0
  int16_t y_axis_raw = (int16_t)y_axis1_result << 8 | y_axis_0_result;
  return y_axis_raw;
}
int16_t read_z_axis_raw()
{
  // tryin to read y axis0
  int8_t z_axis_byte_0 = 0x36;
  z_axis_byte_0 |= _BV(7); // Read set to 1
  z_axis_byte_0 |= _BV(6); // MB to 1, multiple bits

  PORTL &= ~(_BV(SS));
  // send address
  spi_write_byte(z_axis_byte_0);
  // read from that address
  int8_t z_axis_0_result = spi_read_byte();
  PORTL |= _BV(SS);

  //  //tryin to read y axis1
  PORTL &= ~(_BV(SS));
  int8_t z_axis_1 = 0x37;
  z_axis_1 |= _BV(7); // Read set to 1
  z_axis_1 |= _BV(6); // MB to 1, multiple bits
  // send address
  spi_write_byte(z_axis_1);
  // read data from that address
  int8_t z_axis_1_result = spi_read_byte();
  PORTL |= _BV(SS);
  // combine x1 and x0
  int16_t z_axis_raw = (int16_t)z_axis_1_result << 8 | z_axis_0_result;
  return z_axis_raw;
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
// https://www.engineersgarage.com/adxl345-accelerometer-raspberry-pi-i2c/
// sensitivity 2 G's Reading acceleration in SI units from ADXL345:
//https://www.edaboard.com/threads/accelerometer-questions.250221/
float read_x_axis()
{
  return (float)((read_x_axis_raw() *0.004) * 9.80665);
}
// sensitivity 2 G's
float read_y_axis()
{
  return (float)((read_y_axis_raw() *0.004)* 9.80665) ;
}
// sensitivity  G's
float read_z_axis()
{

  return (float)((read_z_axis_raw() *0.004)* 9.80665) ;
}