#include <stdint.h>
static inline uint8_t inb(uint16_t port)
{
    uint8_t returned;
    asm volatile ("inb %1, %0" : "=a"(returned) : "Nd"(port));
    return returned;
}
static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd" (port));
}