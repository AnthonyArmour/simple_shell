#include "shell.h"

/**
 * _cd - change directory
 * @cmd_list: list of commands
 * @alias_list: list of aliases
 * @free_env_list: env vars to be freed
 * @tokes: tokens
 * @argv: Argument
 * @env: environment
 * Return: free_env_list
 */

char *_cd(char **cmd_list, ll *alias_list,
	  char *free_env_list, char **tokes, char *argv, char **env)
{
	int err_num;
	size_t n = 15;
	char *buf = NULL;
	char *temp = NULL, *old_pwd = NULL, *pwd = "PWD=", *path = NULL;

	(void)cmd_list;
	(void)alias_list;
	temp = malloc(5);
	_strcat(temp, pwd);
	if (!tokes[1])
		path = get_home(path, env);
	else if (_strcmp(tokes[1], "-") == 0)
		path = get_old_dir(path, env);
	else
	{
		path = malloc(_strlen(tokes[1]) + 1);
		_strcat(path, tokes[1]);
	}
	if (chdir(path) < 0)
	{
		err_num = errno;
		handle_err(argv, err_num, tokes[1]);
	}
	else
	{
		buf = findcwd(buf, n);
		temp = _realloc(temp, 5, _strlen(buf) + 5);
			temp = _strcat(temp, buf);
		free(buf);
		printf("BEFORE SETPWD\n");
		old_pwd = set_pwd(temp, env);
		printf("BEFORE SETOLDPWD\n");
		set_old_pwd(old_pwd, env);
		printf("BEFORE FREE ENV LIST\n");
		free_env_list = add_to_free_env(free_env_list, "OLDPWD");
		free_env_list = add_to_free_env(free_env_list, "PWD");
	}
	free(temp);
	free(path);
	return (free_env_list);
}

/**
 * findcwd - finds PWD
 * @buf: string to put PWD
 * @n: integer input
 * Return: buf
 */

char *findcwd(char *buf, size_t n)
{
	buf = malloc(n);
	buf = getcwd(buf, n);
	while (!buf)
	{
		n = n * 2;
		buf = _realloc(buf, (n / 2), n);
		buf = getcwd(buf, n);
	}
	return (buf);
}

/**
 * get_old_dir - gets previous directory
 * @old: old directory
 * @env: environment
 * Return: old directory
 */

char *get_old_dir(char *old, char **env)
{
	int idx = 0, x = 7, xx = 0;

	while (env[idx])
	{
		if (_strncmp(env[idx], "OLDPWD=", 7) == 0)
			break;
		idx++;
	}
	old = malloc(_strlen(env[idx]) - 6);
	for (x = 7; env[idx][x]; x++)
		old[xx] = env[idx][x], xx++;
	old[xx] = '\0';
	return (old);
}

/**
 * set_old_pwd - sets old pwd
 * @str: str to hold env idx
 * @env: environment
 * Return: void
 */

void set_old_pwd(char *str, char **env)
{
	int idx = 0;

	while (env[idx])
	{
		if (_strncmp(env[idx], "OLDPWD=", 7) == 0)
			break;
		idx++;
	}
	env[idx] = str;
}

/**
 * set_pwd - sets pwd
 * @str: str to hold env idx
 * @env: environment
 * Return: old pwd
 */

char *set_pwd(char *str, char **env)
{
	int idx = 0, x = 0, xx = 0;
	char *old = NULL, *temp = "OLDPWD=";

	while (env[idx])
	{
		if (_strncmp(env[idx], "PWD=", 4) == 0)
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
