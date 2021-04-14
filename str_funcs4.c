#include "shell.h"

/**
 * script_check - checks if input is a script
 * @argc: argc
 * @argv: argv
 * @env: env
 * @alias_List: list of aliases
 * @free_env_list: list of env variables to be freed
 * @Cmd: Command
 * Return: void
 */

void script_check(int argc, char *argv[], char **env, ll *alias_List,
				char *free_env_list, char **Cmd)
{
	int fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(22);
		alias_List = _script(fd, argv[0], env, alias_List);
		free_env(env, free_env_list);
		free_rm(Cmd, alias_List);
		exit(0);
	}
}

/**
 * comment_check - checks for command line comments
 * @buf: input string
 * Return: buf
 */

char *comment_check(char *buf)
{
	int x = 0, y = 0;

	if (buf[0] == '\n' && buf[1] == '\0')
        {
                free(buf);
                return (NULL);
        }
	for (x = _strlen(buf) - 1; x >= 0; x--)
	{
		if (buf[x - 1] != ' ' && buf[x - 1] != '\n')
		{
			buf[x] = '\n';
			break;
		}
		if (buf[x] == ' ' || buf[x] == '\n')
			buf[x] = '\0';
		if (x - 1 == 0 && (buf[x - 1] == ' ' || buf[x - 1] == '\n'))
		{
			free(buf);
			return (NULL);
		}
	}

/*	while (buf[0] == ' ')
	{
		buf++;
		if (buf[0] == '\n')
			break;
	}
*/
	for (x = 0; buf[x] != '\0'; x++)
	{
		if (buf[x + 1] == '#')
		{
			buf[x] = '\n';
			buf[x + 1] = '\0';
			y = x;
			while (buf[y - 1] == ' ' || buf[y - 1] == '\\')
			{
				y--;
				if (buf[y] == '\\')
					buf[y] = ' ';
			}
			break;
		}
	}
	return (buf);
}
