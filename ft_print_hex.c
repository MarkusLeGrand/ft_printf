#include "ft_printf.h"

int ft_print_hex(unsigned int n, int uppercase)
{
    if (uppercase)
        return ft_print_number_base(n, "0123456789ABCDEF");
    else
        return ft_print_number_base(n, "0123456789abcdef");
}
