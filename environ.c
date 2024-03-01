#include "shell.h"

/**
 * p_myenv - prints the current environment
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int p_myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * p_getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * @name: env var name
 * Return: the value
 */

char *p_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * p_mysetenv - Initialize a new environment variable,
 * or modify an existing one.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 *  Return: Always 0
 */

int p_mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * p_myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int p_myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * p_populate_env_list - populates env linked list
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int p_populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
