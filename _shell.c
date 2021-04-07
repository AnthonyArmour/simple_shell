#include "shell.h"
/**
 * main - basic shell
 * @argc: num of cmd line args
 * @argv: args at cmd line
 * @env: environment data
 * Return: int
 */
int err_Cnt = 0;
int main(int argc, char *argv[], char *env[])
{
	char *command = NULL;
	int ttrue = 1, cmd_Count = 0, mode, x = 0;
	char **Cmd = NULL;

	(void)argv;
	(void)argc;
	(void)env;
	if ((mode = isatty(STDIN_FILENO)))
                puts("Interactive mode!");
        else
	{
                puts("Non-interactive mode!");
	}
	while (ttrue)
	{
		if (mode)
			print_Prompt1();
		command = read_Cmd("argv");
		cmd_Count = _strlen(command);
		if (command[0] == '\0' || command[0] == '\n')
		{
			free(command);
			continue;
		}
		if (strcmp(command, "exit\n") == 0)
		{
			free(command);
			break;
		}
		if (cmd_Count != 0)
		{
			Cmd = parser1(command, "argv");
			for (x = 0; Cmd[x]; x++)
				printf("command str is: %s\n", Cmd[x]);
			for (x = 0; Cmd[x]; x++)
				free(Cmd[x]);
			free(Cmd);
		}
		if (!mode)
		{
			free(command);
			break;
		}
		free(command);
	}
	return (0);
	}
/**
 * print_Prompt1 - prints prompt
 * Return: void
 */
void print_Prompt1(void)
{
	char *buf = "SS$ ";
	int Wcheck;
	char *err = "ERROR: Could not write prompt";

	Wcheck = write(STDOUT_FILENO, buf, _strlen(buf));
	if (Wcheck == -1)
	{
		Wcheck = write(STDERR_FILENO, err, _strlen(err)), exit(10);
	}
}
/**
 * read_Cmd - reads command into string
 * Return: string
 */
char *read_Cmd(char *argv)
{
	size_t bufsize = 1024;
	ssize_t cmd_Check = NULL;
	char *cmd_Str = NULL, *buf = NULL;
	/*char *err_Str = NULL, *temp = NULL, *err_Str2 = NULL;*/
	char /**temp2 = NULL, */*cmd_temp = NULL;
	int ptr_len = 0, cmd_index = 0, buf_len = 0;
/*	char *num_Buf = NULL;

	num_Buf = malloc(10);
	if (!num_Buf)
		return (NULL);
	for (x = 0; num_Buf[x]; x++)
		num_Buf[x] = '\0';
	err_Str = strcat(argv, ": ");
	temp2 = str_number(num_Buf, (unsigned int)err_Cnt);
	err_Str2 = strcat(temp2, ": ");
	temp = strcat(err_Str, err_Str2);
*/
	(void)argv;
	while(cmd_Check != -1)
	{
		cmd_Check = getline(&buf, &bufsize, stdin);
		buf_len = _strlen(buf);
		if (!cmd_Str)
			cmd_Str = malloc(buf_len + 1);
		else
		{
			cmd_temp = _realloc(cmd_Str, cmd_index, ptr_len);
		        if (cmd_temp)
				cmd_Str = cmd_temp;
			else
				free(cmd_Str), cmd_Str = NULL;
		}
		_strcpy(cmd_Str + ptr_len, buf);
		if (buf[buf_len - 1] == '\n')
		{
			if (buf_len == 1 || buf[buf_len - 2] != '\\')
			{
				free(buf);
				return (cmd_Str);
			}
			cmd_Str[ptr_len + buf_len - 2] = '\0';
			buf_len -= 2;
			print_Prompt2();
		}
		ptr_len += buf_len;
	}
	if (!cmd_Str)
	{
		write(STDERR_FILENO, "Memory error", 12);
		exit(11);
	}
	free(buf);
	return (cmd_Str);
}
/**
 * print_Prompt2 - prints > prompt
 * Return: void
 */
void print_Prompt2(void)
{
        char *buf = "> ";
        int Wcheck;
        char *err = "ERROR: Could not write prompt";

        Wcheck = write(STDOUT_FILENO, buf, _strlen(buf));
        if (Wcheck == -1)
	{
                Wcheck = write(STDERR_FILENO, err, _strlen(err)), exit(10);
	}
}
