#include <stdint.h>
#include "serial.h"
#include "mouse.h"
#include "vga.h"
int mx = 69, my = 69;
uint8_t cursor[8] = {
    0x18, //00011000
    0x18, //00011000
    0x18, //00011000
    0xE7, //11100111
    0xE7, //11100111
    0x18, //00011000
    0x18, //00011000
    0x18, //00011000
};
void draw_cursor(int x, int y, int co)
{
    int cx, cy;
	int mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    unsigned char *font = cursor;
    for (cy = 0; cy < 8; cy++)
    {
        for (cx = 0; cx < 8; cx++)
        {
            if (font[cy] & mask[cx])
                vga_setp(x + cx, y + cy, co);
        }
    }
}
void interface_draw()
{
    vga_rectfill(0, 0, 320, 192, 4);
    vga_setfgbg(10, 4);
    vga_setpos(0, 0);
    vga_prints("R-OS");
    vga_setpos(1, 0);
    vga_prints("BETA");
    vga_rectfill(0, 192, 320, 8, 3);
    vga_setfgbg(10, 1);
    vga_setpos(24, 0);
    vga_prints("MENU");
    vga_rectfill(32, 192, 8, 8, 2);
    draw_cursor(mx / 2, (400 - my) / 2, 6);
    vga_writebuffer();
}
#include "string.h"
void interface_mouseint(uint8_t b1, uint8_t b2, uint8_t b3)
{
    if (b1 & 0x80 || b1 & 0x40)
    {
        return;
    }
	unsigned int mouse_x = 0, mouse_y = 0;
	mouse_x = b2 - ((b1 << 4) & 0x100);
    mouse_y = b3 - ((b1 << 3) & 0x100);
	mx = mx + mouse_x;
    my = my + mouse_y;
    if (mx < 0)
        mx = 0;
    else if (mx > 640)
        mx = 640;
    if (my < 0)
        my = 0;
    else if (my > 400)
        my = 400;
    interface_draw();
}
int enable = 0;
int interface_enabled()
{
    return enable;
}
#include "keybd.h"
void interface_init()
{
    enable = 1;
    keyboard_listener(0);
    interface_draw();
    serial_prints("interface_init");
}