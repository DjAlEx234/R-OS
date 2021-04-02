#include "inoutb.h"
#include "text.h"
#include "int.h"
static uint8_t cycle = 0;
static uint8_t byte[3] = {0, 0, 0};
void*mouse_out = 0;
void mouse_setout(void* newout)
{
    mouse_out = newout;
}
void mouse_output()
{
    if (mouse_out == 0)
        return;
    void (*send)(uint8_t b1, uint8_t b2, uint8_t b3) = mouse_out;
    send(byte[0], byte[1], byte[2]);
}
void mouse_handler(__attribute__((unused)) struct regs *r)
{
    switch(cycle)
    {
        case 0:
            byte[0] = inb(0x60);
            if (!((byte[0] >> 3) & 1))
                break;
            cycle++;
            break;
        case 1:
            byte[1] = inb(0x60);
            cycle++;
            break;
        case 2:
            byte[2] = inb(0x60);
            mouse_output();
            cycle = 0;
            break;
    }
}
void mouse_wait(int a)
{
    unsigned int timeout = 100000;
    if (a == 0)
    {
        while (timeout--)
            if ((inb(0x64) & 1) == 1)
                return;
        return;
    }
    else
    {
        while (timeout--)
            if ((inb(0x64) & 2) == 0)
                return;
        return;
    }
}
void mouse_send(int send)
{
    mouse_wait(1);
    outb(0x64, 0xD4);
    mouse_wait(1);
    outb(0x60, send);
}
int mouse_read()
{
    mouse_wait(0);
    return inb(0x60);
}
void mouse_install()
{
    unsigned char mouse_status;
    mouse_send(0xF5);
    mouse_wait(1);
    outb(0x64, 0xA8);
    mouse_wait(1);
    outb(0x64, 0x20);
    mouse_wait(0);
    mouse_status = (inb(0x60) | 2);
    mouse_wait(1);
    outb(0x64, 0x60);
    mouse_wait(1);
    outb(0x60, mouse_status);
    mouse_send(0xF6);//default settings
    mouse_read();
    mouse_send(0xF4);//enable
    mouse_read();
    irq_install_handler(12, mouse_handler);
}