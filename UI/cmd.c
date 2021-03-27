#include "text.h"
#include "string.h"
#define command_num 4
char* terminal_mode = "";
char* commands[command_num] = {
    "about", "cls", "help", "reboot"
};
void about()
{
    text_prints("\nR-OS Pre-Alpha CLI\nRunning in: ");
    text_prints(terminal_mode);
    text_printc('\n');
}
void cls()
{
    text_prints("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    text_setpos(0, 0);
}
void help()
{
    text_prints("\nList of available commands:");
    for (int i = 0; i < command_num; i++)
    {
        text_printc('\n');
        text_prints(commands[i]);
    }
    text_printc('\n');
}
#include "inoutb.h"
void reboot()
{
    __asm__ volatile ("cli");
    uint8_t temp = 0x02;
    while (temp & 0x02)
       temp = inb(0x64);
    outb(0x64, 0xFE);
    text_prints("\nReboot feature not supported, halting!");
halt:
    __asm__ volatile ("hlt");
    goto halt;
}
void* commandptr[command_num] = {
    about, cls, help, reboot
};
void cmd_run(char* command)
{
    for (int i = 0; i < command_num; i++)
    {
        if (string_cmp(command, commands[i]))
        {
            void(*v)() = commandptr[i];
            text_setfgbg(10, 4);
            v();
            return;
        }
    }
    text_prints("\nCommand \'");
    text_prints(command);
    text_prints("\' not found.\nUse \'help\' for a list of commands.\n");
}
void cmd_mode(char* name)
{
    terminal_mode = name;
}