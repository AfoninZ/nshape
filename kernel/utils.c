#include "utils.h"

unsigned char* memcpy(unsigned char* dest, const unsigned char* src, int count)
{
    for (int i = 0; i < count; i++)
    {
        dest[i] = src[i];
    }
    return dest;
}

unsigned char* memset(unsigned char* dest, unsigned char val, int count)
{
    for (int i = 0; i < count; i++)
    {
        dest[i] = val;
    }
    return dest;
}

unsigned char* memsetw(unsigned short* dest, unsigned short val, int count)
{
    for (int i = 0; i < count; i++)
    {
        dest[i] = val;
    }
    return dest;
}

int strlen(const char* str)
{
    int len = 0;
    while (str[len])
        len++;
    return len;
}