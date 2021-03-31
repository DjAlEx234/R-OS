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
    text_setfgbg(12, 1);
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
    term_ptr(text_printc, text_prints, text_setfgbg, text_setpos);
    keyboard_listener(term_keyin);
}
void main(void)
{
    splashscreen();
    cmd();
    while(1);
}
#include "multiboot.h"
void multiboot_main(unsigned long magic, unsigned long addr)
{
    outb(0x3D4, 0x0A); //disable text cursor
	outb(0x3D5, 0x20);
    text_init();
    text_setfgbg(15, 0);
    text_prints("DEBUG INFO:\n");
    char* mag = 0;
    string_itoa(magic, mag, 16);
    text_prints("MAGIC: ");
    text_prints(mag);
    multiboot_info_t *mbi;
    mbi = (multiboot_info_t*) addr;
    string_itoa((unsigned) mbi->flags, mag, 2);
    text_prints("\nFLAGS: ");
    text_prints(mag);
    if (mbi->flags & (1 << 0))
    {
        string_itoa((unsigned) mbi->mem_lower, mag, 16);
        text_prints("\nMEMLO: ");
        text_prints(mag);
        string_itoa((unsigned) mbi->mem_upper, mag, 16);
        text_prints("\nMEMHI: ");
        text_prints(mag);
    }
    if (mbi->flags & (1 << 6))
    {
        multiboot_memory_map_t *mem;
        string_itoa((unsigned) mbi->mmap_addr, mag, 16);
        text_prints("\nMMAPA: ");
        text_prints(mag);
        string_itoa((unsigned) mbi->mmap_length, mag, 16);
        text_prints("\nMMAPL: ");
        text_prints(mag);
        for (mem = (multiboot_memory_map_t *) mbi->mmap_addr; (unsigned long) mem < mbi->mmap_addr + mbi->mmap_length; mem = (multiboot_memory_map_t *) ((unsigned long) mem + mem->size + sizeof (mem->size)))
        {
            string_itoa((unsigned) mem->size, mag, 16);
            text_prints("\nMSIZE: ");
            text_prints(mag);
            string_itoa((unsigned) (mem->addr >> 32), mag, 16);
            text_prints(" MADDR: ");
            text_prints(mag);
            string_itoa((unsigned) (mem->addr & 0xffffffff), mag, 16);
            text_prints(mag);
            string_itoa((unsigned) (mem->len >> 32), mag, 16);
            text_prints(" MLENG: ");
            text_prints(mag);
            string_itoa((unsigned) (mem->len & 0xffffffff), mag, 16);
            text_prints(mag);
            if ((unsigned) mem->type == 1)
                text_prints(" MTYPE: AVAILABLE");
            else if ((unsigned) mem->type == 2)
                text_prints(" MTYPE: RESERVED");
            else if ((unsigned) mem->type == 3)
                text_prints(" MTYPE: ACPI RECLAIMABLE");
            else if ((unsigned) mem->type == 4)
                text_prints(" MTYPE: NVS");
            else if ((unsigned) mem->type == 5)
                text_prints(" MTYPE: BAD RAM");
        }
    }
    interrupt_install();
    __asm__ volatile ("sti");
    keyboard_init();
    text_printc('\n');
    text_setfgbg(0, 15);
    text_prints("Press SPACE to enter R-OS...");
    keyboard_waitchar(' ');
    main();
}