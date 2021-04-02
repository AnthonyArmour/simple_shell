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
