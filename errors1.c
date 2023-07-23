#include "shell.h"

/**
 * Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number if successful, -1 on error.
 */
int convert_to_integer(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
	}

	return (int)result;
}

/**
 * Prints an error message.
 * @info: Pointer to the info_t struct.
 * @estr: String containing the specified error type.
 *
 * Return: Nothing.
 */
void print_error_message(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * Prints a decimal (integer) number in base 10.
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
	int (*output_char)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		output_char = _eputchar;

	if (input < 0)
	{
		absolute_value = (unsigned int)-input;
		output_char('-');
		count++;
	}
	else
		absolute_value = (unsigned int)input;

	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			output_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	output_char('0' + current);
	count++;

	return count;
}

/**
 * Converts a number to a string.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: The converted string.
 */
char *convert_number_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return ptr;
}

/**
 * Replaces the first instance of '#' with '\0' in the string.
 * @buf: The address of the string to modify.
 *
 * Return: Nothing.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}

