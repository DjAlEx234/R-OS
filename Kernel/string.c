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
void string_tolower(char* s)
{
    for (int i = 0; i < string_len(s); i++)
    {
        if (s[i] >= 65 && s[i] <= 90)
            s[i] = s[i] + 32;
    }
}
void string_reverse(char* text)
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
void string_pitoa(int conv, char* yes, int base)
{
    static char val[] = "0123456789ABCDEF";
    int sign;
    if ((sign = conv) < 0) conv = -conv;
    do *yes++ = val[conv % base]; 
    while (conv /= base);
    if (sign < 0) 
        *yes++ = '-';
    *yes = '\0';
}
void string_itoa(int conv, char* yes, int base)
{
    string_pitoa(conv, yes, base);
    string_reverse(yes);
}