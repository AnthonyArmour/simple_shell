#include "shell.h"

/**
 * cmdStrDimensions - Calculates dimensions of passed arguments/commands
 * @cmd_Str: Commands/arguments passed
 * @argv: Name of our shell executable
 * @cmd_Str_Len: Length of commands/arguments passed
 * @cmd_Count: Amount of commands/arguments passed
 * Return: Void
 */

void cmdStrDimensions(char *cmd_Str, char *argv, int *cmd_Str_Len, int *cmd_Count)
{
	int cmd_Pos = 0;

	(void)argv;
	if (cmd_Str == NULL)
		return;
	for (cmd_Pos = 0; cmd_Str[cmd_Pos]; cmd_Pos++)
	{
		if (cmd_Str[cmd_Pos] == ';')
		{
			(*cmd_Count)++;
			continue;
		}
	(*cmd_Str_Len)++;
	}
	return;
}

void dim2(char *str, int *chars, int *words)
{
	int x = 0;

	for (; str[x]; x++)
	{
		if ((str[x] != ' ' && str[x + 1] == ' ') || (str[x + 1] == '\0'))
			(*words)++;
		(*chars)++;
	}
}
