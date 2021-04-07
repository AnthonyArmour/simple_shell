#include "shell.h"
#include <string.h>

/*int main(void)
{
	char *cmd = NULL;
	char **temp;
	int x = 0;

	printf("Prompt: ");
	cmd = read_Cmd("argv");
	temp = parser1(cmd, "argv");
	for (x = 0; temp[x]; x++)
		printf("command is: %s\n", temp[x]);
	return (0);
}
*/
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

/**
 * _strtok - Returns next word of input string
 * @str: The input string
 * @index: Where we are in the input string
 * @delim: Spaces, null bytes, semicolons
 * Return: Next word of input string
 */

char *_strtok(char *str, int index, char delim)
{
	int x = 0, y = 0;
	char *tok;

	while (str[y + index] != '\0' && str[y + index] != delim)
		y++;
	tok = malloc(sizeof(char) * (y + 1));
	if (!tok)
		return (NULL);
	for (x = 0; x < y; x++)
		tok[x] = str[x + index];
	tok[x] = '\0';
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
			tmp = _strtok(cmd_Str, cmd_Pos, ';');
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
			x++, cmd_Pos += y;
		}
	}
	cmd_List[x] = NULL;
	return (cmd_List);
}
