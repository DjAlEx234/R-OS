#include "string.h"
#include "inoutb.h"
#include "text.h"
#define command_num 5
char* terminal_mode = "";
char* commands[command_num] = {
    "about", "cls", "echo", "help", "reboot"
};
char* cmd_notsplit = 0;
char cmd_splote[10][20];
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
void echo()
{
    if (cmd_splote[1] == 0)
    {
        text_prints("\nNothing to echo!\n");
        return;
    }
    text_printc('\n');
    text_prints(cmd_notsplit + 5);
    text_printc('\n');
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
    about, cls, echo, help, reboot
};
void cmd_clear()
{
    cmd_splote[0][0] = 0;
    cmd_splote[1][0] = 0;
    cmd_splote[2][0] = 0;
    cmd_splote[3][0] = 0;
    cmd_splote[4][0] = 0;
    cmd_splote[5][0] = 0;
    cmd_splote[6][0] = 0;
    cmd_splote[7][0] = 0;
    cmd_splote[8][0] = 0;
    cmd_splote[9][0] = 0;
    cmd_notsplit = 0;
}
void cmd_split(char tosplit[])
{
    int length = string_len(tosplit);
    int variable = 0, index = 0;
    for (int loop = 0; loop <= length; loop++)
    {
        if (tosplit[loop] == ' ' || tosplit[loop] == '\n')
        {
            cmd_splote[variable++][index] = 0;
            index = 0;
        }
        else
            cmd_splote[variable][index++] = tosplit[loop];
        if (variable == 10)
            break;
    }
}
void cmd_run(char* command)
{
    cmd_notsplit = command;
    cmd_split(command);
    for (int i = 0; i < command_num; i++)
    {
        if (string_cmp(cmd_splote[0], commands[i]))
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
    cmd_clear();
}
void cmd_mode(char* name)
{
    terminal_mode = name;
}