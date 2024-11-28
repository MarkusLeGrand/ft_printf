#include "ft_printf.h"

int ft_print_string(char *str)
{
    int len = 0;

    if (!str)
        str = "(null)";
    while (str[len])
        write(1, &str[len++], 1);
    return len;
}
