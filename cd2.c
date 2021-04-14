#include "shell.h"

/**
 * get_home - gets home directory
 * @home: string holding home directory
 * @env: environment
 * Return: home directory
 */

char *get_home(char *home, char **env)
{
	int idx = 0, x = 4, xx = 0;

	while (env[idx])
	{
		if (_strncmp(env[idx], "HOME=", 5) == 0)
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
