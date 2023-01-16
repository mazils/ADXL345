// https://www.engineersgarage.com/adxl345-accelerometer-sensor-how-to-use/
extern "C"
{
#include "adxl_345.h"
}
#include <Arduino.h>

int main()
{
  Serial.begin(9600);
  innit_adxl();
  struct adxl_345 axes;
  double pitch, roll,roll_f,pitch_f;

  // Serial.print("X:,Y:,Z:,");
  while (1)
  {
    read_x_y_z(&axes);
    
    // Roll & Pitch Equations
    roll = atan2(axes.y_axis , sqrt(pow(axes.x_axis,2) + pow(axes.z_axis,2))) * 180.0 / PI ;
    pitch = atan2(-1 * axes.x_axis, sqrt(pow(axes.y_axis,2) + pow(axes.z_axis,2))) *180.0 / PI;

    // Low-pass filter
    roll_f = 0.94 * roll_f + 0.06 * roll;
    pitch_f = 0.94 * pitch_f + 0.06 * pitch;

    Serial.print(pitch_f);
    Serial.print(",");
    Serial.println(roll_f);

    _delay_ms(10);
  }

  return 0;
}
