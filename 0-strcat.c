#include "shell.h"
/**
 * _strcat - concatinate string
 * @dest: str input
 * @src: str input
 * Return: string
 */
char *_strcat(char *dest, char *src)
{
	int dest_len = 0;
	int x = 0;

	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}
	for (; src[x] != '\0'; x++)
	{
		dest[dest_len] = src[x];
		dest_len++;
	}
	dest[dest_len] = '\0';
	return (dest);
}
