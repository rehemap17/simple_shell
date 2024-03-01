#include "shell.h"

/**
 * p_is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @paths: path to the file
 * Return: 1 if true, 0 otherwise
 */

int p_is_cmd(info_t *info, char *paths)
{
	struct stat st;

	(void)info;
	if (!paths || stat(paths, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * p_dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *p_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * p_find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *p_find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *paths;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (p_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			paths = p_dup_chars(pathstr, curr_pos, i);
			if (!*paths)
				_strcat(paths, cmd);
			else
			{
				_strcat(paths, "/");
				_strcat(paths, cmd);
			}
			if (p_is_cmd(info, paths))
				return (paths);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
