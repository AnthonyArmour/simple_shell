#include "shell.h"

/**
 * script_check - checks if input is a script
 * @argc: argc
 * @argv: argv
 * @env: env
 * @my_lists: lists for env and aliases
 * @Cmd: Command
 * Return: void
 */

void script_check(int argc, char *argv[], char **env, my_ret my_lists
		  , char **Cmd)
{
	int fd;
	char *tmp = ": 0: Can't open ";

	(void)Cmd;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, tmp, _strlen(tmp));
			write(STDERR_FILENO, argv[1], _strlen(argv[1]));
			write(STDERR_FILENO, "\n", 1);
			exit(127);
		}
		my_lists = _script(fd, argv[0], env, my_lists);
		free_env(env, my_lists.free_env_list);
		free_list(my_lists.alias_List);
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

/**
 * quick_stat - stat check
 * @token: token
 * Return: stat
 */

int quick_stat(char *token)
{
	struct stat stats;
	int x = 0, sig = 0, len = _strlen(token) - 1;

	if (stat(token, &stats) == 0)
	{
		for (x = len; x >= 0; x--)
		{
			if (token[x] == '/' && token[x - 1] == '.')
				sig = 1;
		}
		if (token[0] == '/' && (token[1] == 'b'
				|| token[1] == 'u' || token[1] == 's'))
			sig = 1;
	}
	if (token[0] == '/' && (token[1] != 'b'
				&& token[1] != 'u' && token[1] != 's'))
		sig = 2;
	return (sig);
}
