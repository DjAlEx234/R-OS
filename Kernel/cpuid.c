#include <stdint.h>
#include <cpuid.h>
char* cpuid_string()
{
    static int a[4];
    __asm__("mov $0x0, %eax\n\t");
    __asm__("cpuid\n\t");
    __asm__("mov %%ebx, %0\n\t":"=r" (a[0]));
    __asm__("mov %%edx, %0\n\t":"=r" (a[1]));
    __asm__("mov %%ecx, %0\n\t":"=r" (a[2]));
    a[3] = 0;
    return &a;
}
int cpuid_is64bit()
{
    uint32_t input;
    __asm__("mov $0x80000001, %eax\n\t");
    __asm__("cpuid\n\t");
    __asm__("mov %%edx, %0\n\t":"=r" (input));
    return (int)(input >> 29);
}