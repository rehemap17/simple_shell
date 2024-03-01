#include "shell.h"

/**
 * p_myhistory - displays the history list, one command by line,
 * preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int p_myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * p_unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 and 1 on error
 */

int p_unset_alias(info_t *info, char *str)
{
	char *p, q;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	q = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = q;
	return (ret);
}

/**
 * p_set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 and 1 on error
 */

int p_set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (p_unset_alias(info, str));

	p_unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * p_print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 and 1 on error
 */

int p_print_alias(list_t *node)
{
	char *p = NULL, *c = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (c = node->str; c <= p; c++)
		_putchar(*c);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * p__myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int p__myalias(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			p_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = _strchr(info->argv[j], '=');
		if (p)
			p_set_alias(info, info->argv[j]);
		else
			p_print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
