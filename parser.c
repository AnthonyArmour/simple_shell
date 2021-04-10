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

char *_strtok_Alias(char *str, int *index, char delim)
{
	int x = 0, y = 0;
	char *tok;

	if (!str)
		return (NULL);
	while (str[(*index)] == ' ')
		(*index)++;
	while (str[y + (*index)] != '\0' && str[y + (*index)] != delim)
	{
		y++;
		if (str[y + (*index)] == 39)
		{
			y++;
			while (str[y + (*index)] != 39)
				y++;
			y++;
			break;
		}
	}
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

ll *add_Alias(char *token, char *argv, ll *alias_List)
{
	(void)argv;


	alias_List = add_Alias_Node(&alias_List, token);
	return (alias_List);
}

void print_Alias(char *token, char *argv, ll *alias_List)
{
	int signal = 0;

	strcat(token, "=");
	(void)argv;
	while (alias_List->next != NULL)
	{
		if ((strncmp(alias_List->str, token, _strlen(token))) == 0)
		{
			write(STDOUT_FILENO, alias_List->str, _strlen(alias_List->str));
			write(STDOUT_FILENO, "\n", 1);
			signal++;
			break;
		}
		else
			alias_List = alias_List->next;
	}	
	if (alias_List->next == NULL)
	{
		if ((strncmp(alias_List->str, token, _strlen(token))) == 0)
		{
			write(STDOUT_FILENO, alias_List->str, _strlen(alias_List->str));
			write(STDOUT_FILENO, "\n", 1);
			signal++;
		}
	}
	if (signal == 0)
		printf("OOPSIES\n");
}

ll *alias_Options(char *argv, char *cmd, ll *alias_List)
{
	int x = 1, y = 0, signal = 0, tok_idx = 0, chars = 0, words = 0;
	char **tokes = NULL;

	dim3(cmd, &chars, &words, argv);
	tokes = malloc(sizeof(char *) * chars + words);
	tokes[0] = _strtok_Alias(cmd, &tok_idx, ' ');
	for (x = 1; x < words; x++)
		tokes[x] = _strtok_Alias(cmd, &tok_idx, ' ');
	tokes[x] = NULL;
	if (tokes[1] == NULL)
	{
		print_list(alias_List);
		return (alias_List);
	}
	for (x = 1; tokes[x]; x++)
	{
		for (y = 0; tokes[x][y]; y++)
		{
			if (tokes[x][y] == '=')
			{
				alias_List = add_Alias(tokes[x], argv, alias_List);
				signal = 1;
				break;
			}
		signal = 0;
		}
		if (signal == 0)
			print_Alias(tokes[x], argv, alias_List);
	}
	(void)signal;
	return (alias_List);
}

/**
 * parser2 - tokenizes strings into tokens
 * @cmd_List: 2d array of strings
 * @argv: argv[0]
 * @env: environ
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
	return (alias_List);
}

char *alias_Check(char *cmd_Str, ll *alias_List, char *argv)
{
	int i = 0, tok_idx = 0, chars = 0, words = 0, idx = 0, len = 0;
	char **tokes = NULL, *alias_Cmd = NULL, *new_Cmd;

	dim2(cmd_Str, &chars, &words, argv);
	tokes = malloc(sizeof(char *) * chars + words);
	tokes[0] = _strtok(cmd_Str, &tok_idx, ' ');
	for (i = 1; i < words; i++)
		tokes[i] = _strtok(cmd_Str, &tok_idx, ' ');
	tokes[i] = NULL;
	if (alias_List != NULL)
		alias_Cmd = rep_Alias(alias_List, argv, tokes, &idx, &len);
	if (alias_Cmd != NULL)
	{
		new_Cmd = reset_Cmd(alias_Cmd, argv, cmd_Str, idx, len);
		return (new_Cmd);
	}
	else
		return (cmd_Str);
}

char *reset_Cmd(char *alias_Cmd, char *argv, char *cmd_Str, int idx, int len)
{
	int x = 0, xx = 0, y = 0, m = 0, words = 0, signal = 0;
	char *new_Cmd;

	(void)argv;
	if (_strlen(alias_Cmd) > len)
		m = _strlen(alias_Cmd) - len;
	else
		m = len;
	new_Cmd = malloc(_strlen(cmd_Str) + m);
	for (x = 0; cmd_Str[x]; x++)
	{
		if (cmd_Str[x] != ' ' && cmd_Str[x + 1] == ' ')
			words++, x++;
		if (words == idx)
		{
			while (cmd_Str[x])
			{
				if (cmd_Str[x] != ' ')
				{
					signal++;
					break;
				}
				x++;
			}
		}
		if (signal != 0)
			break;
	}
	for (xx = 0; xx < x; xx++)
		new_Cmd[xx] = cmd_Str[xx];
	x += len;
	for (y = 0; alias_Cmd[y]; y++)
	{
		new_Cmd[xx] = alias_Cmd[y];
		xx++;
	}
	for (; cmd_Str[x]; x++)
		new_Cmd[xx] = cmd_Str[x], xx++;
	new_Cmd[xx] = '\0';
	free(cmd_Str);
	return (new_Cmd);
}

char *rep_Alias(ll *alias_List, char *argv, char **tokes, int *idx, int *len)
{
	char *cmd_Str = NULL;

	(void)argv;
	for ((*idx) = 0; tokes[(*idx)]; (*idx)++)
	{
		*len = _strlen(tokes[(*idx)]);
		tokes[(*idx)] = _realloc(tokes[(*idx)], *len, (*len) + 1);
		strcat(tokes[(*idx)], "=");
		while (alias_List->next != NULL)
		{
			if ((strncmp(tokes[(*idx)], alias_List->str, (*len) + 1)) == 0)
			{
				cmd_Str = _strdup(alias_List->str);
				break;
			}
			alias_List = alias_List->next;
		}
		if (cmd_Str == NULL)
		{
			if ((strncmp(tokes[(*idx)], alias_List->str, (*len) + 1)) == 0)
				cmd_Str = _strdup(alias_List->str);
		}
		if (cmd_Str != NULL)
			break;
	}
	if (cmd_Str != NULL)
	{
		cmd_Str += ((*len) + 2);
		cmd_Str[_strlen(cmd_Str) - 1] = '\0';
	}
	return (cmd_Str);	
}

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
	return (paths[final_path_idx]);

}

/**
 * builtin - checks if command is builtin
 * @tokes: command string
 * @argv: argv 0
 * @env: environment
 * Return: 0 if not builtin
 */

int builtin(char **tokes, char *argv, char **env)
{
	int x = 0, ret = 0;

	b_in built_in[] = {
		{"exit", my_exit}, {"setenv", _setenv}, {"env", b_env},
	{"unsetenv", _unsetenv}, {NULL, NULL}
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
int _setenv(char **tokes, char *argv, char **env)
{
	int x = 0;
	char *tmp;

	(void)argv;
	while (env[x])
	{
		if (strncmp(env[x], tokes[1], _strlen(tokes[1])) == 0)
			break;
		x++;
	}
	if (env[x] != NULL)
	{
		tmp = str_mul_cat(tokes[1], tokes[2], "=");
		env[x] = _strdup(tmp);
	}
	else
	{
		tmp = str_mul_cat(tokes[1], tokes[2], "=");
		env[x] = _strdup(tmp);
		env[x + 1] = NULL;
	}
	return (1);
}

int _unsetenv(char **tokes, char *argv, char **env)
{	
	int x = 0;

	(void)argv;
	while (env[x])
	{
		if (strncmp(env[x], tokes[1], _strlen(tokes[1])) == 0)
			break;
		x++;
	}
	if (env[x] != NULL)
	{
		while (env[x + 1] != NULL)
		{
			env[x] = env[x + 1];
			x++;
		}
		env[x] = env[x + 1];
	}	
	return (1);
}

int my_exit(char **tokes, char *argv, char **env)
{
	(void)argv;
	(void)env;
	if (tokes[1] == NULL)
		exit(0);
	else
		exit(atoi(tokes[1]));
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

	(void)env;
	if (pid != 0)
	{
		while (wait(NULL) != -1)
			;
	}
	else
	{
		if (execve(tokes[0], tokes, NULL) == -1)
		{
/*			write(STDERR_FILENO, argv, _strlen(argv));
			write(STDERR_FILENO, ": ", 2);
*/			perror(argv);
			exit(-1);
		}
	}
	return;
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
