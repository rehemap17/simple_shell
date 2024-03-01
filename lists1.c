#include "shell.t"

/**
 * p_list_len - determines length of linked list
 * @t: pointer to first node
 * Return: size of list
 */

size_t p_list_len(const list_t *t)
{
	size_t j = 0;

	while (t)
	{
		t = t->next;
		j++;
	}
	return (j);
}

/**
 * p_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */

char **p_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = p_list_len(head), j;
	char **strs;
	char *str;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < j; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 * p_print_list - prints all elements of a list_t linked list
 * @t: pointer to first node
 * Return: size of list
 */

size_t p_print_list(const list_t *t)
{
	size_t j = 0;

	while (t)
	{
		_puts(convert_number(t->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(t->str ? t->str : "(nil)");
		_puts("\n");
		t = t->next;
		j++;
	}
	return (j);
}

/**
 * p_node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *p_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * p_get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */

ssize_t p_get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
