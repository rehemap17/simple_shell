#include "shell.h"

/**
 * p_input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */

ssize_t p_input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, p_sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = p_getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * p_get_input - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */

ssize_t p_get_input(info_t *info)
{
	static char *buf;
	static size_t i, q, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = p_input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		q = i;
		p = buf + i;

		check_chain(info, buf, &q, i, len);
		while (q < len)
		{
			if (is_chain(info, buf, &q))
				break;
			q++;
		}

		i = q + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * p_read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */

ssize_t p_read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * p_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: j
 */

int p_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t q;
	ssize_t r = 0, j = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		j = *length;
	if (i == len)
		i = len = 0;

	r = p_read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	q = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, j, j ? j + q : q + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (j)
		_strncat(new_p, buf + i, q - i);
	else
		_strncpy(new_p, buf + i, q - i + 1);

	j += q - i;
	i = q;
	p = new_p;

	if (length)
		*length = j;
	*ptr = p;
	return (j);
}

/**
 * p_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */

void p_sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
