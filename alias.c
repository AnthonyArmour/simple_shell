#include "shell.h"

/**
 * add_Alias - Calls add_Alias_node
 * @token: token
 * @argv: argv[0]
 * @alias_List: list of aliases
 * Return: alias_List
 */

ll *add_Alias(char *token, char *argv, ll *alias_List)
{
	(void)argv;


	alias_List = add_Alias_Node(&alias_List, token);
	return (alias_List);
}

/**
 * print_Alias - prints alias
 * @token: alias to print
 * @argv: argv[0]
 * @alias_List: alias list
 * Return: void
 */

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
	for (x = 0; tokes[x]; x++)
		free(tokes[x]);
	free(tokes);
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
