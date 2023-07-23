#include "shell.h"

/**
 * Displays the history list, one command per line, preceded
 * with line numbers, starting at 0.
 * @info: Pointer to the info_t struct.
 *
 * Return: Always 0.
 */
int my_history(info_t *info)
{
	list_t *node = info->history;
	unsigned int line_number = 0;

	while (node)
	{
		_printf("%u ", line_number);
		_puts(node->str);
		_puts("\n");
		node = node->next;
		line_number++;
	}

	return 0;
}

/**
 * Sets an alias to a string.
 * @info: Pointer to the info_t struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return 1;
	if (!*++p)
		return unset_alias(info, str);

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * Unsets an alias.
 * @info: Pointer to the info_t struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return 1;
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias), get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return ret;
}

/**
 * Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *p, *a;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return 0;
	}

	return 1;
}

/**
 * Mimics the alias builtin (man alias).
 * @info: Pointer to the info_t struct.
 *
 * Return: Always 0.
 */
int my_alias(info_t *info)
{
	int i;
	char *p;
	list_t *node;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return 0;
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return 0;
}

