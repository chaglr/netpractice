#include <stdarg.h>
#include <unnistd.h>

int ft_printf(const char *format, ... )
{
	va_list	ap;
	va_start(ap, format);
	int len = 0;

	while(*format)
	{
		if((*format == '%') && ((*(format+1) == 's') ||(*(format+1) == 'd') || (*(format+1) == 'x')))
		{
			format++;
			if(*format == 's')
				put_str();
			else if(*format == 'd')
				put_digit();
			else if (*format == 'x')
				put_digit();
		}
		else
			len += write(1, format, 1);
		format++;
	}
	return (va_end(ap), len)
}