#ifndef cmdh
#define cmdh
void cmd_run(char* cmd);
void cmd_mode(char* mode);
void cmd_ptr(void* pc, void* ps, void* fb, void* pos);
void cmd_getposptr(int (*getr)(), int (*getc)());
#endif