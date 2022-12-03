#include "spi_comm.h"
#include <avr/interrupt.h>

// MOSI = PB3
// MISO = PB4 tas gal input
// SCK = PB5
#define MOSI PB2
#define MISO PB3
#define SCK PB1

void init_spi(uint8_t mode, uint8_t LSBFirst)
{
    DDRB |= _BV(SCK) | _BV(MOSI) | _BV(DDB0); // wtf
    PORTB |= _BV(SCK) | _BV(MOSI);
    DDRB &= ~_BV(MISO);

    /* Enable SPI, Master, set clock rate fck/16
    /When the DORD bit is written to zero, the MSB of the data word is transmitted first.*/
    SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(SPR1);
    set_significance(LSBFirst);
    set_spi_mode(mode);
}

// use mode 0
void set_spi_mode(uint8_t mode)
{
    if (mode == 0)
    {
        SPCR &= ~(_BV(CPOL) | _BV(CPHA));
    }
    else if (mode == 1)
    {
        SPCR |= _BV(CPHA);
        SPCR &= ~(_BV(CPOL));
    }
    else if (mode == 2)
    {
        SPCR |= _BV(CPOL);
        SPCR &= ~(_BV(CPHA));
    }
    else if (mode == 3)
    {
        SPCR |= _BV(CPOL) | _BV(CPHA);
    }
}

// set bit significance msb first
void set_significance(uint8_t LSBFirst)
{
    if (LSBFirst)
    {
        SPCR |= _BV(DORD);
    }
    else if (!LSBFirst)
    {
        SPCR &= ~(DORD);
    }
}

void spi_write_byte(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
}

uint8_t spi_read_byte()
{
    // Send some nonsense like all 1's
    SPDR = 0x00;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}