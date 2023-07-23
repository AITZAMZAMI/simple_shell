#include "shell.h"

/**
 * Copies a string up to 'n' characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: A pointer to the concatenated string.
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	while (i < n)
		dest[i++] = '\0';

	return dest;
}

/**
 * Concatenates two strings up to 'n' characters from the source string.
 * @dest: The first string.
 * @src: The second string.
 * @n: The number of bytes to be maximally used.
 *
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, const char *src, int n)
{
	int dest_len = _strlen(dest);
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return dest;
}

/**
 * Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area where the character 'c' occurs.
 *         If the character is not found, return NULL.
 */
char *_strchr(const char *s, char c)
{
	do {
		if (*s == c)
			return (char *)s;
	} while (*s++ != '\0');

	return NULL;
}

