#include "shell.h"

/**
 * path_check - finds directory paths
 * @paths: directory paths
 * Return: directory path index
 */

int path_check(char **paths)
{
	int x = -1;
	struct stat stats;

	for (x = 0; paths[x]; x++)
	{
		if (stat(paths[x], &stats) == 0)
			break;
	}
	if (!paths[x])
		x = -1;
	return (x);
}

/**
 * append_paths - appends command to the path
 * @token: command
 * @paths: paths!
 * Return: appended paths
 */

char **append_paths(char *token, char **paths)
{
	int x = 0;

	for (x = 0; paths[x]; x++)
	{
		paths[x] = _realloc(paths[x], _strlen(paths[x]),
				    _strlen(paths[x]) + _strlen(token) + 2);
		paths[x] = str_mul_cat(paths[x], token, "/");
	}
	return (paths);
}

/**
 * str_mul_cat - concatenates multiple strings
 * @dest: destination string
 * @str1: first string
 * @str2: second string
 * Return: concatenated string
 */

char *str_mul_cat(char *dest, char *str2, char *str1)
{
	if (dest && str2 && str1)
	{
		strcat(dest, str1);
		strcat(dest, str2);
	}
	return (dest);
}

/**
 * path_idx - finds path variable in environment
 * @env: environment
 * Return: path variable index
 */

int path_idx(char **env)
{
	int x = 0;

	while (env[x])
	{
		if (strncmp(env[x], "PATH=", 5) == 0)
			break;
		x++;
	}
	return (x);
}

/**
 * get_size - gets number of delimiters
 * @str: string to evaluate
 * @delim: delimiters
 * Return: number of delimiters
 */

size_t get_size(char *str, char delim)
{
	size_t x = 0, count = 0;

	for (x = 0; str[x]; x++)
	{
		if (str[x] == delim || str[x + 1] == '\0')
			count++;
	}
	return (count);
}
