#include <stdarg.h>
#include <unistd.h>

int pt_d(long int d, int base)
{
	char *c = "0123456789abcdef";
	int res = 0;
	if (d < 0)
	{
		res += write(1, "-", 1);
		d *= -1;
	}
	if (d >= base)
		res += pt_d(d / base, base);
	res += write(1, &c[d % base], 1);
	return (res);
}

int	pt_s(char *s)
{
	int res = 0;
	if (!s)
		s = "(null)";
	while (*s)
		res += write(1, s++, 1);
	return (res);
}

int ft_printf(const char *s, ...)
{
	va_list ptr;
	int res = 0;
	va_start(ptr, s);
	while(*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s == 's')
				res += pt_s(va_arg(ptr, char *));
			else if (*s == 'd')
				res += pt_d((long int)va_arg(ptr, int), 10);
			else if (*s == 'x')
				res += pt_d((long int)va_arg(ptr, unsigned int), 16);
			if (*s != 's' && *s != 'd' && *s != 'x')
			{
				res+= write(1, "%", 1);
				res+= write(1, s, 1);
			}
		}
		else
			res += write(1, s, 1);
		s++;
	}
	va_end(ptr);
	return (res);
}
int main(void)
{
	int i = 0;
	i = ft_printf("%s %d, %x %g", "HELLO", 42, 42);
	//		ft_printf("%s", 23);
	ft_printf("\n%d", i);
	return(0);
}