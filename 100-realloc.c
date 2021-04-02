#include "shell.h"
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
