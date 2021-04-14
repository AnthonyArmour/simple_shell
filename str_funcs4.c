#include "shell.h"

/**
 * script_check - checks if input is a script
 * @argc: argc
 * @argv: argv
 * @env: env
 * @alias_List: list of aliases
 * @free_env_list: list of env variables to be freed
 * @Cmd: Command
 * Return: void
 */

void script_check(int argc, char *argv[], char **env, ll *alias_List,
				char *free_env_list, char **Cmd)
{
	int fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(22);
		alias_List = _script(fd, argv[0], env, alias_List, free_env_list);
		free_env(env, free_env_list);
		free_rm(Cmd, alias_List);
		exit(0);
	}
}

/**
 * comment_check - checks for command line comments
 * @buf: input string
 * Return: buf
 */

char *comment_check(char *buf)
{
	int x = 0, y = 0;

	if (buf[0] == '\n' && buf[1] == '\0')
	{
		free(buf);
		return (NULL);
	}
	for (x = _strlen(buf) - 1; x >= 0; x--)
	{
		if (buf[x - 1] != ' ' && buf[x - 1] != '\n')
		{
			buf[x] = '\n';
			break;
		}
		if (buf[x] == ' ' || buf[x] == '\n')
			buf[x] = '\0';
		if (x - 1 == 0 && (buf[x - 1] == ' ' || buf[x - 1] == '\n'))
		{
			free(buf);
			return (NULL);
		}
	}
	for (x = 0; buf[x] != '\0'; x++)
	{
		if (buf[x + 1] == '#')
		{
			buf[x] = '\n';
			buf[x + 1] = '\0';
			y = x;
			while (buf[y - 1] == ' ' || buf[y - 1] == '\\')
			{
				y--;
				if (buf[y] == '\\')
					buf[y] = ' ';
			}
			break;
		}
	}
	return (buf);
}
/**
 * cat_err2 - concats error message
 * @num: error number
 * @argv: argument
 * @var: special message
 * @token: token
 * Return: temp
 */

char *cat_err2(char *num, char *argv, char *var, char *token)
{
	int x = 0;
	char *temp = NULL, *col_space = ": ";

	temp = malloc(_strlen(argv) + 3);
	for (x = 0; argv[x]; x++)
		temp[x] = argv[x];
	temp[x] = '\0';
	_strcat(temp, col_space);

	temp = _realloc(temp, _strlen(temp) + 1,
			_strlen(temp) + _strlen(num) + 3);
	_strcat(temp, num);
	_strcat(temp, col_space);

	temp = _realloc(temp, _strlen(temp) + 1,
			_strlen(temp) + _strlen(var) + 3);
	_strcat(temp, var);
	_strcat(temp, col_space);

	temp = _realloc(temp, _strlen(temp) + 1,
			_strlen(temp) + _strlen(token) + 1);
	_strcat(temp, token);
	_strcat(temp, "\n");
	return (temp);
}
