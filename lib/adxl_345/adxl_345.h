#include <avr/io.h>
void innit_adxl();
// int16_t read_x_axis_raw();
// int16_t read_y_axis_raw();
// int16_t read_z_axis_raw();
// for testing purposes response should be 229
float read_x_axis();
float read_y_axis();
float read_z_axis();
uint8_t read_adxl_id();