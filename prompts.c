#include "shell.h"

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
