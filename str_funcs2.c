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

	if (str[x] == '\0')
		return (-1);
	for (x = 0; str[x]; x++)
	{
		if (str[x] == delim || str[x + 1] == '\0')
			count++;
	}
	return (count);
}

/**
 * print_number - prints a number
 * @n: number to print
 * @str: str
 * Return: number
 */

char *print_number(char *str, int n)
{
	unsigned int x;
	unsigned int nn = n;
	unsigned int y = 1000000000;
	int idx = 0, len = 0;

	while (nn >= 1)
	{
		if (nn >= y)
		{
			if (str)
				len = _strlen(str);
			x = nn / y;
			str = _realloc(str, len, len + 2);
			str[idx] = ('0' + x), idx++;
			nn = nn - (x * y);
			y = y / 10;
			while (nn < y)
			{
				if (str)
					len = _strlen(str);
				str = _realloc(str, len, len + 1);
				str[idx] = ('0' + x), idx++;
				y = y / 10;
			}
		}
		else
		{
			y = y / 10;
		}
	}
	str[idx] = '\0';
	return (str);
}

/**
 * cat_err - concats error message
 * @num: error number
 * @argv: argument
 * @var: special message
 * @token: token
 * Return: temp
 */

char *cat_err(char *num, char *argv, char *var, char *token)
{
	int x = 0;
	char *temp = NULL, *col_space = ": ";

	temp = malloc(_strlen(argv) + 3);
	for (x = 0; argv[x]; x++)
		temp[x] = argv[x];
	temp[x] = '\0';
	_strcat(temp, col_space);

	temp = _realloc(temp, _strlen(temp) + 1,
			_strlen(temp) + _strlen(num) + 3);
	_strcat(temp, num);
	_strcat(temp, col_space);

	temp = _realloc(temp, _strlen(temp) + 1,
			_strlen(temp) + _strlen(token) + 3);
	_strcat(temp, token);
	_strcat(temp, col_space);

	temp = _realloc(temp, _strlen(temp) + 1,
			_strlen(temp) + _strlen(var) + 1);
	_strcat(temp, var);
	return (temp);
}

/**
 * free_2d - frees 2d array
 * @arr: 2d array
 * Return: void
 */

void free_2d(char **arr)
{
	int x = 0;

	for (x = 0; arr[x]; x++)
		free(arr[x]);
	free(arr);
}
