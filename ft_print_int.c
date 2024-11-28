#include "ft_printf.h"

static char *ft_itoa(int n)
{
    char *str;
    int len = (n <= 0) ? 1 : 0;
    long num = n;

    num = (n < 0) ? -num : num;
    while (n && ++len)
        n /= 10;
    str = malloc(len + 1);
    if (!str)
        return NULL;
    str[len] = '\0';
    while (len--)
    {
        str[len] = num % 10 + '0';
        num /= 10;
    }
    if (str[0] == '0' && str[1] != '\0')
        str[0] = '-';
    return str;
}

int ft_print_int(int n)
{
    char *num_str = ft_itoa(n);
    int len = ft_print_string(num_str);
    free(num_str);
    return len;
}
