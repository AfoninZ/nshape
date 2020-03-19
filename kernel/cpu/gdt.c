#include "../utils.h"
#include "gdt.h"

struct gdt_entry
{
    unsigned short limit_lo;
    unsigned short base_lo;
    unsigned char base_mid;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_hi;
} __attribute__((packed));

struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gdtp;

extern void gdt_flush();

void gdt_set_gate(int i, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    gdt[i].base_lo = (base & 0xFFFF);
    gdt[i].base_mid = (base >> 16) & 0xFF;
    gdt[i].base_hi = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[i].limit_lo = (limit & 0xFFFF);
    gdt[i].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[i].granularity |= (gran & 0xF0);
    gdt[i].access = access;
}

void gdt_init()
{
    gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdtp.base = &gdt;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null Descriptor
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_flush();
}