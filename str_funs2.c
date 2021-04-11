#include "shell.h"
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
