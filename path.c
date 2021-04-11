#include "shell.h"

/**
 * get_path - returns correct path for command
 * @env: environment
 * @token: command string
 * Return: path for command
 */

char *get_path(char **env, char *token)
{
	int ex = 0, num_of_paths = 0, tok_idx = 0, x = 0, final_path_idx = 0;
	char *strp = NULL;
	char **paths = NULL;

	ex = path_idx(env);
	strp = _strdup(env[ex]);
	strp += 5;
	num_of_paths = get_size(strp, ':');
	paths = malloc(sizeof(char *) * (num_of_paths + 1));
	if (!paths)
		exit(98);
	paths[x] = _strtok(strp, &tok_idx, ':');
	tok_idx++;
	for (x = 1; x < num_of_paths; x++)
	{
		paths[x] = _strtok(strp, &tok_idx, ':');
		tok_idx++;
	}
	paths[x] = NULL;
	paths = append_paths(token, paths);
	final_path_idx = path_check(paths);
	if (final_path_idx >= 0)
		return (paths[final_path_idx]);
	return (NULL);
}
