#include "shell.h"

/**
 * StrDimensions - Calculates dimensions of passed arguments/commands
 * @cmd_Str: Commands/arguments passed
 * @argv: Name of our shell executable
 * @cmd_Str_Len: Length of commands/arguments passed
 * @cmd_Count: Amount of commands/arguments passed
 * Return: Void
 */

void StrDimensions(char *cmd_Str, char *argv, int *cmd_Str_Len, int *cmd_Count)
{
	int cmd_Pos = 0;

	if (cmd_Str == NULL)
	{
		perror(argv);
		exit(EXIT_FAILURE);
	}
	for (cmd_Pos = 0; cmd_Str[cmd_Pos]; cmd_Pos++)
	{
		if (cmd_Str[cmd_Pos] == ';')
		{
			(*cmd_Count)++;
			continue;
		}
	(*cmd_Str_Len)++;
	}
}

/**
 * dim2 - finds the dimensions of a str
 * @str: input string
 * @chars: num of chars in str
 * @words: num of words in string
 * @argv: argv[0]
 * Return: void
 */

void dim2(char *str, int *chars, int *words, char *argv)
{
	int x = 0;

	if (!str)
	{
		perror(argv);
		exit(EXIT_FAILURE);
	}
	for (; str[x]; x++)
	{
		if ((str[x] != ' ' && str[x + 1] == ' ') || (str[x + 1] == '\0'))
			(*words)++;
		(*chars)++;
	}
}

/**
 * dim3 - gets amount of chars and words based on delim
 * @str: str to count
 * @chars: num of letter
 * @words: num of words based on delim
 * @argv: argv[0]
 * Return: void
 */

void dim3(char *str, int *chars, int *words, char *argv)
{
	int x = 0;

	if (!str)
	{
		perror(argv);
		exit(EXIT_FAILURE);
	}
	for (; str[x]; x++)
	{
		if (str[x] == 39)
		{
			x++;
			while (str[x] != 39)
				x++;
		}
		if ((str[x] != ' ' && str[x + 1] == ' ') || (str[x + 1] == '\0'))
			(*words)++;
		(*chars)++;
	}
}
