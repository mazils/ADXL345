#include <avr/io.h>
void innit_adxl();
int16_t read_x_axis();
// for testing purposes response should be 229
uint8_t read_adxl_id();