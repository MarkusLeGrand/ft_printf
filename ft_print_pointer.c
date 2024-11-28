#include "ft_printf.h"

int ft_print_pointer(void *ptr)
{
    unsigned long long addr = (unsigned long long)ptr;
    int printed_chars = 0;

    printed_chars += write(1, "0x", 2);
    printed_chars += ft_print_number_base(addr, "0123456789abcdef");
    return printed_chars;
}
