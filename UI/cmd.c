#include "string.h"
#include "keybd.h"
#include "text.h"
#include "int.h"
char cmd_buffer[100];
int cmd_buff_pos = 0;
void cmd_keyin(char c)
{
    if (cmd_buff_pos++ < 100)
        cmd_buffer[cmd_buff_pos] = c;
    else
    {
        return;
    }
    text_setfgbg(3, 4);
    text_printc('\n');
    char* yes = "";
    string_itoa(cmd_buff_pos, yes, 10);
    text_prints(yes);
    text_printc('\n');
    text_setfgbg(1, 2);
    text_printc(c);
}