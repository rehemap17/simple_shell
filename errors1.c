#include "shell.h"

/**
 * p_erratoi - converts a string to an integer
 * @p: the string to be converted
 * Return: 0 if no numbers in string,
 * converted number otherwise -1 on error.
 */

int p_erratoi(char *p)
{
	int j = 0;
	unsigned long int result = 0;

	if (*p == '+')
		p++;
	for (j = 0;  p[j] != '\0'; j++)
	{
		if (p[j] >= '0' && p[j] <= '9')
		{
			result *= 10;
			result += (p[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * p_print_error - prints an error message
 * @info: the parameter & return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string,
 * converted number otherwise -1 on error.
 */

void p_print_error(info_t *info, char *errstr)
{
	_eputs(info->fname);
	_eputs(": ");
	p_print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * p_print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @flds: the filedescriptor to write
 * Return: number of characters printed
 */

int p_print_d(int input, int flds)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (flds == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * p_convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: arguments flags
 * Return: string
 */

char *p_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * p_remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address string to modify
 * Return: Always 0;
 */

void p_remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
