#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "drivers/vga_text.h"
#include "drivers/serial.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


void k_main(void) 
{
	vga_init(0x07);
	gdt_init();
	vga_print("[  OK  -> Loaded GDT.\n");
	idt_init();
	vga_print("[  OK  -> Loaded IDT.\n");
	//serial_init();
	vga_print("Welcome to nShape!\n");
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
}