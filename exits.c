#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @i: the amount of characters to be copied
 * Return: the concatenated string
 */

char *p_strncpy(char *dest, char *src, int i)
{
	int a, b;
	char *p = dest;

	a = 0;
	while (src[a] != '\0' && a < i - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < i)
	{
		b = a;
		while (b < i)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (p);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @i: the amount of bytes to be maximally used
 * Return: the concatenated string
 */

char *p_strncat(char *dest, char *src, int i)
{
	int a, b;
	char *p = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < i)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < i)
		dest[a] = '\0';
	return (p);
}

/**
 * _strchr - locates a character in a string
 * @p: the string to be parsed
 * @c: the character to look for
 * Return: (p) a pointer to the memory area p
 */
 
char *p_strchr(char *p, char c)
{
	do {
		if (*p == c)
			return (p);
	} while (*p++ != '\0');

	return (NULL);
}
