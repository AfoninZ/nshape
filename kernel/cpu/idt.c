#include "../utils.h"

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load();

void idt_set_gate(unsigned char i, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[i].base_lo = base & 0xFFFF;
    idt[i].base_hi = (base >> 16) & 0xFFFF;

    idt[i].sel = sel;
    idt[i].zero = 0;
    idt[i].flags = flags;
}

void idt_init()
{
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    // TODO: Add more ISRs

    idt_load();
}