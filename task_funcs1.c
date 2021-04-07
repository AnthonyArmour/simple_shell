#include "shell.h"

/**
 * _strdup - pointer to newly alloced mem
 * @str: string input
 * Return: string
 *
 *
 */

char *_strdup(char *str)
{
	int x = 0;
	char *ptr = NULL;

	if (str == NULL)
	{
		return (NULL);
	}
	ptr = (char *)malloc(_strlen(str) + 1);

	if (ptr == NULL)
	{
		return (NULL);
	}
	while (str[x])
	{
		ptr[x] = str[x];
		x++;
	}
	ptr[x] = '\0';
	return (ptr);
}

/**
 * _strlen - gets string length
 * @s: pointer input
 * Return: int
 */

int _strlen(char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * free_list - frees lists
 * @head: head of list
 * Return: void
 */

/*void free_list(list_t *head)
{
	list_t *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}*/

/**
 * *_strcpy - copies string
 * @dest: pointer input
 * @src: pointer input
 * Return: char
 */

char *_strcpy(char *dest, char *src)
{
	int x = 0;

	for (; *(src + x) != '\0'; x++)
	{
		*(dest + x) = *(src + x);
	}
	*(dest + x) = *(src + x);
	return (dest);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
