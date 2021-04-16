#include "shell.h"

/**
 * free_env - frees an environmental variable
 * @env: variable to free
 * @free_env_list: list of all environ variables
 * Return: Null
 */

void free_env(char **env, char *free_env_list)
{
	int idx = 0, x = 0, tokx = 0, chars = 0, words = 0;
	char **free_str = NULL;

	if (!free_env_list)
		return;
	dim2(free_env_list, &chars, &words, "str");
	free_str = malloc(sizeof(char *) * chars + words);
	for (x = 0; x < words; x++)
		free_str[x] = _strtok(free_env_list, &tokx, ' ');
	free_str[x] = NULL;
	for (idx = 0; env[idx]; idx++)
	{
		for (x = 0; free_str[x]; x++)
		{
			if (_strncmp(free_str[x], env[idx],
				     _strlen(free_str[x])) == 0)
			{
				free(env[idx]);
				break;
			}
		}
	}
	free_2d(free_str);
	free(free_env_list);
}

/**
 * my_exit - exits on exit cmd
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * @cmd_list: list of commands
 * @alias_list: list of aliases
 * @free_env_list: list of envs
 * Return: int
 */

char *my_exit(char **cmd_list, ll *alias_list,
	      char *free_env_list, char **tokes, char *argv, char **env)
{
	int num = 0, err_num = 0;


	if (tokes[1] == NULL)
	{
		free_2d(tokes);
		free_env(env, free_env_list);
		free_rm(cmd_list, alias_list);
		exit(0);
	}
	else
	{
		num = myAtoi(tokes[1]);
		if (num < 0 || _strlen(tokes[1]) > 10)
		{
			err_num = 122;
			handle_err(argv, err_num, tokes[1]);
		}
		else
		{
			free_2d(tokes);
			free_env(env, free_env_list);
			free_rm(cmd_list, alias_list);
			exit(num);
		}
	}
	return (free_env_list);
}

/**
 * free_rm - frees cmds and aliases
 * @cmd: cmd to free
 * @alias_list: list of aliases
 * Return: NULL
 */

void free_rm(char **cmd, ll *alias_list)
{
	int x = 0;

	for (x = 0; cmd[x]; x++)
		free(cmd[x]);
	free(cmd);
	free_list(alias_list);
}

/**
 * xstrlen - finds str len not equal to space
 * @s: str
 * Return: len
 */

int xstrlen(char *s)
{
	int x = 0;

	for (x = 0; s[x] != ' '; x++)
		;
	return (x);
}
