#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

void ft_putstr(char *str ,int *len)
{
	if(!str) //str adresi bossa
		str = "(null)";
	while(*str) //poinetrin gosterdigi veri varken
		*len += write(1, str++, 1);
}

void ft_putnbr(long long int nbr, int base, int  *len)
{
	char *hex = "0123456789abcdef";

	if( nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if(nbr > base)
		ft_putnbr((nbr/base), base, len);
	*len += write(1, &hex[nbr % base], 1);
}

int ft_printf(const char *format, ...)
{
	//declare va_list
	va_list	ap;
	//start the va;
	va_start(ap, format);
	int len = 0;
	//karakterimiz % ise ve sonraki karakter 's' 'd' 'x' ise
	while(*format)
	{
		//*(format+1) anlami bir sonraki  byte in degerine bakiyoruz.
		if(*(format) == '%' && ( *(format+1)== 's' || *(format+1)== 'd' || *(format+1)== 'x') )
		{
			//bu format pointerini bir sonraki array elemanina gecirir.
			format++;
			if(*format == 's')
				ft_putstr(va_arg(ap, char *), &len);
			else if(*format == 'd')
				ft_putnbr((long long int)va_arg(ap, int), 10, &len);
			else if(*format == 'x')
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

/*
*(format + 1) ifadesinin pointer'ı bir sonraki karaktere taşımaması ve sadece
pointer'ın gösterdiği konumdan bir sonraki karakteri göstermesi, C ve
C++'daki pointer aritmetiğinin temel prensipleriyle alakalıdır.
Bu durum, karakter boyutu ve dizi (array) kavramı ile doğrudan ilişkilidir.

C ve C++'da, pointer aritmetiği, pointer'ın gösterdiği veri türünün boyutunu
dikkate alır. char türündeki bir pointer (char *), char türünün boyutu olan
1 byte ilerler. Yani, format + 1 ifadesi, format pointer'ını bellekte bir
byte ilerletir, bu da genellikle bir sonraki karaktere denk gelir,
çünkü char tipindeki veriler bellekte 1 byte yer kaplar.

*(format + 1) ifadesinde iki işlem gerçekleşir:

Pointer Aritmetiği (format + 1): format pointer'ı, bellekte bir sonraki
char konumuna (yani bir sonraki karaktere) ilerletilir. Ancak bu,
format'ın kendisi üzerinde bir değişiklik yapmaz; sadece bir sonraki konumu hesaplar.

Dereferans Operatörü (*): format + 1 ifadesi tarafından elde edilen yeni adres,
dereferans operatörü (*) ile dereferans edilir. Bu, yeni adresteki karakterin değerini alır.

Örnek olarak, eğer format "hello" stringinin 'h' karakterini gösteriyorsa,
*(format + 1) 'e' karakterini gösterir. Ancak format'ın kendisi hala
'h' karakterini göstermeye devam eder.

Bu nedenle, *(format + 1) ifadesi sadece bir sonraki karakteri gösterir ve
format pointer'ının kendisini değiştirmez.
*/