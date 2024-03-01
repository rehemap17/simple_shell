#include "shell.h"

/**
 * p_interactive - returns true if shell is p_interactive mode
 * @info: struct address
 * Return: 1 if p_interactive mode, 0 otherwise
 */

int p_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readflds <= 2);
}

/**
 * p_is_delim - checks if character is a delimeter
 * @k: the char to check
 * @dlm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int p_is_delim(char k, char *dlm)
{
	while (*dlm)
		if (*dlm++ == k)
			return (1);
	return (0);
}

/**
 *p_isalpha - checks for alphabetic character
 *@k: The character to input
 *Return: 1 if k is alphabetic, 0 otherwise
 */

int p_isalpha(int k)
{
	if ((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *p_atoi - converts a string to an integer
 *@p: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int p_atoi(char *p)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  p[i] != '\0' && flag != 2; i++)
	{
		if (p[i] == '-')
			sign *= -1;

		if (p[i] >= '0' && p[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (p[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
