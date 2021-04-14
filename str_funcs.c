#include "shell.h"

/**
 * _strdup - pointer to newly alloced mem
 * @str: string input
 * Return: string
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
 * _realloc - reallocates mem
 * @ptr: ptr
 * @old_size: un int
 * @new_size: un int
 * Return: ptr
 */

char *_realloc(char *ptr, unsigned int old_size, unsigned int new_size)
{
	char *nptr;
	int x = 0;

	if (new_size == 0 && !ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	if (!ptr)
	{
		ptr = malloc(new_size);
		if (!ptr)
			return (NULL);
	}
	nptr = malloc(new_size);
	if (!nptr)
		return (NULL);
	for (; ptr[x]; x++)
		nptr[x] = ptr[x];
	nptr[x] = '\0';
	free(ptr);
	return (nptr);
}

/**
 * _strcmp - compares two strings
 * @s1: str input
 * @s2: str input
 * Return: int
 */

int _strcmp(char *s1, char *s2)
{
	int x = 0;

	for (; s1[x] != '\0'; x++)
	{
		if (s1[x] != s2[x])
		{
			return (s1[x] - s2[x]);
		}
	}
	return (s1[x] - s2[x]);
}
