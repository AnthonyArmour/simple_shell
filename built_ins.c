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
int _cd(char **tokes, char *argv, char **env)
{
	int err_num, x = 0;
	size_t n = 15;
	char *buf = NULL;
	char *temp = NULL, *old_pwd = NULL;
	char *pwd = "PWD=", *path = NULL;

	(void)env;
	temp = malloc(5);
	for (x = 0; pwd[x]; x++)
		temp[x] = pwd[x];
	temp[x] = '\0';
	if (!tokes[1])
		path = get_home(path, env);
	else if (strcmp(tokes[1], "-") == 0)
		path = get_old_dir(path, env);
	else
	{
		path = malloc(_strlen(tokes[1]) + 1);
		for (x = 0; tokes[1][x]; x++)
			path[x] = tokes[1][x];
		path[x] = '\0';
	}
	if (chdir(path) < 0)
	{
		err_num = errno;
		free(path);
		handle_err(argv, err_num, tokes[1]);
	}
	else
	{
		buf = malloc(n);
		buf = getcwd(buf, n);
		while (!buf)
		{
			n = n * 2;
			buf = _realloc(buf, (n / 2), n);
			buf = getcwd(buf, n);
		}
		temp = _realloc(temp, 5, _strlen(buf) + 5);
			temp = strcat(temp, buf);
		free(buf);
		old_pwd = set_pwd(temp, env);
		set_old_pwd(old_pwd, env);
	}
	free(path);
	return (0);
}
char *get_home(char *home, char **env)
{
	int idx= 0, x = 4, xx = 0;


        while (env[idx])
	{
                if (strncmp(env[idx], "HOME=", 5) == 0)
                        break;
                idx++;
        }
	home = malloc(_strlen(env[idx]) - 4);
	for (x = 5; env[idx][x]; x++)
	{
		home[xx] = env[idx][x], xx++;
	}
	home[xx] = '\0';
	return (home);
}
char *get_old_dir(char *old, char **env)
{
	int idx = 0, x = 7, xx = 0;


	while (env[idx])
	{
		if (strncmp(env[idx], "OLDPWD=", 7) == 0)
			break;
		idx++;
	}
	old = malloc(_strlen(env[idx]) - 6);
	for (x = 7; env[idx][x]; x++)
		old[xx] = env[idx][x], xx++;
	old[xx] = '\0';
	return (old);
}
void set_old_pwd(char *str, char **env)
{
	int idx = 0;

	while (env[idx])
	{
		if (strncmp(env[idx], "OLDPWD=", 7) == 0)
			break;
		idx++;
	}
	env[idx] = str;
}
void free_pwd(char **env)
{
        int idx = 0;

	while (env[idx])
        {
                if (strncmp(env[idx], "OLDPWD=", 7) == 0)
                        break;
                idx++;
        }
        free(env[idx]);
	idx = 0;
	while (env[idx])
        {
                if(strncmp(env[idx], "PWD=", 4) == 0)
                        break;
                idx++;
        }
	free(env[idx]);
}

char *set_pwd(char *str, char **env)
{
	int idx = 0, x = 0, xx = 0;
	char *old = NULL, *temp = "OLDPWD=";

	while (env[idx])
	{
		if(strncmp(env[idx], "PWD=", 4) == 0)
			break;
		idx++;
	}
	old = malloc(_strlen(env[idx]) + 4);
	for (x = 0; temp[x]; x++)
		old[xx] = temp[x], xx++;
	for (x = 4; env[idx][x]; x++)
		old[xx] = env[idx][x], xx++;
	old[xx] = '\0';
	env[idx] = str;
	return (old);
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
 * my_exit - exits on exit cmd
 * @tokes: tokens
 * @argv: argv[0]
 * @env: environment
 * Return: int
 */

int my_exit(char **tokes, char *argv, char **env)
{
	(void)argv;
	(void)env;
	if (tokes[1] == NULL)
		exit(0);
	else
		exit(atoi(tokes[1]));
	return (0);
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
