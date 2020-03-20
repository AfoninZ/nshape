#include "../utils.h"
#include "vga_text.h"
#include "../cpu/irq.h"

unsigned int ticks = 0;

void timer_handler(struct regs *r)
{
    ticks++;
    if (ticks % 164 == 0)
    {
        vga_print("Nine seconds have passed! Ticks: ");
        vga_printx(ticks);
        vga_put('\n');
    }
}

void timer_init()
{
    irq_install_handler(0, timer_handler);
}