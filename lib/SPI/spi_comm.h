#include <avr/io.h>
void init_spi(uint8_t mode, uint8_t LSBFirst); // 1 for lsb first
void spi_write_byte(uint8_t data);
uint8_t spi_read_byte();