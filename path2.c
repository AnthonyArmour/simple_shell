#include "shell.h"

/**
 * path_idx - finds path variable in environment
 * @env: environment
 * Return: path variable index
 */

int path_idx(char **env)
{
	int x = 0, sig = 0;

	while (env[x])
	{
		if (_strncmp(env[x], "PATH=", 5) == 0)
		{
			sig = 1;
			break;
		}
		x++;
	}
	if (sig == 0)
		return (-1);
	return (x);
}
