#include "shell.h"

/**
 * builtin - checks if command is builtin
 * @cmd_list: List of commands
 * @alias_list: List of aliases
 * @free_env_list: List of envs
 * @tokes: command string
 * @argv: argv 0
 * @env: environment
 * @ret: signal value for parser2 function
 * Return: 0 if not builtin
 */

char *builtin(char **cmd_list, ll *alias_list,
	      char *free_env_list, char **tokes, char *argv, char **env, int *ret)
{
	int x = 0;
	b_in built_in[] = {
		{"exit", my_exit}, {"setenv", _setenv}, {"env", b_env},
		{"unsetenv", _unsetenv}, {"cd", _cd}, {NULL, NULL}
	};

	*ret = 0;
	for (x = 0; built_in[x].var; x++)
	{
		if ((_strcmp(tokes[0], built_in[x].var)) == 0)
		{
			free_env_list = built_in[x].f(cmd_list, alias_list,
						      free_env_list, tokes, argv, env);
			(*ret)++;
		}
	}

	return (free_env_list);
}

/**
 * _setenv - sets environment
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * @cmd_list: list of commands
 * @alias_list: list of aliases
 * @free_env_list: list of envs
 * Return: int
 */

char *_setenv(char **cmd_list, ll *alias_list,
	      char *free_env_list, char **tokes, char *argv, char **env)
{
	int x = 0;
	char *tmp;

	(void)cmd_list;
	(void)alias_list;
	(void)argv;
	while (env[x])
	{
		if (_strncmp(env[x], tokes[1], _strlen(tokes[1])) == 0)
			break;
		x++;
	}
	if (env[x] != NULL)
	{
		free_env_list = add_to_free_env(free_env_list, tokes[1]);
		tmp = str_mul_cat(tokes[1], tokes[2], "=");
		env[x] = _strdup(tmp);
	}
	else
	{
		free_env_list = add_to_free_env(free_env_list, tokes[1]);
		tmp = str_mul_cat(tokes[1], tokes[2], "=");
		env[x] = _strdup(tmp);
		env[x + 1] = NULL;
	}
	return (free_env_list);
}

/**
 * add_to_free_env - adds to free env list
 * @free_env_list: where we are adding
 * @token: what we are adding
 * Return: env list
 */

char *add_to_free_env(char *free_env_list, char *token)
{
	int newsize = 0, len = 0, x = 0;

	if (!free_env_list)
	{
		free_env_list = malloc(_strlen(token) + 1);
			for (x = 0; token[x]; x++)
				free_env_list[x] = token[x];
		free_env_list[x] = '\0';
	}
	else
	{
		len = _strlen(free_env_list);
		newsize = len + _strlen(token);
		free_env_list = _realloc(free_env_list, len, newsize + 2);
		free_env_list = str_mul_cat(free_env_list, token, " ");
	}
	return (free_env_list);
}

/**
 * _unsetenv - unsets env var
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * @cmd_list: list of commadns
 * @alias_list: list of aliases
 * @free_env_list: list of envs
 * Return: int
 */

char *_unsetenv(char **cmd_list, ll *alias_list,
		char *free_env_list, char **tokes, char *argv, char **env)
{
	int x = 0;

	(void)cmd_list;
	(void)alias_list;
	(void)argv;
	while (env[x])
	{
		if (_strncmp(env[x], tokes[1], _strlen(tokes[1])) == 0)
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
		free_env_list = remove_free_list_node(free_env_list, tokes[1]);
	}
	return (free_env_list);
}

/**
 * b_env - env builtin cmd
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * @cmd_list: list of commands
 * @alias_list: list of aliasaes
 * @free_env_list: list of envs
 * Return: int
 */

char *b_env(char **cmd_list, ll *alias_list,
	    char *free_env_list, char **tokes, char *argv, char **env)
{
	int x = 0;
	(void)cmd_list;
	(void)alias_list;
	(void)argv;
	(void)tokes;
	for (x = 0; env[x]; x++)
	{
		write(STDOUT_FILENO, env[x], _strlen(env[x]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (free_env_list);
}
