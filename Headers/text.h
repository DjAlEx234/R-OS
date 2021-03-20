#ifndef texth
#define texth
enum colors;
enum colors {
  Black = 0,
  Blue = 1,
  Green = 2,
  Cyan = 3,
  Red = 4,
  Magenta = 5,
  Brown = 6,
  Light_Gray = 7,
  Dark_Gray = 8,
  Light_Blue = 9,
  Light_Green = 10,
  Light_Cyan = 11,
  Light_Red = 12,
  Light_Magenta = 13,
  Light_Brown = 14,
  White = 15,
};
void text_init(void);
void text_printc(char c);
void text_prints(char* s);
void text_clear(enum colors color);
void text_scroll();
void text_setpos(int new_row, int new_column);
void text_setfgbg(int new_fg, int new_bg);
int text_get_column();
int text_get_row();
int text_cmp(char a[], char b[]);
void text_itoa(int conv, char text[], int base);
int string_len(const char* string);
#endif