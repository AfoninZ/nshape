#define SIO_COM1 0x3f8

void serial_init();

char serial_read();
void serial_put(char a);
void serial_print(const char *data);