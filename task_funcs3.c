#include "shell.h"
char *str_number(char *buf, unsigned int n)
{
	char *temp = buf;

	if (n == 0)
		return (NULL);
	if (n / 10)
		str_number(buf, n / 10);
	*buf = (n % 10 + '0'), buf++;
	return (temp);
}
