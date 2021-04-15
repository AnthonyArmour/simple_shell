#include "shell.h"
static char *free_env_list;
static int err_Cnt;
/**
 * main - basic shel
 * @argc: num of cmd line args
 * @argv: args at cmd line
 * @env: environment data
 * Return: int
 */
int main(int argc, char *argv[], char *env[])
{
	char *command = NULL;
	int ttrue = 1, cmd_Count = 0, mode;
	char **Cmd = NULL;
	ll *alias_List = NULL;

	free_env_list = NULL;
	err_Cnt = 1;
	script_check(argc, argv, env, alias_List, free_env_list, Cmd);
	mode = isatty(STDIN_FILENO);
	signal(SIGINT, SIG_IGN);
	while (ttrue)
	{
		if (mode)
			print_Prompt1();
		command = read_Cmd(mode);
		if (!command)
		{
			if (mode)
			{free(command);
				continue; }
			else
			{free(command);
				exit(0); }
		}
		cmd_Count = _strlen(command);
		if (command[0] == '\0' || command[0] == '\n')
		{free(command);
			continue; }
		if (cmd_Count != 0)
		{
			Cmd = parser1(command, argv[0]);
			free(command);
			alias_List = parser2(Cmd, argv[0], env, alias_List
					     , free_env_list);
			free_2d(Cmd);
		}
		err_Cnt++;
	}
	return (0);
}

/**
 * read_Cmd - reads command into string
 * @mode: mode
 * Return: string
 */

char *read_Cmd(int mode)
{
	size_t bufsize = 1024;
	ssize_t cmd_Check = 1;
	char *cmd_Str = NULL, *buf = NULL, *cmd_temp = NULL;
	int ptr_len = 0, cmd_index = 0, buf_len = 0, x = 0;

	while ((cmd_Check = getline(&buf, &bufsize, stdin)) != -1)
	{buf = comment_check(buf);
		if (!buf)
		{
			if (mode)
				print_Prompt1();
			continue; }
		buf_len = _strlen(buf);
		if (!cmd_Str)
			cmd_Str = malloc(buf_len + 1);
		else
		{
			cmd_temp = _realloc(cmd_Str, cmd_index, ptr_len);
			if (cmd_temp)
				cmd_Str = cmd_temp;
			else
				free(cmd_Str), cmd_Str = NULL; }
		_strcpy(cmd_Str + ptr_len, buf);
		if (buf[buf_len - 1] == '\n')
		{free(buf);
			for (x = _strlen(cmd_Str) - 1; x >= 0; x--)
			{
				if (cmd_Str[x] == ' ' || cmd_Str[x] == '\n')
					cmd_Str[x] = '\0';
				else
					break; }
			return (cmd_Str); }
		ptr_len += buf_len; }
	if (cmd_Check == -1)
	{free(buf);
		exit(0); }
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
 * @free_env_list: list of env vars to be freed
 * Return: void. Passes tokens to execution func
 */

ll *parser2(char **cmd_List, char *argv, char **env, ll *alias_List
	    , char *free_env_list)
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
			free_2d(tokes);
			continue;
		}
		for (i = 1; i < words; i++)
			tokes[i] = _strtok(cmd_List[x], &tok_idx, ' ');
		tokes[i] = NULL;
		free_env_list = builtin(cmd_List, alias_List,
					free_env_list, tokes, argv, env, &ret);
		if (ret == 0)
		{
			our_path = get_path(env, tokes[0]);
			if (our_path)
				tokes[0] = our_path;
			else
			{
				handle_err(argv, 2, tokes[0]);
				free_2d(tokes);
				continue;
			}
			exec_Cmd(tokes, argv, env);
		}
		free_2d(tokes);
		chars = 0, words = 0, tok_idx = 0;
	}
return (alias_List);
}

/**
 * handle_err - Handles errors
 * @argv: Argument
 * @err_num: Counting error numbers
 * @token: token
 * Return: Void
 */

void handle_err(char *argv, int err_num, char *token)
{
	char *temp = NULL;
	char *num = NULL;
	int error_cnt = 0;
	char *not_found = "not found\n", *illegal = "Illegal number";

	error_cnt = err_Cnt;
	num = print_number(num, error_cnt);
	if (err_num == 2 || err_num == 20)
	{
		temp = cat_err(num, argv, not_found, token);
		write(STDERR_FILENO, temp, _strlen(temp));
	}
	else if (err_num == 122)
	{
		temp = cat_err2(num, argv, illegal, token);
		write(STDERR_FILENO, temp, _strlen(temp));
	}
	else
	{
		temp = cat_err(num, argv, "No such file or directory", token);
		write(STDERR_FILENO, temp, _strlen(temp));
		perror(token);
	}
	free(temp);
	free(num);
}
