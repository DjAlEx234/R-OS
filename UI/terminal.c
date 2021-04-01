#include "string.h"
#include "keybd.h"
#include "cmd.h"
static char term_buffer[101];
int term_buff_pos = 0;
void(*printcptr)(char c);
void(*printsptr)(char* s);
void(*setposptr)(int r, int c);
void(*fgbgptr)(int fg, int bg);
void term_ptr(void* pc, void* ps, void* fb, void* pos)
{
    printcptr = pc;
    printsptr = ps;
    fgbgptr = fb;
    setposptr = pos;
    cmd_ptr(printcptr, printsptr, fgbgptr, setposptr);
}
void term_bufin(char c)
{
    if (term_buff_pos < 100)
        term_buffer[term_buff_pos++] = c;
    else
        return;
    printcptr(c);
}
void term_bufdel()
{
    if (term_buff_pos == 0)
        return;
    printcptr('\b');
    term_buff_pos--;
    term_buffer[term_buff_pos] = 0;
}
void term_run()
{
    term_buff_pos++;
    term_buffer[term_buff_pos] = 0;
    cmd_run(term_buffer);
    for (int i = 0; i < term_buff_pos; i++)
        term_buffer[i] = 0;
    term_buff_pos = 0;
    fgbgptr(15, 4);
    printsptr("R-OS>");
    fgbgptr(7, 4);
}
char number_shift[10] = {
    ')', '!', '@', '#', '$', 
    '%', '^', '&', '*', '('
};
void term_keyin(struct keyboard_send send)
{
    char c = send.ascii;
    if (c >= 32 && c <= 126 && !send.shift)
        term_bufin(c);
    else if (c == 32)
        term_bufin(c);
    else if (c == 8)
        term_bufdel();
    else if (c == 10)
        term_run();
    else if ((c >= 32 && c <= 126) && send.shift)
    {
        if (c >= 97 && c <= 122)
        {
            term_bufin(c - 32);
            return;
        }
        else if (c >= 48 && c <= 57)
        {
            term_bufin(number_shift[c - 48]);
            return;
        }
        switch (c)
        {
            case '`':
                term_bufin('~');
                return;
            case '-':
                term_bufin('_');
                return;
            case '=':
                term_bufin('+');
                return;
            case '[':
                term_bufin('{');
                return;
            case ']':
                term_bufin('}');
                return;
            case '\\':
                term_bufin('|');
                return;
            case ';':
                term_bufin(':');
                return;
            case '\'':
                term_bufin('"');
                return;
            case ',':
                term_bufin('<');
                return;
            case '.':
                term_bufin('>');
                return;
            case '/':
                term_bufin('?');
                return;
            default:
                break;
        }
    }
}