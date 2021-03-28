#ifndef keyboardh
#include <stdbool.h>
#define keyboardh
struct keyboard_send;
struct keyboard_send {
    bool shift;
    bool ctrl;
    bool alt;
    unsigned char scan;
    char ascii;
};
void keyboard_listener(void* v);
void keyboard_waitchar(char c);
void keyboard_init();
#endif