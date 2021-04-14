#include "shell.h"
/**
 * main - basic shell
 * @argc: num of cmd line args
 * @argv: args at cmd line
 * @env: environment data
 * Return: int
 */
extern int errno;
int err_Cnt = 1;
static char *free_env_list = NULL;
int main(int argc, char *argv[], char *env[])
{
	char *command = NULL;
	int ttrue = 1, cmd_Count = 0, mode, x = 0, fd;
	char **Cmd = NULL;
	ll *alias_List = NULL;

	(void)argv;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(22);
		alias_List = _script(fd, argv[0], env, alias_List);
		free_env(env, free_env_list);
                free_rm(Cmd, alias_List);
		return (0);
	}
        mode = isatty(STDIN_FILENO);
	signal(SIGINT, SIG_IGN);
	while (ttrue)
	{
		if (mode)
			print_Prompt1();
		command = read_Cmd(argv[0]);
		if (!command)
		{
			if (mode)
			{
				free(command);
				continue;
			}
			else
			{
				free(command);
				exit(0);
			}
		}
		cmd_Count = _strlen(command);
		if (command[0] == '\0' || command[0] == '\n')
		{
			free(command);
			continue;
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
		err_Cnt++;
	}
	free_env(env, free_env_list);
	free_rm(Cmd, alias_List);
	return (0);
}

/**
 * read_Cmd - reads command into string
 * @argv: argument
 * Return: string
 */

char *read_Cmd(char *argv)
{
	size_t bufsize = 1024;
	ssize_t cmd_Check = 1;
	char *cmd_Str = NULL, *buf = NULL;
	char *cmd_temp = NULL;
	int ptr_len = 0, cmd_index = 0, buf_len = 0, x = 0, y;

	(void)argv;
	while((cmd_Check = getline(&buf, &bufsize, stdin)) != -1)
	{
		while (buf[0] == ' ')
		{
			buf++;
			if (buf[0] == '\n')
				break;
		}
		if (buf[0] == '\n' && buf[1] == '\0')
		{
			return (cmd_Str);
		}
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
			free(buf);
			for (x = _strlen(cmd_Str) - 1; x >= 0; x--)
			{
				if (cmd_Str[x] == ' ' || cmd_Str[x] == '\n')
					cmd_Str[x] = '\0';
				else
					break;
			}
			return (cmd_Str);
		}
		ptr_len += buf_len;
	}
	if (cmd_Check == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	free(buf);
	return (cmd_Str);
}


/**
 * parser1 - tokenizes multiple cmds into strings
 * @cmd_Str: cmd string input
 * @argv: argv[0]
 * Return: 2d array of strings
 */

char **parser1(char *cmd_Str, char *argv)
{
	char **cmd_List = NULL;
	char *tmp = NULL;
	int x = 0, y = 0, xx = 0, cmd_Pos = 0, cmd_Str_Len = 0, cmd_Count = 1;

	if (!cmd_Str)
		return (NULL);
	StrDimensions(cmd_Str, argv, &cmd_Str_Len, &cmd_Count);
	cmd_List = malloc(sizeof(char *) * cmd_Str_Len + cmd_Count);
	if (!cmd_List)
		return (NULL);
	while (cmd_Str[cmd_Pos])
	{
		if (cmd_Str[cmd_Pos] == ';')
			cmd_Pos++;
		else
		{
			y = 0;
			tmp = _strtok(cmd_Str, &cmd_Pos, ';');
			if (!tmp)
				return (NULL);
			while (tmp[y])
				y++;
			cmd_List[x] = malloc(sizeof(char) * (y + 1));
			if (!cmd_List[x])
				return (NULL);
			for (xx = 0; xx < y; xx++)
				cmd_List[x][xx] = tmp[xx];
			cmd_List[x][xx] = '\0';
			if (tmp)
				free(tmp);
			x++;
		}
	}
	cmd_List[x] = NULL;
	return (cmd_List);
}

/**
 * parser2 - tokenizes strings into tokens
 * @cmd_List: 2d array of strings
 * @argv: argv[0]
 * @env: environ
 * @alias_List: list of aliases
 * Return: void. Passes tokens to execution func
 */

ll *parser2(char **cmd_List, char *argv, char **env, ll *alias_List)
{
	int x = 0, i = 0, tok_idx = 0, chars = 0, words = 0;
	int ret = 0;
	char **tokes = NULL;
	char *our_path = NULL;

	for (x = 0; cmd_List[x]; x++)
	{
		cmd_List[x] = alias_Check(cmd_List[x], alias_List, argv);
		dim2(cmd_List[x], &chars, &words, argv);
		tokes = malloc(sizeof(char *) * chars + words);
		tokes[0] = _strtok(cmd_List[x], &tok_idx, ' ');
		if (_strcmp(tokes[0], "alias") == 0)
		{
			alias_List = alias_Options(argv, cmd_List[x], alias_List);
			free(tokes[0]);
			continue;
		}
		for (i = 1; i < words; i++)
		{
			tokes[i] = _strtok(cmd_List[x], &tok_idx, ' ');
		}
		tokes[i] = NULL;
		free_env_list = builtin(cmd_List, alias_List,
					free_env_list, tokes, argv, env, &ret);
		if (ret == 0)
		{
			our_path = get_path(env, tokes[0]);
			if (our_path)
			{
				free(tokes[0]);
				tokes[0] = our_path;
			}
			exec_Cmd(tokes, argv, env);
		}
		for (i = 0; tokes[i]; i++)
			free(tokes[i]);
		free(tokes);
		chars = 0, words = 0, tok_idx = 0;
	}
/*	for (x = 0; cmd_List[x]; x++)
		free(cmd_List[x]);
	free(cmd_List);
*/
return (alias_List);
}

/**
 * exec_Cmd - execute function
 * @tokes: 2d array of tokens
 * @argv: argv[0]
 * @env: environment
 * Return: void
 */

void exec_Cmd(char **tokes, char *argv, char **env)
{

	pid_t pid = fork();
	int err_num;

	(void)env;
	if (pid != 0)
	{
		while (wait(NULL) != -1)
			;
		kill(pid, SIGKILL);
	}
	else
	{
		if (execve(tokes[0], tokes, NULL) == -1)
		{
			err_num = errno;
			handle_err(argv, err_num, tokes[0]);
			_exit(1);
		}
	}
}
void handle_err(char *argv, int err_num, char *token)
{
	char *temp = NULL;
	char *num;
	int x = 0, error_cnt = 0, idx = 0;
	char *not_found = "not found\n", *illegal = "Illegal number\n";

	error_cnt = err_Cnt;
	num = print_number(error_cnt);
	temp = malloc(_strlen(argv) + 3);
	for (idx = 0; argv[idx]; idx++)
		temp[idx] = argv[idx];
	temp[idx] = ':', idx++;
	temp[idx] = ' ', idx++;
	temp = _realloc(temp, _strlen(temp),
			_strlen(temp) + _strlen(num) + 2);
	for (x = 0; num[x]; x++)
	temp[idx] = num[x], idx++;
	temp[idx] = ':', idx++;
	temp[idx] = ' ', idx++;
	if (err_num == 2 || err_num == 20)
	{
		temp = _realloc(temp, _strlen(temp),
				_strlen(temp) + _strlen(token) + 2);
		for (x = 0; token[x]; x++)
				temp[idx] = token[x], idx++;
		temp[idx] = ':', idx++;
		temp[idx] = ' ', idx++;
		temp = _realloc(temp, _strlen(temp),
				_strlen(temp) + _strlen(not_found) + 1);
		for (x = 0; not_found[x]; x++)
			temp[idx] = not_found[x], idx++;
		temp[idx] = '\0';
		write(STDERR_FILENO, temp, _strlen(temp));
	}
	else if (err_num == 122)
	{
		temp = _realloc(temp, _strlen(temp),
				_strlen(temp) + _strlen(token) + 2);
		for (x = 0; token[x]; x++)
				temp[idx] = token[x], idx++;
		temp[idx] = ':', idx++;
		temp[idx] = ' ', idx++;
		temp = _realloc(temp, _strlen(temp),
				_strlen(temp) + _strlen(illegal) + 1);
		for (x = 0; illegal[x]; x++)
			temp[idx] = illegal[x], idx++;
		temp[idx] = '\0';
		write(STDERR_FILENO, temp, _strlen(temp));
	}
	else
	{
		write(STDERR_FILENO, temp, _strlen(temp));
		perror(token);
	}
	free(temp);
}
