#include <stdint.h>
int string_len(const char* string)
{
	int len = 0;
	while (string[len])
		len++;
	if (string[0] == 0)
		return len - 1;
	return len;
}
int string_cmp(char a[], char b[])
{
    int len = string_len(b);
    for (int c = 0; c != len; c++)
        if (a[c] != b[c])
            return 0;
    return 1;
}
void string_reverse(char text[])
{
    int a, b;
    char c;
    for (a = 0, b = string_len(text)-1; a < b; a++, b--)
    {
        c = text[a];
        text[a] = text[b];
        text[b] = c;
    }
}
char* string_itoa(int conv, int base)
{
    static char val[] = "0123456789ABCDEF";
    char* yes = 0;
    int sign;
    if ((sign = conv) < 0) conv = -conv;
    do *yes++ = val[conv % base]; 
    while (conv /= base);
    if (sign < 0) 
        *yes++ = '-';
    *yes = '\0';
    string_reverse(yes);
    return yes;
}