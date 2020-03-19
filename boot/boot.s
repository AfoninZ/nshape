[bits 32]
MB_ALIGN equ 1<<0
MB_MEMINFO equ 1<<1
MB_FLAGS equ MB_ALIGN | MB_MEMINFO
MB_MAGIC equ 0x1BADB002
MB_CHECK equ -(MB_MAGIC + MB_FLAGS)

section .multiboot
align 4
	dd MB_MAGIC
	dd MB_FLAGS
	dd MB_CHECK

section .bss
align 16
	stack_bottom:
	resb 16384
	stack_top:

section .text
global _start:function (_start.s_end - _start)
_start:
	mov esp, stack_top
	extern k_main
	call k_main

	cli
	hlt
	jmp $
.s_end:

global gdt_flush
extern gdtp
gdt_flush:
	lgdt [gdtp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2
.g_end:

flush2:
	ret

global idt_load
extern idtp
idt_load:
	lidt [idtp]
	ret