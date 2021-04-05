#include "string.h"
#include "inoutb.h"
#define command_num 9
char* terminal_mode = "";
char* commands[command_num] = {
    "about", "cls", "echo", "help", "mouse", "reboot", "serial", "ui", "vga"
};
char* cmd_notsplit = 0;
char cmd_splote[10][20];
void(*printc)(char c);
void(*prints)(char* s);
void(*setpos)(int r, int c);
void(*fgbg)(int fg, int bg);
int (*getcolumn)();
int (*getrow)();
void about()
{
    prints("\nR-OS Pre-Alpha CLI\nRunning in: ");
    prints(terminal_mode);
    printc('\n');
}
void cls()
{
    prints("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    setpos(0, 0);
}
void echo()
{
    if (string_cmp("echo\0", cmd_notsplit) || string_cmp("echo \0", cmd_notsplit))
    {
        prints("\nNothing to echo!\n");
        return;
    }
    printc('\n');
    prints(cmd_notsplit + 5);
    printc('\n');
}
void help()
{
    prints("\nList of available commands:");
    for (int i = 0; i < command_num; i++)
    {
        printc('\n');
        prints(commands[i]);
    }
    printc('\n');
}
int mouse_running = 0;
#include "mouse.h"
int x, y;
char* blank = "        ";
void mouse_local(uint8_t b1, uint8_t b2, uint8_t b3)
{
    int c = getcolumn();
    int r = getrow();
    fgbg(1, 4);
    setpos(5, 32);
    if (b1 & 0x80 || b1 & 0x40)
    {
        prints("OVERFLOW");
        setpos(r, c);
        fgbg(7, 4);
        return;
    }
    else
        prints(blank);
    setpos(0, 32);
    prints(blank);
    setpos(1, 32);
    prints(blank);
    setpos(2, 32);
    prints(blank);
    char* itoa = 0;
    string_itoa(b1, itoa, 2);
    setpos(0, 29);
    prints("p1:");
    prints(itoa);
    string_itoa(b2, itoa, 2);
    setpos(1, 29);
    prints("p2:");
    prints(itoa);
    string_itoa(b3, itoa, 2);
    setpos(2, 29);
    prints("p3:");
    prints(itoa);
    unsigned int mouse_x = 0, mouse_y = 0;
    mouse_x = b2 - ((b1 << 4) & 0x100);
    mouse_y = b3 - ((b1 << 3) & 0x100);
    setpos(3, 72);
    prints(blank);
    setpos(4, 72);
    prints(blank);
    x = x + mouse_x;
    y = y + mouse_y;
    if (x < 0)
        x = 0;
    else if (x > 640)
        x = 640;
    if (y < 0)
        y = 0;
    else if (y > 400)
        y = 400;
    string_itoa(x, itoa, 10);
    setpos(3, 29);
    prints("mX:");
    prints(itoa);
    string_itoa(y, itoa, 10);
    setpos(4, 29);
    prints("mY:");
    prints(itoa);
    fgbg(7, 4);
    setpos(r, c);
}
void mouse()
{
    cls();
    if (mouse_running == 0)
    {
        mouse_running = 1;
        mouse_setout(mouse_local);
        prints("Mouse Enabled!");
    }
    else
    {
        mouse_running = 0;
        mouse_setout(0);
        prints("Mouse Disabled!");
    }
    printc('\n');
}
void reboot()
{
    __asm__ volatile ("cli");
    uint8_t temp = 0x02;
    while (temp & 0x02)
       temp = inb(0x64);
    outb(0x64, 0xFE);
    prints("\nReboot feature not supported, halting!");
halt:
    __asm__ volatile ("hlt");
    goto halt;
}
#include "serial.h"
void serial()
{
    serial_init();
    prints("\nSerial enabled!\n");
    serial_prints("Serial enabled!");
}
#include "vga.h"
#include "interface.h"
void ui()
{
    if (!vga_enabled())
    {
        prints("\nMust be ran in VGA mode!\n");
        return;
    }
    else if (!mouse_running)
    {
        prints("\nMust be ran with mouse enabled!\n");
        return;
    }
    mouse_setout(interface_mouseint);
    interface_init();
    interface_draw();
}
void vga()
{
    vga_init();
}
void* commandptr[command_num] = {
    about, cls, echo, help, mouse, reboot, serial, ui, vga
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
    cmd_split(cmd_notsplit);
    string_tolower(cmd_splote[0]);
    serial_prints("This command was attemped:");
    serial_prints(command);
    for (int i = 0; i < command_num; i++)
    {
        if (string_cmp(cmd_splote[0], commands[i]))
        {
            void(*v)() = commandptr[i];
            fgbg(10, 4);
            v();
            cmd_clear();
            return;
        }
    }
    prints("\nCommand \'");
    prints(command);
    prints("\' not found.\nUse \'help\' for a list of commands.\n");
    cmd_clear();
}
void cmd_mode(char* name)
{
    terminal_mode = name;
}
void cmd_ptr(void* pc, void* ps, void* fb, void* pos)
{
    printc = pc;
    prints = ps;
    fgbg = fb;
    setpos = pos;
}
void cmd_getposptr(int (*getr)(), int (*getc)())
{
    getrow = getr;
    getcolumn = getc;
}