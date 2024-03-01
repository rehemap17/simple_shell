#include "shell.h"

/**
 * p_memset - fills memory with a constant byte
 * @mem: the pointer to the memory area
 * @byt: the byte to fill *mem with
 * @num: the amount of bytes to be filled
 * Return: (mem) a pointer to the memory area mem
 */

char *p_memset(char *mem, char byt, unsigned int num)
{
	unsigned int j;

	for (j = 0; j < num; j++)
		mem[j] = byt;
	return (mem);
}

/**
 * p_ffree - frees a string of strings
 * @pp: string of strings
 */

void p_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * p_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @o_size: byte size of previous block
 * @n_size: byte size of new block
 * Return: pointer to da ol'block nameen.
 */

void *p_realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	char *p;

	if (!ptr)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr), NULL);
	if (n_size == o_size)
		return (ptr);

	p = malloc(n_size);
	if (!p)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		p[o_size] = ((char *)ptr)[o_size];
	free(ptr);
	return (p);
}
