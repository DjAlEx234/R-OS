#include "terminal.h"
#include "inoutb.h"
#include "string.h"
#include "cpuid.h"
#include "keybd.h"
#include "text.h"
#include "int.h"
#include "cmd.h"
void splashscreen()
{
    char* ln1 = " _____              ____     _____";
    char* ln2 = "|  __ \\            / __ \\   / ____|";
    char* ln3 = "| |__) |  ______  | |  | | | (___  ";
    char* ln4 = "|  _  /  |______| | |  | |  \\___ \\";
    char* ln5 = "| | \\ \\           | |__| |  ____) |";
    char* ln6 = "|_|  \\_\\           \\____/  |_____/";
    text_clear(4);
    text_setfgbg(4, 1);
    text_prints("\n\n\n\n\n\n");
    text_setpos(0, 0);
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
    text_prints(ln6);
    text_setpos(6, 0);
    text_printc('\n');
    text_setfgbg(15, 4);
    text_prints("Welcome to R-OS. CPU Info:\n");
    text_setfgbg(14, 9);
    text_prints("Bits:");
    if (!cpuid_is64bit())
        text_prints(" 32-bit");
    else
        text_prints(" 64-bit");
    text_prints(" Vendor: ");
    text_prints(cpuid_string());
    text_setfgbg(15, 4);
}
void cmd()
{
    text_prints("\nR-OS>");
    text_setfgbg(7, 4);
    cmd_mode("Text Mode");
    keyboard_listener(term_keyin);
}
void main(void)
{
    outb(0x3D4, 0x0A); //disable text cursor
	outb(0x3D5, 0x20);
    text_init();
    splashscreen();
    interrupt_install();
    __asm__ volatile ("sti");
    keyboard_init();
    text_prints("\n\nPress SPACE to enter command line...");
    keyboard_waitchar(' ');
    cmd();
    while(1);
}