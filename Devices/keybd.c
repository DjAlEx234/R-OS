#include <stdbool.h>
#include "inoutb.h"
#include "keybd.h"
#include "int.h"
char keyboard_keys[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b',
    '\t',
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0,
    '*',
    0,  /* Alt */
    ' ',    /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};
void*keyboard_ptr = 0;
void keyboard_listener(void* v)
{
    keyboard_ptr = v;
}
bool shift;
bool ctrl;
bool alt;
void keyboard_gotkey(struct keyboard_send key)
{
    if (keyboard_ptr == 0)
        return;
    void (*send)(struct keyboard_send key) = keyboard_ptr;
    send(key);
}
bool caps = false;
void keyboard_handler(__attribute__((unused)) struct regs *r)
{
    unsigned char key = inb(0x60);
    switch (key)
    {
        case 0xAA:
            shift = false;
            break;
        case 0xB6:
            shift = false;
            break;
        case 0x9D:
            ctrl = false;
            break;
        case 0xB8:
            alt = false;
            break;
        case 0x2A:
            shift = true;
            break;
        case 0x36:
            shift = true;
            break;
        case 0x1D:
            ctrl = true;
            break;
        case 0x38:
            alt = true;
            break;
        case 0x3A:
            caps = !caps;
            return;
        default:
            break;
    }
    if (key & 0x80)
        return;
    struct keyboard_send tosend;
    tosend.shift = shift ^ caps;
    tosend.ctrl = ctrl;
    tosend.alt = alt;
    tosend.scan = key;
    tosend.ascii = keyboard_keys[key];
    keyboard_gotkey(tosend);
}
void keyboard_waitchar(char c)
{
    void* keep = keyboard_ptr;
    keyboard_ptr = 0;
    unsigned char wait = 0;
    while (keyboard_keys[wait] != c)
    {
        wait = inb(0x60);
    }
    keyboard_ptr = keep;
}
void keyboard_init()
{
    irq_install_handler(1, keyboard_handler);
}