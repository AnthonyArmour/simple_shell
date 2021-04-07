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


char **parser1(char *cmd_Str, char *argv)
{
	char **cmd_List;
	char *tmp;
	int x = 0, y = 0, xx = 0, cmd_Pos = 0, cmd_Str_Len = 0, cmd_Count = 1;

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

void parser2(char **cmd_List, char *argv)
{
	int x = 0, i = 0, tok_idx = 0, chars = 0, words = 0;
	char **tokes = NULL;

	(void)argv;
	for (; cmd_List[x]; x++)
	{
		dim2(cmd_List[x], &chars, &words);
		tokes = malloc(sizeof(char *) * chars + words);
		tokes[0] = _strtok(cmd_List[x], &tok_idx, ' ');
		for (i = 1; i < words; i++)
		{
			tokes[i] = _strtok(cmd_List[x], &tok_idx, ' ');
		}
		tokes[i] = NULL;
		exec_Cmd(tokes);
		/*for (i = 0; tokes[i]; i++)
			printf("%s\n", tokes[i]);*/
		for (i = 0; tokes[i]; i++)
			free(tokes[i]);
		free(tokes);
		chars = 0, words = 0, tok_idx = 0;
	}
}

void exec_Cmd(char **tokes)
{
	pid_t pid = fork();

	if (pid != 0)
	{
		while (wait(NULL) != -1)
			;
	}
	else
	{
		if (execve(tokes[0], tokes, NULL) == -1)
		{
			perror("exec failure");
			exit(-1);
		}
	}
	return;
}
