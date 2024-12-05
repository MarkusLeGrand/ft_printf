#include "ft_printf.h"
#include <stdarg.h>

int ft_printf(const char *format, ...)
{
    va_list args;
    int     printed_chars;

    printed_chars = 0;
    va_start(args, format);
    printed_chars = handle_format(format, args); // Helper function to handle input
    va_end(args);

    return printed_chars;
}
