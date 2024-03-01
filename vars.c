#include "shell.h"

/**
 * p_is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @q: address of current position in buff
 * Return: 1 if chain delimeter, 0 otherwise
 */

int p_is_chain(info_t *info, char *buff, size_t *q)
{
	size_t j = *q;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[j] == ';')
	{
		buff[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = j;
	return (1);
}

/**
 * p_check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @q: address of current position in buff
 * @s: starting position in buff
 * @len: length of buff
 * Return: Void
 */

void p_check_chain(info_t *info, char *buff, size_t *q, size_t s, size_t len)
{
	size_t j = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[s] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[s] = 0;
			j = len;
		}
	}

	*q = j;
}

/**
 * p_replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */

int p_replace_alias(info_t *info)
{
	int s;
	list_t *node;
	char *q;

	for (s = 0; s < 10; s++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * p_replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */

int p_replace_vars(info_t *info)
{
	int s = 0;
	list_t *node;

	for (s = 0; info->argv[s]; s++)
	{
		if (info->argv[s][0] != '$' || !info->argv[s][1])
			continue;

		if (!_strcmp(info->argv[s], "$?"))
		{
			p_replace_string(&(info->argv[s]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[s], "$$"))
		{
			p_replace_string(&(info->argv[s]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[s][1], '=');
		if (node)
		{
			p_replace_string(&(info->argv[s]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		p_replace_string(&info->argv[s], _strdup(""));

	}
	return (0);
}

/**
 * p_replace_string - replaces string
 * @o: address of old string
 * @n: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int p_replace_string(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
