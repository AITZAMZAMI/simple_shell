#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st) != 0)
		return 0;

	if (S_ISREG(st.st_mode))
		return 1;

	return 0;
}

/**
 * dup_chars - Duplicates characters from a given range in the path string.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = '\0';
	return buf;
}

/**
 * find_path - Finds the given cmd in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd if found, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return NULL;

	if (_strlen(cmd) > 2 && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return cmd;
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcpy(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (is_cmd(info, path))
				return path;

			if (!pathstr[i])
				break;

			curr_pos = i + 1;
		}
		i++;
	}

	return NULL;
}

