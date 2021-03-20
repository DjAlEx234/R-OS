#ifndef interrupth
#define interrupth
struct regs;
struct regs
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};
void interrupt_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void irq_remove_handler(int irq);
void error_handler(char* errortext);
#endif