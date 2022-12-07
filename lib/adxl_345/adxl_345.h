#include <avr/io.h>
#include <stdio.h>
struct adxl_345
{
    float x_axis;
    float y_axis;
    float z_axis;
};

void innit_adxl();
void enable_measure_mode();
void read_x_axis(float*);
void read_y_axis(float*);
void read_z_axis(float*);
// for testing purposes response should be 229
uint8_t read_adxl_id();
void read_x_y_z(struct adxl_345*);


