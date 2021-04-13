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
		return (new_Cmd);
	}
	else
		return (cmd_Str);
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
/*	int x = 0;
 */
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
/*	for (x = 0; tokes[x]; x++)
		free(tokes[x]);
	free(tokes);
*/	return (cmd_Str);
}
