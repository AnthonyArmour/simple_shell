#include "shell.h"
extern int err_Cnt;
extern int errno;

/**
 * _strtok - Returns next word of input string
 * @str: The input string
 * @index: Where we are in the input string
 * @delim: Spaces, null bytes, semicolons
 * Return: Next word of input string
 */

char *_strtok(char *str, int *index, char delim)
{
	int x = 0, y = 0;
	char *tok;

	if (!str)
		return (NULL);
	while (str[(*index)] == ' ')
	{
		if (str[(*index)] == ' ' && str[(*index) + 1] == '\0')
			return (NULL);
		(*index)++;
	}
	while (str[y + (*index)] != '\0' && str[y + (*index)] != delim)
		y++;
	tok = malloc(sizeof(char) * (y + 1));
	if (!tok)
		return (NULL);
	for (x = 0; x < y; x++)
		tok[x] = str[x + (*index)];
	tok[x] = '\0';
	*index += x;
	return (tok);
}

/**
 * _script - runs command script
 * @fd: File descriptor for script
 * @argv: Arguments
 * @env: Environment
 * Return: void
 */

ll *_script(int fd, char *argv, char **env, ll *alias_List)
{
	int x = 0, xx = 0, buflen = 0, newlen = 0;
	char *buf = NULL, tmp[1024];
	char **Cmd = NULL;
	ssize_t count;

	while ((count = read(fd, tmp, 1024)) > 0)
	{
		if (buf != NULL)
			buflen = _strlen(buf);
		newlen = buflen + count;
		buf = _realloc(buf, buflen, newlen);
		for (x = 0; x < count; x++)
		{
			buf[xx] = tmp[x];
			xx++;
		}
		buf[xx] = '\0';
	}
	for (x = 0; buf[x]; x++)
	{
		if (buf[x] == '\n')
			buf[x] = ';';
	}
	if (x != 0)
	{
		Cmd = parser1(buf, argv);
		alias_List = parser2(Cmd, argv, env, alias_List);
		for (x = 0; Cmd[x]; x++)
			free(Cmd[x]);
		free(Cmd);
	}
	return (alias_List);
}
