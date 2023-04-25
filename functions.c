#include "main.h"
/** print char  **/

/*
 * print_char - prints a char
 * @types: List a of arguments
 * @buffer: buffer array to  handle print
 * @flags: calculates active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/** print a string  **/
/**
  * print_string - print a string
  * @types: List a of arguments
  * @buffer: buffer array to  handle print
  * @flags: calculates active flags
  * @width: width
  * @precision: precision specification
  * @size: size specifier
  * Return: Number of chars printed
  */
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if(str == NULL)
	{
		str = "(null)";
		if(precision >= 6)
			str = "  ";
	}

	while(str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for(i = width - length; i> 0; i--)
				write(1, "",1);
			return (width);
		}
		else
		{
			for (i = width - length; i> 0; i--)
				write(1,"",1);
			write(1,&str[0], length);
			return (width);

		}
	}
	return (write(1, str, length));
}
/** print percent sign  **/
/**
  * print_percent - prints a percent sign
  * @types: List a of arguments
  * @buffer: Buffer array to handle print
  * @flags: Calculates active flags
  * @width: Width
  * @precision: Precision specification
  * @size: Size specifier
  * Return: Number of chars printed
  */
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return(write(1,"%%",1));
}

/** print int **/
/**
  * print_int - print int
  * @types: List a of arguments
  * @buffer: Buffer array to handle print
  * @flags: Calculates active flag
  * @width: Width
  * @precision: Precision specification
  * @size: Size specifier
  * Return: Number of chars printed
 */
int print_int(va_list types,char buffer[], int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;
	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE -1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = ((unsigned long int)(-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return(write_number(is_negative, i, buffer, flags, width, precision, size));
}

/** print binary **/
/**
 * print_binary - print an unsigned number
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flag
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed1
 */
int print_binary(va_list types,char buffer[], int flags, int width, int precision, int size)
{
	unsigned int s, u, m, sum;
	unsigned int x[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	s = va_arg(types, unsigned int);
	u = 2147483648; /*(2^31)*/
	x[0] = s / u;
	for (m = 1; m < 32; m++)
	{
		u /= 2;
		x[m] = (s / u) % 2;
	}
	for (m = 0, sum = 0, count = 0; m < 32; m++)
	{
		sum += x[m];
		if (sum || m == 31)
		{
			char z = '0' + x[m];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
