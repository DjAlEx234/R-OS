#include "string.h"
#include "inoutb.h"
#include "cpuid.h"
#include "text.h"
#include "int.h"
void splashscreen()
{
    char b = 254;
    char s = ' ';
    char ln1[16] = {b, b, b, s, s, s, s, s, b, b, b, s, b, b, b, 0};
    char ln2[16] = {b, s, b, s, s, s, s, s, b, s, b, s, b, s, s, 0};
    char ln3[16] = {b, b, s, s, b, b, b, s, b, s, b, s, b, b, b, 0};
    char ln4[16] = {b, s, b, s, s, s, s, s, b, s, b, s, s, s, b, 0};
    char ln5[16] = {b, s, b, s, s, s, s, s, b, b, b, s, b, b, b, 0};
    text_clear(4);
    text_setfgbg(9, 1);
    text_prints(ln1);
    text_setpos(1, 0);
    text_prints(ln2);
    text_setpos(2, 0);
    text_prints(ln3);
    text_setpos(3, 0);
    text_prints(ln4);
    text_setpos(4, 0);
    text_prints(ln5);
    text_setpos(5, 0);
    text_setfgbg(15, 4);
    text_prints("Welcome to R-OS\nCPU Type: ");
    text_setfgbg(14, 9);
    text_prints(cpuid_string());
    text_setfgbg(15, 4);
}
void keyboardhandler(struct regs *r)
{
    unsigned char maybe = inb(0x60);
    text_setpos(10, 0);
    text_prints(string_itoa(maybe, 16));
}
void keyboardloop()
{
    text_setfgbg(14, 9);
    text_setpos(10, 0);
    text_printc(' ');
    irq_install_handler(1, keyboardhandler);
}
void main(void)
{
    outb(0x3D4, 0x0A); //disable text cursor
	outb(0x3D5, 0x20);
    text_init();
    splashscreen();
    interrupt_install();
    asm("sti");
    text_prints("\nR-OS>");
    keyboardloop();
    //while (1); //it is important to say in C code
}