#include "shell.h"

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
	cmdStrDimensions(cmd_Str, argv, &cmd_Str_Len, &cmd_Count);
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
 * Return: void. Passes tokens to execution func
 */

void parser2(char **cmd_List, char *argv, char **env)
{
	int x = 0, i = 0, tok_idx = 0, chars = 0, words = 0;
	int built_In = 0;
	char **tokes = NULL;
	char *our_path = NULL;

/*JWOW question*/
/*check cmd_List? return what?*/
	for (; cmd_List[x]; x++)
	{
		dim2(cmd_List[x], &chars, &words, argv);
		tokes = malloc(sizeof(char *) * chars + words);
		tokes[0] = _strtok(cmd_List[x], &tok_idx, ' ');
		for (i = 1; i < words; i++)
		{
			tokes[i] = _strtok(cmd_List[x], &tok_idx, ' ');
		}
		tokes[i] = NULL;
		built_In = builtin(tokes, argv, env);
		if (built_In == 0)
		{
			our_path = get_path(env, tokes[0]);
			free(tokes[0]);
			tokes[0] = our_path;
			exec_Cmd(tokes, argv, env);
		}
		for (i = 0; tokes[i]; i++)
			free(tokes[i]);
		free(tokes);
		chars = 0, words = 0, tok_idx = 0;
	}
}
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
	return (paths[final_path_idx]);

}
int builtin(char **tokes, char *argv, char **env)
{
	int x = 0, ret = 0;

	b_in built_in[] = {
		{"jhgfkf", b_env}, {NULL, NULL}
	};

	for (x = 0; built_in[x].var; x++)
	{
		if ((strcmp(tokes[0], built_in[x].var)) == 0)
		{
			built_in[x].f(tokes, argv, env);
			ret++;
		}
	}

	return (ret);
}
int b_env(char **tokes, char *argv, char **env)
{
	int x = 0;

	(void)argv;
	(void)tokes;
	for (x = 0; env[x]; x++)
	{
		write(STDOUT_FILENO, env[x], _strlen(env[x]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * exec_Cmd - execute function
 * @tokes: 2d array of tokens
 * @argv: argv[0]
 * Return: void
 */

void exec_Cmd(char **tokes, char *argv, char **env)
{
	pid_t pid = fork();

	if (pid != 0)
	{
		while (wait(NULL) != -1)
			;
	}
	else
	{
		if (execve(tokes[0], tokes, env) == -1)
		{
/*			write(STDERR_FILENO, argv, _strlen(argv));
			write(STDERR_FILENO, ": ", 2);
*/			perror(argv);
			exit(-1);
		}
	}
	return;
}
