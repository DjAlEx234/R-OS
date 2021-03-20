extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void irq32();
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
#include <stdint.h>
#include <stddef.h>
#include "int.h"
#include "inoutb.h"
#include "text.h"
void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));
struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));
struct idt_entry idt[256];
struct idt_ptr idtp;
extern void idt_load();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}
void isr_install()
{
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);
}
void irq_install()
{
	irq_remap();
	idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}
void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}
void idt_install()
{
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int) &idt;
    memset(&idt, 0, sizeof(struct idt_entry) * 256);
    idt_load();
}
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));
struct gdt_entry gdt[3];
struct gdt_ptr gp;
extern void gdt_flush();
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}
void gdt_install()
{
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int) &gdt;
    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_flush();
}
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}
void irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r);
    handler = irq_routines[r->int_no - 32];
    if (handler)
        handler(r);
    if (r->int_no >= 40)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}
int isr = 0;
void error_handler(char* errortext)
{
  text_setfgbg(0, 4);
  text_prints("\nHandler has been called!");
  text_prints(errortext);
}
char *tips[32] = {
    "DIVIDE BY ZERO",
    "DEBUG",
    "NON MASKABLE INTERRUPT",
    "BREAKPOINT",
    "OVERFLOW",
    "BOUND RANGE EXCEEDED",
    "IVALID OPCODE",
    "DEVICE NOT AVAILABLE",
    "DOUBLE FAULT",
    "(should not be possible)",
    "INVALID TSS",
    "SEGMENT NOT PRESENT",
    "STACK-SEGMENT FAULT",
    "GENERAL PROTECTION FAULT",
    "PAGE FAULT",
    "RESERVED",
    "X87 FPE",
    "ALIGNMENT CHECK",
    "MACHINE CHECK",
    "SIMD FPE",
    "VIRTUALIZATION EXCEPTION",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "SECURITY EXCEPTION",
    "RESERVED",
};
#include "string.h"
void dump_registers(struct regs *uhoh)
{
    text_setfgbg(7, 4);
    text_prints("GS: ");
    text_prints(string_itoa(uhoh->gs, 16));
    text_prints("\nFS: ");
    text_prints(string_itoa(uhoh->fs, 16));
    text_prints("\nES: ");
    text_prints(string_itoa(uhoh->es, 16));
    text_prints("\nDS: ");
    text_prints(string_itoa(uhoh->ds, 16));
    text_prints("\nEDI: ");
    text_prints(string_itoa(uhoh->edi, 16));
    text_prints("\nESI: ");
    text_prints(string_itoa(uhoh->esi, 16));
    text_prints("\nEBP: ");
    text_prints(string_itoa(uhoh->ebp, 16));
    text_prints("\nESP: ");
    text_prints(string_itoa(uhoh->esp, 16));
    text_prints("\nEBX: ");
    text_prints(string_itoa(uhoh->ebx, 16));
    text_prints("\nEDX: ");
    text_prints(string_itoa(uhoh->edx, 16));
    text_prints("\nECX: ");
    text_prints(string_itoa(uhoh->ecx, 16));
    text_prints("\nInterrupt Number: ");
    text_prints(string_itoa(uhoh->int_no, 16));
    text_prints("\nError Code: ");
    text_prints(string_itoa(uhoh->err_code, 16));
    text_prints("\nEIP: ");
    text_prints(string_itoa(uhoh->eip, 16));
    text_prints("\nCS: ");
    text_prints(string_itoa(uhoh->cs, 16));
    text_prints("\nEFLAGS: ");
    text_prints(string_itoa(uhoh->eflags, 16));
    text_prints("\nUser ESP: ");
    text_prints(string_itoa(uhoh->useresp, 16));
    text_prints("\nSS: ");
    text_prints(string_itoa(uhoh->ss, 16));
}
void asm_error(struct regs *r)
{
    text_setpos(0, 0);
    text_setfgbg(7, 4);
    dump_registers(r);
    text_printc('\n');
    text_prints(tips[r->int_no]);
    error_handler("\nISR CALLED!");
    asm ("cli");
    while (1) {}
}
void interrupt_install()
{
    gdt_install();
    idt_install();
    irq_install();
    isr_install();
    asm("sti");
}