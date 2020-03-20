#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/irq.h"

#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "drivers/vga_text.h"
#include "drivers/serial.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


void k_main(void) 
{
	vga_init(0x07);
	gdt_init();
	print_ok("Loaded GDT.");
	idt_init();
	print_ok("Loaded IDT.");
	isr_init();
	print_ok("Loaded ISRs.");
	irq_init();
	print_ok("Loaded IRQs.");
	__asm__ __volatile__ ("sti"); 
	//serial_init();
	vga_print("\nWelcome to nShape!\n");
	timer_init();
	keyboard_init();
	for (char i = 0; i < 8; i++)
	{
		vga_setcolor((char) i << 4 | (i + 8));
		vga_print("FF");
	}
	vga_put('\n');
	for (char i = 8; i < 16; i++)
	{
		vga_setcolor((char) i << 4 | (i - 8));
		vga_print("OS");
	}
	vga_put('\n');
	vga_setcolor(0x07);
	while (1) {};
}

void print_ok(char* msg)
{
	vga_print("-");
	vga_setcolor(0x0A);
	vga_print(" OK ");
	vga_setcolor(0x07);
	vga_print("-> ");
	vga_print(msg);
	vga_put('\n');
}