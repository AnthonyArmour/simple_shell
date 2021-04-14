#include "shell.h"

/**
 * remove_free_list_node - Remvoes a node from our list
 * @free_env_list: List of tokes
 * @token: What to remove
 * Return: our list
 */

char *remove_free_list_node(char *free_env_list, char *token)
{
	int x = 0, sig = 0, y = 0;

	for (x = 0; free_env_list[x]; x++)
	{
		if (_strncmp((free_env_list + x), token, _strlen(token)) == 0)
		{
			sig = 1;
		}
		if (sig == 1)
		{
			y = x;
			while (free_env_list[y] != ' ' && free_env_list[y] != '\0')
				free_env_list[y] = ' ', y++;
			sig = 0;
		}
	}
	return (free_env_list);
}
