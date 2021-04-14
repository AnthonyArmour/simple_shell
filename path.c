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
	char *strp = NULL, *tmp = NULL;
	char **paths = NULL;
	struct stat stats;

	if (stat(token, &stats) == 0)
		return (token);
	ex = path_idx(env);
	strp = _strdup((env[ex] + 5));
	num_of_paths = get_size(strp, ':');
	strp = add_cwd(strp);
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
	free(strp);
	paths = append_paths(token, paths);
	final_path_idx = path_check(paths);
	if (final_path_idx >= 0)
	{
		free(token);
		tmp = _strdup(paths[final_path_idx]);
		free_2d(paths);
		return (tmp);
	}
	else
	{
		free_2d(paths);
		return (NULL);
	}
}

/**
 * add_cwd - adds PWD
 * @str: passed directory
 * Return: directory
 */

char *add_cwd(char *str)
{
	int idx = 0, sig = 0;
	size_t n = 20;
	char *buf = NULL, *temp = NULL;

	buf = malloc(n);
	buf = getcwd(buf, n);
	while (!buf)
	{
		n = n * 2;
		buf = _realloc(buf, (n / 2), n);
		buf = getcwd(buf, n);
	}
	temp = cwd_cat(temp, idx, buf, str);
	if (str[_strlen(str) - 1] == ':')
	{
		_strcat(temp, str);
		_strcat(temp, buf);
		sig = 1;
	}
	else if (sig == 0)
	{
		free(temp);
		free(buf);
		return (str);
	}
	free(str);
	free(buf);
	return (temp);
}

/**
 * cwd_cat - deals with signal if statements
 * @temp: base string
 * @idx: index
 * @buf: buffer
 * @str: string
 * Return: temp
 */

char *cwd_cat(char *temp, int idx, char *buf, char *str)
{
	int xx = _strlen(buf), x = 0, sig = 0;

	temp = malloc(_strlen(str) + _strlen(buf) + 1);
	if (str[0] == ':')
	{
		_strcat(temp, buf);
		_strcat(temp, str);
		sig = 1;
	}
	else
	{
		for (idx = 0; str[idx]; idx++)
		{
			if (str[idx] == ':' && str[idx + 1] == ':')
			{
				sig = 1;
				break;
			}
		}
		if (sig != 0)
		{
			for (x = 0; x <= idx; x++)
				temp[xx] = str[x], xx++;
			for (x = 0; buf[x]; x++)
				temp[xx] = buf[x], xx++;
			for (idx = idx + 1; str[idx]; idx++)
				temp[xx] = str[idx], xx++;
			temp[xx] = '\0';
		}
	}
	return (temp);
}

/**
 * path_check - finds directory paths
 * @paths: directory paths
 * Return: directory path index
 */

int path_check(char **paths)
{
	int x = -1, sig = 0;
	struct stat stats;

	for (x = 0; paths[x]; x++)
	{
		if (stat(paths[x], &stats) == 0)
		{
			sig = 1;
			break;
		}
	}
	if (sig == 0)
		x = -1;
	return (x);
}

/**
 * append_paths - appends command to the path
 * @token: command
 * @paths: paths!
 * Return: appended paths
 */

char **append_paths(char *token, char **paths)
{
	int x = 0;

	for (x = 0; paths[x]; x++)
	{
		paths[x] = _realloc(paths[x], _strlen(paths[x]),
				    _strlen(paths[x]) + _strlen(token) + 2);
		paths[x] = str_mul_cat(paths[x], token, "/");
	}
	return (paths);
}
