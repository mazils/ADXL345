#include "spi_comm.h"
#include <avr/interrupt.h>

// SS = PB2
// MOSI = PB3
// MISO = PB4 tas gal input
// SCK = PB5
#define SS PL0
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
// When a serial transfer is complete, the SPIF Flag is set
// Function to send and receive data for both master and slave
// uint8_t spi_send_receive(uint8_t data)
// {
//     PORTL &= ~(_BV(SS));
//     /* Start transmission and Load data into the buffer */
//     SPDR = data;
//     /* Wait for transmission complete */
//     while (!(SPSR & (1 << SPIF)));
//     //read back the data and return it
//     SPDR = 0xff;
//     while (!(SPSR & (1 << SPIF)));
//     PORTL |= _BV(SS);
//     // Return received data
//     return(SPDR);
// }

void spi_write_byte(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)))
        ;
}

uint8_t spi_read_byte()
{
    // Send some nonsense like all 1's
    SPDR = 0x00;
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}