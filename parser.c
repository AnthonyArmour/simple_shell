#include "shell.h"

int main(void)
{
	/*cmdStrDimensions("     mkdir", "argv", &cmd_Str_Len, &cmd_Count);
	*/parser1("mkdir file1; mkdir file3; mkdir file5; mkdir file10", "argv");
	
	return (0);
}

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
	int cmd_Pos = 0, tmp_Len = 0;

	(void)argv;
	if (cmd_Str == NULL)
		return;
	for (cmd_Pos = 0; cmd_Str[cmd_Pos]; cmd_Pos++)
	{
		if (cmd_Str[cmd_Pos] == ';')
		{
			(*cmd_Count)++, cmd_Pos++;
			if (tmp_Len > *cmd_Str_Len)
				*cmd_Str_Len = tmp_Len;
			tmp_Len = 0;
			continue;
		}
		if (cmd_Str[cmd_Pos + 1] == '\0')
		{
			tmp_Len++;
			if (tmp_Len > *cmd_Str_Len)
				*cmd_Str_Len = tmp_Len;
			tmp_Len = 0;
		}
	tmp_Len++;
	}
	return;
}

char **parser1(char *cmd_Str, char *argv)
{
	char **cmd_List;
	int x = 0, size = 0, cmd_Pos = 0, cmd_Str_Len = 0, cmd_Count = 1;
	int list_Index = 0;

	cmdStrDimensions(cmd_Str, argv, &cmd_Str_Len, &cmd_Count);
	printf("Strlen = %d Count = %d cmd_str = %s\n", cmd_Str_Len, cmd_Count, cmd_Str);
	size = ((sizeof(char *) * (cmd_Count + 1)));
	cmd_List = (char **)malloc(size);
	for (x = 0; cmd_List[x]; x++)
	{
		cmd_List[x] = (char *)malloc(sizeof(char) * (cmd_Str_Len + 1));
	}
	x = 0;
	for (cmd_Pos = 0; cmd_Str[cmd_Pos]; cmd_Pos++)
	{
		printf("Entered for loop\n");
		cmd_List[list_Index][x] = cmd_Str[cmd_Pos];
		if (cmd_Str[cmd_Pos] == ';')
		{
			printf("Entered ; if statement\n");
			cmd_List[list_Index][x + 1] = '\0', list_Index++, x = 0;
			cmd_Pos++;
		}
		if (cmd_Str[cmd_Pos + 1] == '\0')
		{
			printf("Entered 2nd if statement\n");
			cmd_List[list_Index][x + 1] = '\0';
		}
	}
	for (x = 0; cmd_List[x]; x++)
	{
		printf("%s\n", cmd_List[x]);
	}
	return (cmd_List);
}
