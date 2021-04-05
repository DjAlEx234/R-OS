#ifndef vgah
#define vgah
void vga_rectfill(int x, int y, int width, int height, int c);
void vga_setp(int x, int y, int c);
void vga_setfgbg(int fg, int bg);
void vga_setpos(int r, int c);
void vga_prints(char* s);
void vga_printc(int c);
void vga_writebuffer();
void vga_cls(int c);
int vga_enabled();
void vga_init();
#endif