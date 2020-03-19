#include "serial.h"
#include "ports.h"

void serial_init()
{
    io_out(SIO_COM1 + 1, 0x00);
    io_out(SIO_COM1 + 3, 0x80);
    io_out(SIO_COM1 + 0, 0x03);
    io_out(SIO_COM1 + 1, 0x00);
    io_out(SIO_COM1 + 2, 0xC7);
    io_out(SIO_COM1 + 4, 0x0B);
}

int serial_recieved()
{
    return io_in(SIO_COM1 + 5) & 1;
}

char serial_read() {
    while (!serial_recieved())
        ;
    return io_in(SIO_COM1);
}

int serial_sent()
{
    return io_in(SIO_COM1 + 5) & 0x20;
}

void serial_put(char a) {
    while (!serial_sent)
        ;
    io_out(SIO_COM1, a);
}

void serial_print(const char* data) {
    int i = 0;
    while (data[i])
    {
        serial_put(data[i]);
        i++;
    }
}