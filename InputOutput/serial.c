#include "inoutb.h"
#include "string.h"
int serial_enabled = 0;
#define PORT 0x3F8//serial 1 port
void serial_init()
{
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x80);
    outb(PORT + 0, 0x03);
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x03);
    outb(PORT + 2, 0xC7);
    serial_enabled = 1;
}
int serial_empty()
{
    return inb(PORT + 5) & 0x20;
}
void serial_printc(char c)
{
    if (serial_enabled == 0)
        return;
    while (serial_empty() == 0);
    outb(PORT, c);
}
void serial_internal(char* s)
{
    for (int i = 0; i < string_len(s); i++)
        serial_printc(s[i]);
}
void serial_prints(char* s)
{
    serial_internal(s);
    serial_printc('\n');//split apart
}
void serial_printd(int d)
{
    char* out = 0;
    string_itoa(d, out, 10);
    serial_internal(out);
}
void serial_printh(int h)
{
    char* out = 0;
    string_itoa(h, out, 16);
    serial_internal(out);
}