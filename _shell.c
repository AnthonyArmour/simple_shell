#include "shell.h"
/**
 * main - basic shell
 * @argc: num of cmd line args
 * @argv: args at cmd line
 * @env: environment data
 * Return: int
 */
int err_Cnt = 0;
int main(int argc, char *argv[], char *env[])
{
	char *command = NULL;
	int ttrue = 1, cmd_Count = 0, mode, x = 0, fd;
	char **Cmd = NULL;
	ll *alias_List = NULL;

	(void)argv;
	(void)argc;
	if (argv[1] != NULL)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(22);
		alias_List = _script(fd, argv[0], env, alias_List);
		return (0);
	}
	if ((mode = isatty(STDIN_FILENO)))
                puts("Interactive mode!");
        else
	{
                puts("Non-interactive mode!");
	}
	signal(SIGINT, SIG_IGN);
	while (ttrue)
	{
		if (mode)
			print_Prompt1();
		command = read_Cmd("argv");
		cmd_Count = _strlen(command);
		if (command[0] == '\0' || command[0] == '\n')
		{
			free(command);
			continue;
		}
		if (strcmp(command, "exit\n") == 0)
		{
			free(command);
			break;
		}
		if (cmd_Count != 0)
		{
			Cmd = parser1(command, argv[0]);
			alias_List = parser2(Cmd, argv[0], env, alias_List);
			for (x = 0; Cmd[x]; x++)
				free(Cmd[x]);
			free(Cmd);
		}
		free(command);
		if (!mode)
			break;
	}
	return (0);
}
	
/**
 * _script - runs command script
 * @fd: File descriptor for script
 * @argv: Arguments
 * @env: Environment
 * Return: void
 */

ll *_script(int fd, char *argv, char **env, ll *alias_List)
{
	int x = 0, xx = 0, buflen = 0, newlen = 0;
	char *buf = NULL, tmp[1024];
	char **Cmd = NULL;
	ssize_t count;

	while ((count = read(fd, tmp, 1024)) > 0)
	{
		if (buf != NULL)
			buflen = _strlen(buf);
		newlen = buflen + count;
		buf = _realloc(buf, buflen, newlen);
		for (x = 0; x < count; x++)
		{
			buf[xx] = tmp[x];
			xx++;
		}
		buf[xx] = '\0';
	}
	for (x = 0; buf[x]; x++)
	{
		if (buf[x] == '\n')
			buf[x] = ';';
	}
	if (x != 0)
	{
		Cmd = parser1(buf, argv);
		alias_List = parser2(Cmd, argv, env, alias_List);
		for (x = 0; Cmd[x]; x++)
			free(Cmd[x]);
		free(Cmd);
	}
	return (alias_List);
}

/**
 * read_Cmd - reads command into string
 * Return: string
 */

char *read_Cmd(char *argv)
{
	size_t bufsize = 1024;
	ssize_t cmd_Check = NULL;
	char *cmd_Str = NULL, *buf = NULL;
	char *cmd_temp = NULL;
	int ptr_len = 0, cmd_index = 0, buf_len = 0, x = 0, y;

	(void)argv;
	while(cmd_Check != -1)
	{
		cmd_Check = getline(&buf, &bufsize, stdin);
		for (x = 0; buf[x] != '\0'; x++)
		{
			if (buf[x + 1] == '#')
			{
				buf[x] = '\n';
				buf[x + 1] = '\0';
				y = x;
				while (buf[y - 1] == ' '|| buf[y - 1] == '\\')
				{
					y--;
					if (buf[y] == '\\')
						buf[y] = ' ';
				}
				break;
			}
		}
		buf_len = _strlen(buf);
		if (!cmd_Str)
			cmd_Str = malloc(buf_len + 1);
		else
		{
			cmd_temp = _realloc(cmd_Str, cmd_index, ptr_len);
		        if (cmd_temp)
				cmd_Str = cmd_temp;
			else
				free(cmd_Str), cmd_Str = NULL;
		}
		_strcpy(cmd_Str + ptr_len, buf);
		if (buf[buf_len - 1] == '\n')
		{
			if (buf_len == 1 || buf[buf_len - 2] != '\\')
			{
				free(buf);
				cmd_Str[_strlen(cmd_Str) - 1] = '\0';
				return (cmd_Str);
			}
			cmd_Str[ptr_len + buf_len - 2] = '\0';
			buf_len -= 2;
			print_Prompt2();
		}
		ptr_len += buf_len;
	}
	if (!cmd_Str)
	{
		write(STDERR_FILENO, "Memory error", 12);
		exit(11);
	}
	free(buf);
	return (cmd_Str);
}
