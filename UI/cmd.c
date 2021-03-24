#include "../Headers/string.h"
#include "../Headers/keybd.h"
#include "../Headers/text.h"
#include "../Headers/int.h"
char cmd_buffer[100];
int cmd_buff_pos = 0;
void cmd_keyin(char c)
{
    text_setfgbg(7, 4);
    text_printc(c);
    text_printc('\n');
    if (cmd_buff_pos++ < 100)
        cmd_buffer[cmd_buff_pos] = c;
    else
    {
        return;
    }
    text_printc('\n');
    text_setfgbg(6, 4);
    char* yes = "jason";
    string_itoa(cmd_buff_pos, yes, 10);
    text_prints(yes);
    text_printc('\n');
}