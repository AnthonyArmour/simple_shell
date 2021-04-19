#include "shell.h"

/**
 * alias_Check - checks if entered cmd is alias
 * @cmd_Str: cmd str
 * @alias_List: alias list
 * @argv: argv[0]
 * Return: new cmd if found
 */

char *alias_Check(char *cmd_Str, ll *alias_List, char *argv)
{
	int i = 0, tok_idx = 0, chars = 0, words = 0, idx = 0, len = 0;
	char **tokes = NULL, *alias_Cmd = NULL, *new_Cmd = NULL;

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
		free(alias_Cmd);
		free_2d(tokes);
		return (new_Cmd);
	}
	else
	{
		free_2d(tokes);
		return (cmd_Str);
	}
}

/**
 * reset_Cmd - resets cmd str to alias
 * @alias_Cmd: new cmd
 * @argv: argv[0]
 * @cmd_Str: old cmd str
 * @idx: index rep alias in cmd str
 * @len: len of alias in cmd str
 * Return: new cmd
 */

char *reset_Cmd(char *alias_Cmd, char *argv, char *cmd_Str, int idx, int len)
{
	int x = 0, xx = 0, y = 0, m = 0, words = 0, signal = 0;
	char *new_Cmd = NULL;

	(void)argv;
	if (_strlen(alias_Cmd) > len)
		m = _strlen(alias_Cmd) - len;
	else
		m = len;
	m = _strlen(cmd_Str);
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
		new_Cmd[xx] = alias_Cmd[y], xx++;
	for (; cmd_Str[x]; x++)
		new_Cmd[xx] = cmd_Str[x], xx++;
	new_Cmd[xx] = '\0';
	free(cmd_Str);
	return (new_Cmd);
}

/**
 * rep_Alias - finds and replaces alias command
 * @alias_List: alias list
 * @argv: argv[0]
 * @tokes: tokens
 * @idx: index rep alias in cmd str
 * @len: len of alias token
 * Return: alias cmd to replace
 */

char *rep_Alias(ll *alias_List, char *argv, char **tokes, int *idx, int *len)
{
	char *cmd_Str = NULL;

	(void)argv;
	for ((*idx) = 0; tokes[(*idx)]; (*idx)++)
	{
		*len = _strlen(tokes[(*idx)]);
		tokes[(*idx)] = _realloc(tokes[(*idx)], (*len), (*len) + 2);
		_strcat(tokes[(*idx)], "=");
		while (alias_List->next != NULL)
		{
			if ((_strncmp(tokes[(*idx)], alias_List->str, (*len) + 1)) == 0)
			{
				cmd_Str = _strdup(alias_List->str + ((*len) + 2));
				break;
			}
			alias_List = alias_List->next;
		}
		if (cmd_Str == NULL)
		{
			if ((_strncmp(tokes[(*idx)], alias_List->str, (*len) + 1)) == 0)
			{
				cmd_Str = _strdup(alias_List->str + ((*len) + 2));
			}
		}
		if (cmd_Str != NULL)
			break;
	}
	if (cmd_Str != NULL)
		cmd_Str[_strlen(cmd_Str) - 1] = '\0';
	return (cmd_Str);
}


/**
 * alias_Options - checks if command is alias or adding alias
 * @argv: argv[0]
 * @cmd: cmd str
 * @alias_List: alias list
 * Return: alias list
 */

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
		free_2d(tokes);
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
	free_2d(tokes);
	(void)signal;
	return (alias_List);
}

/**
 * _strtok_Alias - custom tokenizer for alias options
 * @str: string
 * @index: keeps index for tok func
 * @delim: delim to tokenize with
 * Return: token
 */

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
