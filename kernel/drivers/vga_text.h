#define VGA_ADDRESS 0xb8000
#define VGA_HEIGHT 25
#define VGA_WIDTH 80

#define REG_VGA_CTRL 0x3d4
#define REG_VGA_DATA 0x3d5

void vga_init(char color);
void vga_print(const char *message);
void vga_setcolor(char color);