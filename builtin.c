#include "shell.h"

/**
 * Exits the shell with a given exit status.
 * @info: Pointer to the info_t struct.
 *
 * Return: -1 if there is an error, 0 otherwise.
 */
int my_exit(info_t *info)
{
	int exit_status = 0;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_status = _atoi(info->argv[1]);

		if (exit_status == 0 && _strcmp(info->argv[1], "0") != 0)
		{
			info->status = 2;
			print_error(info, "Invalid exit status: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return -1;
		}

		info->err_num = exit_status;
		return -2;
	}

	info->err_num = -1;
	return -2;
}

/**
 * Changes the current directory of the process.
 * @info: Pointer to the info_t struct.
 *
 * Return: 0 on success, -1 on failure.
 */
int my_cd(info_t *info)
{
	char *dir;

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
		{
			print_error(info, "HOME environment variable not set.\n");
			return -1;
		}
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			print_error(info, "OLDPWD environment variable not set.\n");
			return -1;
		}
	}
	else
		dir = info->argv[1];

	if (chdir(dir) == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(dir);
		_eputchar('\n');
		return -1;
	}

	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(NULL, 0));

	return 0;
}

/**
 * Displays help information for the shell.
 * @info: Pointer to the info_t struct.
 *
 * Return: Always 0.
 */
int my_help(info_t *info)
{
	(void)info;
	_puts("Shell Help:\n");
	_puts("  myexit [exit_status] - Exit the shell with the given status.\n");
	_puts("  mycd [directory] - Change the current directory.\n");
	_puts("  myhelp - Display help information.\n");
	return 0;
}

