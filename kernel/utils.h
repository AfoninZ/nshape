unsigned char* memcpy(unsigned char* dest, const unsigned char* src, int count);
unsigned char* memset(unsigned char* dest, unsigned char val, int count);
unsigned char* memsetw(unsigned short* dest, unsigned short val, int count);
int strlen(const char* str);

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};