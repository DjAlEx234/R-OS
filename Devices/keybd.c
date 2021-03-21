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
#include "inoutb.h"
#include "int.h"
void*keyboard_send = 0;
void keyboard_listener(void* v)
{
    keyboard_send = v;
}
void keyboard_gotkey(char c)
{
    if (keyboard_send == 0)
        return;
    void (*send)(char key) = keyboard_send;
    send(c);
}
void keyboard_handler(__attribute__((unused)) struct regs *r)
{
    unsigned char key = inb(0x60);
    if (key & 0x80)
        return;
    else
        keyboard_gotkey(keyboard_keys[key]);
}
void keyboard_init()
{
    irq_install_handler(1, keyboard_handler);
}