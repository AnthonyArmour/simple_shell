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
	int ttrue = 1, cmd_Count = 0;
	int id1 = fork();
	int id2 = fork();

	(void)argc;
	(void)env;
	while (ttrue)
	{
		if (id == 0)
			print_Prompt1();
		else
		{
			while (wait(NULL) != -1)
				;
			command = read_Cmd(argv[0]);
		}
		cmd_Count = _strlen(command);
		if (cmd_Count != 0)
			write(STDOUT_FILENO, command, cmd_Count);
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
		Wcheck = write(STDOUT_FILENO, err, _strlen(err)), exit(10);
}
/**
 * read_Cmd - reads command into string
 * Return: string
 */
char *read_Cmd(char *argv)
{
	char buf[1024];
	char *cmd_String = NULL;
	char *err_Str, *temp, *err_Str2, *temp2;
	int x = 0, xx = 0, rCheck = 0;
	char *num_Buf;

	num_Buf = malloc(10);
	if (!num_Buf)
		return (NULL);
	err_Str = _strcat(argv, ": ");
	temp2 = str_number(num_Buf, (unsigned int)err_Cnt);
	err_Str2 = _strcat(temp2, ": ");
	temp = _strcat(err_Str, err_Str2);
	while((rCheck = read(STDIN_FILENO, buf, 1024)) > 0)
	{
		if (!cmd_String)
		{
			cmd_String = malloc(rCheck + 1);
			if (!cmd_String)
			{
				write(STDERR_FILENO, temp, _strlen(temp));
				write(STDERR_FILENO, "Memory error", 12);
				exit(11);
			}
			for (x = 0; x < rCheck; x++)
				cmd_String[xx] = buf[x], xx++;
			cmd_String[xx] = '\0', xx++;
		}
		else
		{
			cmd_String = _realloc(cmd_String, _strlen(cmd_String),
			 _strlen(cmd_String) + rCheck);
			if (!cmd_String)
			{
				write(STDERR_FILENO, temp, _strlen(temp));
				write(STDERR_FILENO, "Memory error", 12);
				exit(11);
			}
			for (x = 0; buf[x] != '\0'; x++)
				cmd_String[xx] = buf[x];
			cmd_String[xx] = buf[x];
		}
	}
	printf("Outside while loop\n");
	return (cmd_String);
}
