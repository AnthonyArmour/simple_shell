#include "shell.h"

/*char *str_number(char *buf, unsigned int n)
{
	char *temp = buf;

	if (n == 0)
		return (NULL);
	if (n / 10)
		str_number(buf, n / 10);
	buf[num_index] = (n % 10 + '0'), num_index++;
	return (temp);
}*/

int num_index = 0;
char *str_number(char *buf, unsigned int n)
{
	unsigned int x;
	unsigned int nn = n;
	unsigned int y = 1000000000;
	if (nn < 1)
	{
		buf[num_index] = '0', num_index++;
	}
	while (nn >= 1)
	{
		if (nn >= y)
		{
			x = nn / y;
			buf[num_index] = ('0' + x), num_index++;
			nn = nn - (x * y);
			y = y / 10;
			while (nn < y)
			{
				buf[num_index] = '0', num_index++;
				y = y / 10;
			}
		}
		else
		{
			y = y / 10;
		}
	}
	buf[num_index] = '\0';
	return (buf);
}

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
