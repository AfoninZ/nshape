void irq_install_handler(char irq, void (*handler)(struct regs *r));
void irq_init();