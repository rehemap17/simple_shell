#include "shell.h"

/**
 * p_strlen - returns the length of a string
 * @s: the string whose length to check
 * Return: integer length of string
 */

int p_strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * p_strcmp - performs lexicogarphic comparison of two strangs.
 * @sf1: the first strng
 * @ss2: the second strng
 * Return: negative if sf1 < ss2, positive if sf1 > ss2, zero if sf1 == ss2
 */

int p_strcmp(char *sf1, char *ss2)
{
	while (*sf1 && *ss2)
	{
		if (*sf1 != *ss2)
			return (*sf1 - *ss2);
		sf1++;
		ss2++;
	}
	if (*sf1 == *ss2)
		return (0);
	else
		return (*sf1 < *ss2 ? -1 : 1);
}

/**
 * p_starts_with - checks if ndle starts with haystack
 * @hystack: string to search
 * @ndle: the substring to find
 * Return: address of next char of haystack or NULL
 */
 
char *p_starts_with(const char *hystack, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hystack++)
			return (NULL);
	return ((char *)hystack);
}

/**
 * p_strcat - concatenates two strings
 * @dst: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */

char *p_strcat(char *dst, char *src)
{
	char *ret = dst;

	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (ret);
}
