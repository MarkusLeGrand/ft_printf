#include "ft_printf.h"

int ft_print_unsigned(unsigned int n)
{
    return ft_print_number_base(n, "0123456789");
}
