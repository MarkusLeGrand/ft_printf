#include "ft_printf.h"
#include <stdio.h>

int main()
{
    ft_printf("Char: %c\n", 'A');
    ft_printf("String: %s\n", "Hello, World!");
    ft_printf("Pointer: %p\n", (void *)123456);
    ft_printf("Decimal: %d\n", 42);
    ft_printf("Unsigned: %u\n", 42);
    ft_printf("Hex (lower): %x\n", 255);
    ft_printf("Hex (upper): %X\n", 255);
    ft_printf("Percent: %%\n");

    return 0;
}
