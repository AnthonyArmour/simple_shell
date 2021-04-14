#include "shell.h"

/**
 * str_mul_cat - concatenates multiple strings
 * @dest: destination string
 * @str1: first string
 * @str2: second string
 * Return: concatenated string
 */

char *str_mul_cat(char *dest, char *str2, char *str1)
{
	if (dest && str2 && str1)
	{
		_strcat(dest, str1);
		_strcat(dest, str2);
	}
	return (dest);
}

/**
 * get_size - gets number of delimiters
 * @str: string to evaluate
 * @delim: delimiters
 * Return: number of delimiters
 */

size_t get_size(char *str, char delim)
{
	size_t x = 0, count = 0;

	for (x = 0; str[x]; x++)
	{
		if (str[x] == delim || str[x + 1] == '\0')
			count++;
	}
	return (count);
}

char *print_number(int n)
{
	unsigned int x;
	unsigned int nn = n;
	unsigned int y = 1000000000;
	int idx = 0;
	char *str = NULL;

	str = malloc(1);
	str[0] = '\0';
	while (nn >= 1)
	{
		if (nn >= y)
		{
			x = nn / y;
			str = _realloc(str, _strlen(str), _strlen(str) + 1);
			str[idx] = ('0' + x), idx++;
			nn = nn - (x * y);
			y = y / 10;
			while (nn < y)
			{
				str = _realloc(str, _strlen(str), _strlen(str) + 1);
				str[idx] = ('0' + x), idx++;
				y = y / 10;
			}
		}
		else
		{
			y = y / 10;
		}
	}
	str[idx + 1] = '\0';
	return (str);
}
