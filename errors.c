#include "shell.h"

/**
 *p_eputs - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */

void p_eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		p_eputchar(str[j]);
		j++;
	}
}

/**
 * p_eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1, On error -1,
 * and errno is set appropriately.
 */

int p_eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * p_putflds - writes the character c to given flds
 * @c: The character to print
 * @flds: The filedescriptor to write
 * Return: On success 1,On error -1,
 * and errno is set appropriately.
 */
 
int p_putflds(char c, int flds)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(flds, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 *p_putsflds - prints an input string
 * @str: the string to be printed
 * @flds: the filedescriptor to write
 * Return: the number of chars put
 */

int p_putsflds(char *str, int flds)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += p_putflds(*str++, flds);
	}
	return (j);
}
