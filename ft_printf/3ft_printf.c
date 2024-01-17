#include <stdarg.h>
#include <unistd.h>

void ft_putstr(char *str, int *len)
{
	if(!str)
		str = "(null)";
	while(*str)
	*len += write (1, str++, 1);

}

void ft_putnbr(long long int nbr, int base, int *len)
{
	char *hex = "0123456789abcdef";
	if(nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if(nbr >= base)
		ft_putnbr((nbr / base) , base , len);
	*len += write(1, &hex[nbr % base], 1);
}


int ft_printf(char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int len = 0;

	while(*format)
	{
		if(*format == '%' && (*(format+1) == 's' || *(format+1) == 'd' || *(format+1) == 'x') )
		{
			format++;
			if(*format == 's')
				ft_putstr(va_arg(ap, char *), &len);
			if(*format == 'd')
				ft_putnbr((long long int)va_arg(ap,int), 10, &len);
			if(*format == 'x')
				ft_putnbr((long long int)va_arg(ap, unsigned int), 16, &len);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	return(va_end(ap), len);
}

int main(void)
{
	int i = 0;
	i = ft_printf("%s %d, %x %g", "HELLO", 42, 42);
	ft_printf("\n%d", i);
	return(0);
}