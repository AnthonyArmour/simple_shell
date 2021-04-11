#include "shell.h"
extern int err_Cnt;
extern int errno;
/**
 * _strtok - Returns next word of input string
 * @str: The input string
 * @index: Where we are in the input string
 * @delim: Spaces, null bytes, semicolons
 * Return: Next word of input string
 */

char *_strtok(char *str, int *index, char delim)
{
	int x = 0, y = 0;
	char *tok;

	if (!str)
		return (NULL);
	while (str[(*index)] == ' ')
		(*index)++;
	while (str[y + (*index)] != '\0' && str[y + (*index)] != delim)
		y++;
	tok = malloc(sizeof(char) * (y + 1));
	if (!tok)
		return (NULL);
	for (x = 0; x < y; x++)
		tok[x] = str[x + (*index)];
	tok[x] = '\0';
	*index += x;
	return (tok);
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
	cmd_List = malloc(sizeof(char *) * cmd_Str_Len + cmd_Count); /*null bytes?*/
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
	int built_In = 0;
	char **tokes = NULL;
	char *our_path = NULL;
	struct stat stats;

	for (; cmd_List[x]; x++)
	{
		cmd_List[x] = alias_Check(cmd_List[x], alias_List, argv);
		dim2(cmd_List[x], &chars, &words, argv);
		tokes = malloc(sizeof(char *) * chars + words);
		tokes[0] = _strtok(cmd_List[x], &tok_idx, ' ');
		if (strcmp(tokes[0], "alias") == 0)
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
		built_In = builtin(tokes, argv, env);
		if (built_In == 0)
		{
			if (stat(tokes[0], &stats) != 0)
			{
				our_path = get_path(env, tokes[0]);
				if (our_path)
				{
					free(tokes[0]);
					tokes[0] = our_path;
				}
			}
			exec_Cmd(tokes, argv, env);
		}
		for (i = 0; tokes[i]; i++)
			free(tokes[i]);
		free(tokes);
		chars = 0, words = 0, tok_idx = 0;
	}
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
	int error_cnt, x = 0, idx = 0;
	char *not_found = "not found\n";

	err_num = errno;
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
	if (err_num == 2)
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
	else
	{
		write(STDERR_FILENO, temp, _strlen(temp));
		perror(token);
	}
	free(temp);
}
