#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../utils.h"
#include "vga_text.h"
#include "ports.h"

int vga_row;
int vga_col;
char vga_color;
short* vga_buffer;

void vga_init(char color) {
    vga_row = 0;
    vga_col = 0;
    vga_color = color;
    vga_buffer = (short*) VGA_ADDRESS;

    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            vga_buffer[index] = color << 8;
        }
    }
}

void vga_setcolor(char color) {
    vga_color = color;
}

int vga_getcur() {
    io_out(REG_VGA_CTRL, 14);
    int pos = io_in(REG_VGA_DATA) << 8;
    io_out(REG_VGA_CTRL, 15);
    pos += io_in(REG_VGA_DATA);
    return pos * 2;
}

void vga_setcur(int pos) {
    io_out(REG_VGA_CTRL, 14);
    io_out(REG_VGA_DATA, (unsigned char)(pos >> 8));
    io_out(REG_VGA_CTRL, 15);
    io_out(REG_VGA_DATA, (unsigned char)(pos & 0xff));
}

void vga_putat(char c, char color, int x, int y) {
    const int index = y * VGA_WIDTH + x;
    vga_buffer[index] = c | color << 8;
}

void vga_put(char c) {
    switch(c) {
        case '\a':
            break;
        case '\b':
            vga_col--;
            break;
        case '\n':
            vga_col = 0;
            vga_row++;
            break;
        case '\t':
            if (vga_col + 4 >= VGA_WIDTH) {
            vga_col = -1;
            vga_row++;
            } else vga_col += 4;
            break;
        default:
        vga_putat(c, vga_color, vga_col, vga_row);
        if (++vga_col == VGA_WIDTH) {
            vga_col = 0;
            vga_row++;
        }
        if (vga_row == VGA_HEIGHT) {
            for (short i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
                vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
            }
            vga_row = VGA_HEIGHT - 1;
        }
        break;
    }
    vga_setcur(vga_row * VGA_WIDTH + vga_col);
}

void vga_write(const char* data, int size) {
    for (int i = 0; i < size; i++)
        vga_put(data[i]);
}

void vga_print(const char* data) {
    vga_write(data, strlen(data));
}

void vga_printx(uint32_t data) {
    char ref[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	vga_write("0x", 2);
	char hex[5] = "    ";
	for (int i = 0; i < 4; i++) {
		hex[3 - i] = ref[data % 16];
		data = data >> 4;
	}
	vga_write(hex, 4);
}