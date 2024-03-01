#include "shell.h"

/**
 * p_strcpy - copies a string
 * @dst: the destination
 * @src: the source
 * Return: pointer to destination
 */

char *p_strcpy(char *dst, char *src)
{
	int i = 0;

	if (dst == src || src == 0)
		return (dst);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

/**
 * p_strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */

char *p_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * p_puts - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */

void p_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		p_putchar(str[i]);
		i++;
	}
}

/**
 * p_putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1,On error -1,
 * and errno is set appropriately.
 */

int p_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
