#include "driverlib.h"
#include "spi.h"


int spi_send(const uint8_t* send_buffer, size_t buffer_len)
{
    int i;
    volatile uint8_t dummy;
    for (i = 0; i < buffer_len; ++i)
    {
        while (!(UCB0IFG & UCTXIFG)); 
        UCB0TXBUF = send_buffer[i]; 
        while (!(UCB0IFG & UCRXIFG));
        dummy = UCB0RXBUF;
    }
    return 0;
}

int spi_recv(uint8_t *recv_buffer, size_t buffer_len)
{
    int i;
    for (i = 0; i < buffer_len; ++i)
    {
        while (!(UCB0IFG & UCTXIFG));
        UCB0TXBUF = 0; 
        while (!(UCB0IFG & UCRXIFG)); 
        recv_buffer[i] = UCB0RXBUF; 
    }
    return 0;
}

int spi_send_recv(const uint8_t* send_buffer, uint8_t *recv_buffer, size_t buffer_len)
{
    int i;
    for (i = 0; i < buffer_len; ++i)
    {
        while (!(UCB0IFG & UCTXIFG));
        UCB0TXBUF = send_buffer[i]; 
        while (!(UCB0IFG & UCRXIFG));
        recv_buffer[i] = UCB0RXBUF; 
    }
    return 0;
}
