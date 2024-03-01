#include "shell.h"

/**
 * **p_strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @p: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **p_strtow(char *str, char *p)
{
	int a, b, q, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!p)
		p = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], p) && (is_delim(str[a + 1], p) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(str[a], p))
			a++;
		q = 0;
		while (!is_delim(str[a + q], p) && str[a + q])
			q++;
		s[b] = malloc((q + 1) * sizeof(char));
		if (!s[b])
		{
			for (q = 0; q < b; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < q; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **p_strtow2 - splits a string into words
 * @str: the input string
 * @p: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **p_strtow2(char *str, char p)
{
	int a, b, q, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != p && str[a + 1] == p) ||
		    (str[a] != p && !str[a + 1]) || str[a + 1] == p)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == p && str[a] != p)
			a++;
		q = 0;
		while (str[a + q] != p && str[a + q] && str[a + q] != p)
			q++;
		s[b] = malloc((q + 1) * sizeof(char));
		if (!s[b])
		{
			for (q = 0; q < b; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < q; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}
