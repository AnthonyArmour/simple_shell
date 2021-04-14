#include "shell.h"
extern int errno;
char *_cd(char **cmd_list, ll *alias_list,
	  char *free_env_list, char **tokes, char *argv, char **env)
{
	int err_num, x = 0;
	size_t n = 15;
	char *buf = NULL;
	char *temp = NULL, *old_pwd = NULL;
	char *pwd = "PWD=", *path = NULL;

	(void)cmd_list;
	(void)alias_list;
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
		free_env_list = add_to_free_env(free_env_list, "OLDPWD");
		free_env_list =add_to_free_env(free_env_list, "PWD");
	}
	free(path);
	return (free_env_list);
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
