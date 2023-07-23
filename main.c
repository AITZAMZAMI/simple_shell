#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT }; // Initialize the info_t struct.
	int fd = 2; // Initialize a file descriptor.

	// Use inline assembly to manipulate the file descriptor.
	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	// Check if a command file is provided as an argument.
	if (ac == 2)
	{
		// Attempt to open the command file for reading.
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			// Handle different error scenarios.
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd; // Set the read file descriptor in the info struct.
	}

	populate_env_list(info); // Populate the environment list from the system's environment.
	read_history(info); // Read the command history from the history file.
	hsh(info, av); // Start the shell (main loop).
	return (EXIT_SUCCESS); // Exit with success status.
}

