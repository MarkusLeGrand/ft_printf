#include "ft_printf.h"

int handle_format(const char *format, va_list args)
{
    int printed_chars;

    printed_chars = 0;
    while (*format)
    {
        if (*format == '%' && *(format + 1))
        {
            format++;
            printed_chars += handle_conversion(*format, args);
        }
        else
        {
            write(1, format, 1);
            printed_chars++;
        }
        format++;
    }
    return printed_chars;
}
