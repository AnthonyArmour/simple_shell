#include "shell.h"

/**
 * _strcat - concats strs
 * @str: string 1
 * @str2: string 2
 * Return: concatenated string
 */

char *_strcat(char *str, char *str2)
{
	int x = 0, xx = 0;

	if (!str)
		return (NULL);
	for (x = 0; str[x]; x++)
		;
	for (xx = 0; str2[xx]; xx++)
	{
		str[x] = str2[xx];
		x++;
	}
	str[x] = '\0';
	return (str);
}
