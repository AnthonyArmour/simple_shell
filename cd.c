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
	char *temp, *old_pwd = NULL, *path = NULL, *pwd = "PWD=";

	(void)cmd_list;
	(void)alias_list;
	temp = NULL;
	temp = malloc(5);
	temp[0] = '\0';
	_strcat(temp, pwd);
	if (!tokes[1])
		path = get_home(path, env);
	else if (_strcmp(tokes[1], "-") == 0)
		path = get_old_dir(path, env);
	else
	{
		path = malloc(_strlen(tokes[1]) + 1), path[0] = '\0';
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
		temp = _realloc(temp, 5, _strlen(buf) + 6);
		temp = _strcat(temp, buf);
		free(buf);
		old_pwd = set_pwd(temp, env, free_env_list);
		set_old_pwd(old_pwd, env, free_env_list);
		free_env_list = add_to_free_env(free_env_list, "OLDPWD");
		free_env_list = add_to_free_env(free_env_list, "PWD");

	}
	free(temp);
	free(path);
	path = NULL;
	return (free_env_list); }

/**
 * findcwd - finds PWD
 * @buf: string to put PWD
 * @n: integer input
 * Return: buf
 */

char *findcwd(char *buf, size_t n)
{

	buf = malloc(n);
	while (getcwd(buf, n) == NULL)
	{
		free(buf);
		buf = NULL;
		n = n * 2;
		buf = malloc(n);
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
 * @free_env_list: list of envs to free
 * Return: void
 */

void set_old_pwd(char *str, char **env, char *free_env_list)
{
	int idx = 0;

	while (env[idx])
	{
		if (_strncmp(env[idx], "OLDPWD=", 7) == 0)
			break;
		idx++;
	}
	if (free_env_list)
		free(env[idx]);
	env[idx] = _strdup(str);
	free(str);
	str = NULL;
}

/**
 * set_pwd - sets pwd
 * @str: str to hold env idx
 * @env: environment
 * @free_env_list: list of envs to free
 * Return: old pwd
 */

char *set_pwd(char *str, char **env, char *free_env_list)
{
	int idx = 0;
	char *old = NULL, *pwd = NULL;

	while (env[idx])
	{
		if (_strncmp(env[idx], "PWD=", 4) == 0)
			break;
		idx++;
	}
	old = malloc(_strlen(env[idx]) + 5);
	old[0] = '\0';
	_strcat(old, "OLDPWD=");
	_strcat(old, env[idx] + 4);
	if (free_env_list)
		free(env[idx]);
	pwd = malloc(_strlen(str) + 5);
	pwd[0] = '\0';
	_strcat(pwd, str);
	env[idx] = _strdup(pwd);
	free(pwd);
	pwd = NULL;
	return (old);
}
