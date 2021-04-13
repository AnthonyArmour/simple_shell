#include "shell.h"
extern int errno;

/**
 * builtin - checks if command is builtin
 * @tokes: command string
 * @argv: argv 0
 * @env: environment
 * Return: 0 if not builtin
 */

int builtin(char **tokes, char *argv, char **env)
{
	int x = 0, ret = 0;

	b_in built_in[] = {
		{"exit", my_exit}, {"setenv", _setenv}, {"env", b_env},
		{"unsetenv", _unsetenv}, {"cd", _cd}, {NULL, NULL}
	};

	for (x = 0; built_in[x].var; x++)
	{
		if ((strcmp(tokes[0], built_in[x].var)) == 0)
		{
			built_in[x].f(tokes, argv, env);
			ret++;
		}
	}

	return (ret);
}

/*
{"help", _help}
void _help(char **tokes, char *argv, char **env)
{
//something like this!
	{"exit", my_exit}, {"setenv", _setenv}, {"env", b_env},
	{"unsetenv", _unsetenv}, {"help", _help}, {NULL, NULL}
}
*/

/**
 * _setenv - sets environment
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * Return: int
 */

int _setenv(char **tokes, char *argv, char **env)
{
	int x = 0;
	char *tmp;

	(void)argv;
	while (env[x])
	{
		if (strncmp(env[x], tokes[1], _strlen(tokes[1])) == 0)
			break;
		x++;
	}
	if (env[x] != NULL)
	{
		tmp = str_mul_cat(tokes[1], tokes[2], "=");
		env[x] = _strdup(tmp);
	}
	else
	{
		tmp = str_mul_cat(tokes[1], tokes[2], "=");
		env[x] = _strdup(tmp);
		env[x + 1] = NULL;
	}
	return (1);
}

/**
 * _unsetenv - unsets env var
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * Return: int
 */

int _unsetenv(char **tokes, char *argv, char **env)
{
	int x = 0;

	(void)argv;
	while (env[x])
	{
		if (strncmp(env[x], tokes[1], _strlen(tokes[1])) == 0)
			break;
		x++;
	}
	if (env[x] != NULL)
	{
		free(env[x]);
		while (env[x + 1] != NULL)
		{
			env[x] = env[x + 1];
			x++;
		}
		env[x] = env[x + 1];
	}
	return (1);
}

/**
 * b_env - env builtin cmd
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * Return: int
 */

int b_env(char **tokes, char *argv, char **env)
{
	int x = 0;
	(void)argv;
	(void)tokes;
	for (x = 0; env[x]; x++)
	{
		write(STDOUT_FILENO, env[x], _strlen(env[x]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
