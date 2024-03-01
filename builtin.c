#include "shell.h"

/**
 * p_myexit - exits the shell
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */

int p_myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = p_erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			p_print_error(info, "Illegal number: ");
			p_eputs(info->argv[1]);
			p_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * p_mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int p_mycd(info_t *info)
{
	char *p, *dir, buffer[1024];
	int chdir_ret;

	p = getcwd(buffer, 1024);
	if (!p)
		p_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = p_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = 
				chdir((dir = p_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (p_strcmp(info->argv[1], "-") == 0)
	{
		if (!p_getenv(info, "PPWD="))
		{
			_puts(p);
			p_putchar('\n');
			return (1);
		}
		_puts(p_getenv(info, "PPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = p_getenv(info, "PPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		p_setenv(info, "PPWD", p_getenv(info, "PWD="));
		p_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * p_myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int p_myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function missing\n");
	if (0)
		_puts(*arg_array);
	return (0);
}
