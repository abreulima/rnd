#include "ft_printf.h"

int id;

static int ft_putchar(char c)
{
    return write(1, &c, 1);
}

static int ft_putstr(char *s)
{
    int len = 0;
    char *copy;

    if (!s)
        s = "(null)";
    
    copy = malloc(sizeof(char) * (strlen(s) + 1));
    if (!copy)
        return 0;
    
    strcpy(copy, s);
    
    while (*copy)
        len += ft_putchar(*copy++);

    free(copy - len); // Move pointer back to free correctly
    return len;
}

static char *ft_itoa_base(long n, int base, char *digits)
{
    char *str;
    long num = (n < 0) ? -n : n;
    int len = (n < 0) ? 2 : 1;
    long temp = num;

    while (temp /= base)
        len++;
    
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return NULL;
    
    str[len] = '\0';
    while (len--)
    {
        str[len] = digits[num % base];
        num /= base;
    }
    if (n < 0)
        str[0] = '-';

    return str;
}

static int ft_putnbr(long n, int base, char *digits)
{
    char *str = ft_itoa_base(n, base, digits);
    int len = 0;

    if (str)
    {
        len = ft_putstr(str);
        free(str);
    }
    return len;
}

static int ft_putptr(unsigned long ptr)
{
    int len = 0;
    char *str = ft_itoa_base(ptr, 16, "0123456789abcdef");

    len += ft_putstr("0x");
    if (str)
    {
        len += ft_putstr(str);
        free(str);
    }
    return len;
}

static int handle_conversion(char spec, va_list args)
{
    if (spec == 'c')
        return ft_putchar(va_arg(args, int));
    else if (spec == 's')
        return ft_putstr(va_arg(args, char *));
    else if (spec == 'p')
        return ft_putptr(va_arg(args, unsigned long));
    else if (spec == 'd' || spec == 'i')
        return ft_putnbr(va_arg(args, int), 10, "0123456789");
    else if (spec == 'u')
        return ft_putnbr(va_arg(args, unsigned int), 10, "0123456789");
    else if (spec == 'x')
        return ft_putnbr(va_arg(args, unsigned int), 16, "0123456789abcdef");
    else if (spec == 'X')
        return ft_putnbr(va_arg(args, unsigned int), 16, "0123456789ABCDEF");
    else if (spec == '%')
        return ft_putchar('%');
    return 0;
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);
    while (*format)
    {
        if (*format == '%' && *(format + 1))
        {
            format++;
            count += handle_conversion(*format, args);
        }
        else
            count += ft_putchar(*format);
        format++;
    }
    va_end(args);
    return count;
}
